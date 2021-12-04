#include "AmazonasGame.h"
#include "AmazonaTool.h"

using namespace std;
AmazonasGame::AmazonasGame(bool bSetBoard)
	:GameBase(AMAZONAS_BOARDSIZE, AMAZONAS_NUMTOOLS)
{
	// set AmazonasGame
	m_gameOn = true;
	setTurn(belongToPlayer::player1);
	setWinner(belongToPlayer::notExist);

	// set board
	if(bSetBoard == true)
		setGameBoard();
	m_gType = gameType::amazons;
}

bool AmazonasGame::checkIfHavePossibleMoves(int row, int col) {
	int size;
	//assuming the position is ok (valid position and not enpty)
	Position* arr = getGameToolInPosition(row, col).getPossibleMoves(size);
	if (size == 0)
		return false;
	else
		return true;
}

//this function checks if either of the players has no more moves, and sets the winner and the gameOn
void AmazonasGame::checkGameEnd()
{
	ToolBase** pl1_Tools = m_pl1.getToolArr();
	ToolBase** pl2_Tools = m_pl2.getToolArr();
	int tempCol, tempRow;
	bool pl1_W = false, pl2_W = false;

	for (int i = 0; i < 4; i++) {
		tempCol = pl1_Tools[i]->getCol();
		tempRow = pl1_Tools[i]->getRow();
		if (checkIfHavePossibleMoves(tempRow, tempCol)) {
			pl1_W = true;
			break;
		}
	}
	for (int i = 0; i < 4; i++) {
		tempCol = pl2_Tools[i]->getCol();
		tempRow = pl2_Tools[i]->getRow();
		if (checkIfHavePossibleMoves(tempRow, tempCol)) {
			pl2_W = true;
			break;
		}
	}

	// game not ended
	if (pl1_W && pl2_W)
		return;

	// game ended, set the winner
	if (pl1_W == false)
		setWinner(belongToPlayer::player2); //pl2 won
	else
		setWinner(belongToPlayer::player1); //pl1 won
}

void AmazonasGame::setGameBoard() {
	//m_pl1.setNumOfTools(4);
	//m_pl2.setNumOfTools(4);
	for (int i = 1; i <= m_boardSize; i++) {
		for (int j = 1; j <= m_boardSize; j++) {
			if (((i == 1) && (j == 4 || j == 7)) || ((i == 4) && (j == 1 || j == 10))) {
				m_boardVec[i - 1][j - 1] = new AmazonaTool(i, j, belongToPlayer::player1,this);
				m_pl1.addTool(*m_boardVec[i - 1][j - 1]);
			}
			else if (((i == 7) && (j == 1 || j == 10)) || ((i == 10) && (j == 4 || j == 7))) {
				m_boardVec[i - 1][j - 1] = new AmazonaTool(i, j, belongToPlayer::player2,this);
				m_pl2.addTool(*m_boardVec[i - 1][j - 1]);
			}
			else
				m_boardVec[i - 1][j - 1] = nullptr;
		}
	}
}

void AmazonasGame::printBoard() {
	cout << *this;
	operator<<(cout, *this);
}

ostream& operator<<(ostream& o, AmazonasGame& g)
{
	o << "   ";
	for (int x = 0; x < g.m_boardSize; x++)
		o << "   " << x + 1;
	o << endl;
	o << "____";
	for (int x = 0; x < g.m_boardSize; x++)
		o << "____";
	o << endl;

	for (int i = 0; i < g.m_boardSize; i++) {
		if ((i + 1) < 10)
			o << " " << i + 1 << "  |";
		else
			o << " " << i + 1 << " |";

		for (int j = 0; j < g.m_boardSize; j++) {
			o << " ";
			if (g.m_boardVec[i][j] != nullptr)
				o << *g.m_boardVec[i][j];
			else
				o << " ";
			o << " |";
		}
		o << endl;
	}

	o << endl << endl;
	return o;
}

void AmazonasGame::burnPos(int row, int col)
{
	//assuming that toR,toC are valid and there is nullptr there right now
	m_boardVec[row - 1][col - 1] = new AmazonaTool(row, col, belongToPlayer::burned, this);
}

