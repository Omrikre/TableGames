#include "Chess.h"
#include "Steeple.h"
#include "Knight.h"
#include "King.h"
#include "Queen.h"
#include "Bishop.h"
#include "Pawn.h"
#include <iostream>

using namespace std;

Chess::Chess(bool bSetBoard)
	:GameBase(CHESS_BOARDSIZE, CHESS_NUMTOOLS)
{
	// set Chess
	m_gameOn = true;
	setTurn(belongToPlayer::player1);
	m_winner = belongToPlayer::notExist;

	// set board
	if(bSetBoard == true)
		setGameBoard();
	m_gType = gameType::chess;

}
Chess::~Chess()
{
}

void Chess::setGameBoardRow1(belongToPlayer pl) {
	int i;
	Player* plPoint;
	if (pl == belongToPlayer::player1) {
		i = 0;
		plPoint = &m_pl1;
	}
	else {
		i = 7;
		plPoint = &m_pl2;
	}

	m_boardVec[i][0] = new Steeple((i + 1), 1, pl, this); // steeple
	m_boardVec[i][1] = new Knight((i + 1), 2, pl, this); // knight
	m_boardVec[i][2] = new Bishop((i + 1), 3, pl, this); // bishop
	m_boardVec[i][3] = new Queen((i + 1), 4, pl, this); // queen
	m_boardVec[i][4] = new King((i + 1), 5, pl, this); // king
	m_boardVec[i][5] = new Bishop((i + 1), 6, pl, this); // bishop
	m_boardVec[i][6] = new Knight((i + 1), 7, pl, this); // knight
	m_boardVec[i][7] = new Steeple((i + 1), 8, pl, this); // steeple
}

void Chess::printBoard() 
{ 
	cout << *this; 
}

