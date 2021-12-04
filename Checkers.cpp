#include "Checkers.h"
#include "CheckersTool.h"
#include <iostream>

using namespace std;

Checkers::Checkers(bool bSetBoard)
	:GameBase(CHECKERS_BOARDSIZE, CHECKERS_NUMTOOLS)
{
	// set players
	//m_pl1.setNumOfTools(m_boardSize);
	//m_pl2.setNumOfTools(m_boardSize);

	// set Checkers
	m_gameOn = true;
	setTurn(belongToPlayer::player1);
	m_winner = belongToPlayer::notExist;

	// set boardw
	if (bSetBoard == true)
		setGameBoard();
	m_gType = gameType::checkers;
}

MoveResult Checkers::move()
{
	int row, col, moveRow, moveCol, size;
	cout << endl << "Please enter the row and col of the Game tool that you want to move: " << endl;
	cin >> row >> col;

	if (!checkGameToolIsValid(row, col))
	{
		cout << "not a valid position" << endl;
		return MoveResult::InvalidPosition;
	}
	// TODO check if the Game tool belong to the player that this is his turn
	if (getBelongToInPos(row, col) != getTurn())
	{
		cout << "This position does not have a tool that belongs to the current player's turn." << endl;
		return MoveResult::ToolBelongToOtherPlayer;
	}

	//get all the positions the tool can move to
	Position* possibleMovArr = getGameToolInPosition(row, col).getPossibleMoves(size);
	if (size == 0)
	{
		cout << "this tile cannot move anywhere" << endl;
		return MoveResult::NoPossibleMoves;
	}

	cout << endl << "Please enter the row and col of the panle that you want the Game tool to move to: " << endl;
	cin >> moveRow >> moveCol;
	int index = -1;
	for (int i = 0; i < size; i++)
	{
		if (moveRow == possibleMovArr[i].r && moveCol == possibleMovArr[i].c)
			index = i;
	}

	if (index == -1)
	{
		cout << "cannot move there sorry" << endl;
		delete[] possibleMovArr;
		return MoveResult::NotAPossibleMove;
	}
	else
	{
		//finally...
		//assuming that toR,toC are valid and there is nullptr there right now
		moveTool(row, col, moveRow, moveCol);
		int eatRow, eatCol;
		eatRow = moveRow > row ? moveRow - 1 : moveRow + 1;
		eatCol = moveCol > col ? moveCol - 1 : moveCol + 1;

		if (abs(row - moveRow) > 1) //yum yum
		{
			//remove this tile for the player
			if (getBelongToInPos(eatRow, eatCol) == belongToPlayer::player1)
			{
				m_pl1.removeTool(getGameToolInPosition(eatRow, eatCol));
			}
			else
			{
				m_pl2.removeTool(getGameToolInPosition(eatRow, eatCol));
			}

			removeTool(eatRow, eatCol);

			//currGame->Game->getGameToolInPosition(eatRow, eatCol).setBelongToPlayer(belongToPlayer::notExist);
			//to do - 1. set the board to be pointers to tools
			// 2. move - actually puts null in one place of the board and connects other place to the toop
			// 3. when moving a tool - set its new row and col
		}
	}

	delete[] possibleMovArr;

	if (moveRow == m_boardSize && getBelongToInPos(moveRow, moveCol) == belongToPlayer::player1)
	{
		dynamic_cast<CheckersTool&>(getGameToolInPosition(moveRow, moveCol)).setIfKing(true);
	}
	else if (moveRow == 1 && getGameToolInPosition(moveRow, moveCol).getWhoBelongTo() == belongToPlayer::player2)
	{
		dynamic_cast<CheckersTool&>(getGameToolInPosition(moveRow, moveCol)).setIfKing(true);
	}

	if (getTurn() == belongToPlayer::player1)
	{
		if (m_pl2.getNumOfTools() == 0)
		{
			setWinner(belongToPlayer::player1);
		}
		else
		{
			setTurn(belongToPlayer::player2);
		}
	}
	else
	{
		if (m_pl1.getNumOfTools() == 0)
		{
			setWinner(belongToPlayer::player2);
		}
		else
		{
			setTurn(belongToPlayer::player1);
		}
	}

	return MoveResult::Success;
}

ostream& operator<<(ostream& o, Checkers& g)
{
	o << "  ";
	for (int x = 0; x < g.m_boardSize; x++)
		o << "   " << x + 1;
	o << endl;
	o << "____";
	for (int x = 0; x < g.m_boardSize; x++)
		o << "____";
	o << endl;

	for (int i = 0; i < g.m_boardSize; i++)
	{
		o << " " << i + 1 << " |";
		for (int j = 0; j < g.m_boardSize; j++)
		{
			if (g.m_boardVec[i][j] == nullptr)
				o << "   |";
			else  
			{
				o << " " << *g.m_boardVec[i][j] << " |";
			}
		}
		o << endl;
	}

	o << endl << endl;
	return o;
}

void Checkers::printBoard() {
	cout << *this;
}

void Checkers::setGameBoard() {
	int check;
	//take care of the player 1 soldiers 
	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= m_boardSize; j++) {
			check = i + j;
			if ((i + j) % 2 == 1)
			{
				m_boardVec[i - 1][j - 1] = new CheckersTool(i, j, belongToPlayer::player1, this);
				m_pl1.addTool(*m_boardVec[i - 1][j - 1]);
			}
			else
				m_boardVec[i - 1][j - 1] = nullptr;
		}
	}
	//take care of the middle area
	for (int i = 4; i <= (m_boardSize -3); i++) {
		for (int j = 1; j <= m_boardSize; j++) {
			m_boardVec[i - 1][j - 1] = nullptr;
		}
	}
	//take care of the player 2 soldiers
	for (int i = (m_boardSize - 2); i <= m_boardSize; i++) {
		for (int j = 1; j <= m_boardSize; j++) {
			if ((i + j) % 2 == 1)
			{
				m_boardVec[i - 1][j - 1] = new CheckersTool(i, j, belongToPlayer::player2, this);
				m_pl2.addTool(*m_boardVec[i - 1][j - 1]);
			}
			else
				m_boardVec[i - 1][j - 1] = nullptr;
		}
	}
}

void Checkers::saveTool(std::ofstream& ofs, ToolBase* tool)
{
	tool->saveToFile(ofs);
}

ToolBase* Checkers::readTool(std::ifstream& ifs)
{
	if (!ifs.good())
		throw runtime_error("file is bad cant read tool");

	ToolBase* tool = new CheckersTool(this);
	tool->readFromFile(ifs);
	return tool;
}