int AmazonasGame::FindIndexInMovesArr(Position* arr, int size, int row, int col) const
{
	int index = -1;
	for (int i = 0; i < size; i++)
	{
		if (row == arr[i].r && col == arr[i].c)
			index = i;
	}

	return index;
}

MoveResult AmazonasGame::move()
{
	int row, col, moveRow, moveCol, size, RowMark, ColMark, ArrowSize;

	// we print to the user who the turn is and ask him for row and col to move from
	if (m_winner != belongToPlayer::notExist)
	{
		cout << "The game is over." << endl;
		return MoveResult::GameIsOver;
	}

	cout << endl << "This is ";
	printTurn();
	cout << " turn" << endl << "Please enter the row and col of the Game tool that you want to move: " << endl;
	cin >> row >> col;
	//we cheak if the user enter a square in the board limits
	if (checkGameToolIsValid(row, col) == false)
	{
		cout << endl << "-- not a valid position-- " << endl << endl;
		return MoveResult::InvalidPosition;
	}
	// if the user enter a square that have there amazona that need to move

	//if (currGame->Game->getGameToolInPosition(row, col).getWhoBelongTo() != currGame->Game->getTurn())
	if (getBelongToInPos(row, col) != getTurn())
	{
		cout << endl << "-- This position does not have a tool that belongs to the current player's turn --" << endl << endl;
		return MoveResult::ToolBelongToOtherPlayer;
	}

	Position* possibleMovArr = getGameToolInPosition(row, col).getPossibleMoves(size);
	if (size == 0)
	{
		cout << endl << "-- This tile cannot move anywhere --" << endl << endl;
		delete[] possibleMovArr;
		return MoveResult::NoPossibleMoves;
	}

	cout << endl << "Please enter the row and col of the panle that you want the Game tool to move to: " << endl;
	cin >> moveRow >> moveCol;
	int index = FindIndexInMovesArr(possibleMovArr, size, moveRow, moveCol);

	if (index == -1)
	{
		cout << "-- Can't move there --" << endl;
		delete[] possibleMovArr;
		return MoveResult::NotAPossibleMove;
	}
	else
	{
		//became the square from not exsits to the player who get this square
		cout << "please enter locations that you want to mark" << endl;
		cin >> RowMark >> ColMark;

		if (RowMark == row && ColMark == col)//if we shoot to mark where we came from
		{
			//change the square status to not burned and the new pos to the player
			moveTool(row, col, moveRow, moveCol);
			burnPos(row, col);
			cout << endl << "the square is burned" << endl;
		}
		else
		{
			//this move is required so that building the ArrowArray will not be on nullptr tool
			moveTool(row, col, moveRow, moveCol);

			//Position* ArrowArray = dynamic_cast<AmazonaTool&>(getGameToolInPosition(moveRow, moveCol)).getMovesForArrow(ArrowSize);
			Position* ArrowArray = getGameToolInPosition(moveRow, moveCol).getPossibleMoves(ArrowSize);
			index = FindIndexInMovesArr(ArrowArray, ArrowSize, RowMark, ColMark);
			if (index == -1)
			{
				cout << "impossible square! you cant shoot and burned this square!" << endl;
				//return the amazona to the original location, because the mark position is wrong

				moveTool(moveRow, moveCol, row, col);

				delete[] ArrowArray;
				delete[] possibleMovArr;
				return MoveResult::Success;
			}
			else
			{
				burnPos(RowMark, ColMark);
				cout << endl << "the square is burned" << endl;
				delete[] ArrowArray;
			}
		}
	}
	delete[] possibleMovArr;

	//set next players turn
	if (getTurn() == belongToPlayer::player1)
		setTurn(belongToPlayer::player2);
	else
		setTurn(belongToPlayer::player1);

	checkGameEnd();

	return MoveResult::Success;
}

void AmazonasGame::saveTool(std::ofstream& ofs, ToolBase* tool)
{
	tool->saveToFile(ofs);
}

ToolBase* AmazonasGame::readTool(std::ifstream& ifs)
{
	if (!ifs.good())
		throw runtime_error("file is bad cant read tool");

	ToolBase* tool = new AmazonaTool(this);
	tool->readFromFile(ifs);
	return tool;
}