ostream& operator<<(ostream& o, Chess& g)
{
	o << "   ";
	for (int x = 0; x < g.getBoardSize(); x++)
		o << "   " << x + 1;
	o << endl;
	o << "____";
	for (int x = 0; x < g.getBoardSize(); x++)
		o << "____";
	o << endl;

	for (int i = 0; i < g.getBoardSize(); i++) {
		if ((i + 1) < 10)
			o << " " << i + 1 << "  |";
		else
			o << " " << i + 1 << " |";

		for (int j = 0; j < g.getBoardSize(); j++) {
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

void Chess::setGameBoardRow2(belongToPlayer pl) {
	int i;
	Player* plPoint;
	if (pl == belongToPlayer::player1) {
		i = 1;
		plPoint = &m_pl1;
	}
	else {
		i = 6;
		plPoint = &m_pl2;
	}

	for (int j = 0; j < m_boardSize; j++) {
		m_boardVec[i][j] = new Pawn(i+1, j+1, pl, this);
	}
}

int Chess::FindIndexInMovesArr(Position* arr, int size, int row, int col) const
{
	int index = -1;
	for (int i = 0; i < size; i++)
	{
		if (row == arr[i].r && col == arr[i].c)
			index = i;
	}

	return index;
}

bool Chess::checkIfGameEnded() {
	Player* nextPl;
	if (m_turn == belongToPlayer::player1)
		nextPl = &m_pl2;
	else
		nextPl = &m_pl1;

	ToolBase** arr = nextPl->getToolArr();
	int size = nextPl->getNumOfTools();

	//TODO - after each move, check if the next players king- all its possible moves have risks + 
	// its current position has risks and then set winner, game on , and return true
	// otherwise - return false
	return false;
}


MoveResult Chess::move()
{
	int row, col, moveRow, moveCol, size;

	// we print to the user who the turn is and ask him for row and col to move from
	if (getWinner() != belongToPlayer::notExist) {
		cout << "-- The game is over --" << endl << endl;
		return MoveResult::GameIsOver;
	}

	cout << endl << "Please enter the row and col of the Game tool that you want to move: " << endl;
	cin >> row >> col;
	//we cheak if the user enter a square in the board limits
	if (!checkGameToolIsValid(row, col)) {
		cout << endl << "-- not a valid position-- " << endl << endl;
		return MoveResult::InvalidPosition;
	}
	// if the user enter a square that have there amazona that need to move

	//if (currGame->Game->getGameToolInPosition(row, col).getWhoBelongTo() != currGame->Game->getTurn())
	if (getBelongToInPos(row, col) !=getTurn()) {
		cout << endl << "-- This position does not have a tool that belongs to the current player's turn --" << endl << endl;
		return MoveResult::ToolBelongToOtherPlayer;
	}

	Position* possibleMovArr = getGameToolInPosition(row, col).getPossibleMoves(size);
	if (size == 0) {
		cout << endl << "-- This tile cannot move anywhere --" << endl << endl;
		delete[] possibleMovArr;
		return MoveResult::NoPossibleMoves;
	}

	cout << endl << "Please enter the row and col of the panle that you want the Game tool to move to: " << endl;
	cin >> moveRow >> moveCol;
	int index = FindIndexInMovesArr(possibleMovArr, size, moveRow, moveCol);

	if (index == -1) {
		cout << "-- Can't move there --" << endl;
		delete[] possibleMovArr;
		return MoveResult::NotAPossibleMove;
	}
	else {
		//if moving to opponent tool - remove it
		if (this->getBelongToInPos(moveRow, moveCol) == belongToPlayer::player2 && getTurn() == belongToPlayer::player1 )
		{
			m_pl2.removeTool(getGameToolInPosition(moveRow, moveCol));
			removeTool(moveRow,moveCol);
		}
		else if (this->getBelongToInPos(moveRow, moveCol) == belongToPlayer::player1 && getTurn() == belongToPlayer::player2)
		{
			m_pl1.removeTool(getGameToolInPosition(moveRow, moveCol));
			removeTool(moveRow, moveCol);
		}
		moveTool(row, col, moveRow, moveCol);

		delete[] possibleMovArr;
	}

	//check if winner
	if (checkIfGameEnded() == true)
	{
		cout << "The winner is player:" << (int)getWinner() << "!!!" << endl;
	}

	//set next players turn
	if (getTurn() == belongToPlayer::player1)
		setTurn(belongToPlayer::player2);
	else
		setTurn(belongToPlayer::player1);

	return MoveResult::Success;

 }

void Chess::setGameBoard() {

	setGameBoardRow1(belongToPlayer::player1); // row 1 pl 1
	setGameBoardRow2(belongToPlayer::player1); // row 2 pl 1

	// rows 3 - 6  empty panels
	for (int i = 3; i <= (m_boardSize - 2); i++) {
		for (int j = 1; j <= m_boardSize; j++)
			m_boardVec[i - 1][j - 1] = nullptr;
	}
			
	setGameBoardRow1(belongToPlayer::player2); // row 7 pl 2
	setGameBoardRow2(belongToPlayer::player2); // row 8 pl 2

	for (int i = 0; i < m_boardSize; i++)
	{
		for (int j = 0; j < m_boardSize; j++)
		{
			if (m_boardVec[i][j] != nullptr)
			{
				if (m_boardVec[i][j]->getWhoBelongTo() == belongToPlayer::player1)
				{
					m_pl1.addTool(*m_boardVec[i][j]);
				}
				else
				{
					m_pl2.addTool(*m_boardVec[i][j]);
				}
			}
		}
	}
}

void Chess::saveTool(std::ofstream& ofs, ToolBase* tool)
{
	ChessGameTool* chessTool = dynamic_cast<ChessGameTool*>(tool);
	//TODO - if chessTool == nullptr - throw exception
	toolType tType = chessTool->getToolType();
	ofs.write(reinterpret_cast<const char*>(&tType), sizeof(toolType));

	tool->saveToFile(ofs);
}

ToolBase* Chess::readTool(std::ifstream& ifs)
{
	ToolBase* tool = nullptr;
	toolType tType;

	if (!ifs.good())
		throw runtime_error("file is bad cant read tool");

	ifs.read(reinterpret_cast<char*>(&tType), sizeof(toolType));

	switch (tType)
	{
	case (toolType::knight):
		tool = new Knight(this);
		break;
	case (toolType::king):
		tool = new King(this);
		break;
	case (toolType::pawn):
		tool = new Pawn(this);
		break;
	case (toolType::queen):
		tool = new Queen(this);
		break;
	case (toolType::bishop):
		tool = new Bishop(this);
		break;
	case (toolType::steeple):
		tool = new Steeple(this);
		break;
	default:
		throw runtime_error("wrong tool type in the file");
		break;
	}

	tool->readFromFile(ifs);
	return tool;
}
