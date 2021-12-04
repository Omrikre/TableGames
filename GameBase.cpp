#include "GameBase.h"
#include "ToolBase.h"
#include <iostream>

using namespace std;

GameBase::GameBase(int boardSize,int numPlayerTools)
	:m_pl1(numPlayerTools),m_pl2(numPlayerTools)
{
	m_boardSize = boardSize;
	allocateBoard();
}

GameBase::~GameBase()
{
	deallocateBoard();
}

void GameBase::readFromFile(ifstream& ifs)
{
	ifs.read(reinterpret_cast<char*>(&m_boardSize), sizeof(m_boardSize));
	ifs.read(reinterpret_cast<char*>(&m_gameOn), sizeof(m_gameOn));
	ifs.read(reinterpret_cast<char*>(&m_turn), sizeof(m_turn));
	ifs.read(reinterpret_cast<char*>(&m_winner), sizeof(m_winner));
	m_pl1.readFromFile(ifs);
	m_pl2.readFromFile(ifs);
	readBoardFromFile(ifs);
}

void GameBase::freePartOfBoard(int r, int c)
{
	//free all the tools that were created until position r and c 

	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < m_boardSize; j++)
		{
			delete m_boardVec[i][j];
		}
	}
	for (int j = 0; j < c; j++)
	{
		delete m_boardVec[r][j];
	}
}

void GameBase::readBoardFromFile(ifstream& ifs)
{
	bool bIsTool;
	for (int i = 0; i < m_boardSize; i++)
	{
		for (int j = 0; j < m_boardSize; j++)
		{
			ifs.read(reinterpret_cast<char*>(&bIsTool), sizeof(bIsTool));

			if (bIsTool == false)
			{
				m_boardVec[i][j] = nullptr;
			}
			else
			{
				try
				{
					m_boardVec[i][j] = readTool(ifs);
				}
				catch (runtime_error& error)
				{
					freePartOfBoard(i, j);
					throw error;
				}

				if (m_boardVec[i][j]->getWhoBelongTo() == belongToPlayer::player1)
					m_pl1.addTool(*m_boardVec[i][j]);
				else if (m_boardVec[i][j]->getWhoBelongTo() == belongToPlayer::player2)
					m_pl2.addTool(*m_boardVec[i][j]);
				else
				{
					freePartOfBoard(i, j + 1);
					throw runtime_error("the file has bad data in it");
				}
			}
		}
	}
}

void GameBase::saveToFile(ofstream& ofs)
{
	if (!ofs.good())
		throw runtime_error("something in the file is bad.");
	ofs.write(reinterpret_cast<const char*>(&m_boardSize), sizeof(m_boardSize));
	ofs.write(reinterpret_cast<const char*>(&m_gameOn), sizeof(m_gameOn));
	ofs.write(reinterpret_cast<const char*>(&m_turn), sizeof(m_turn));
	ofs.write(reinterpret_cast<const char*>(&m_winner), sizeof(m_winner));
	m_pl1.saveToFile(ofs);
	m_pl2.saveToFile(ofs);
	saveBoardToFile(ofs);
}

void GameBase::saveBoardToFile(ofstream& ofs)
{
	bool bIsTool;
	for (int i = 0; i < m_boardSize; i++)
	{
		for (int j = 0; j < m_boardSize; j++)
		{
			if (m_boardVec[i][j] == nullptr)
			{
				bIsTool = false;
				ofs.write(reinterpret_cast<const char*>(&bIsTool), sizeof(bIsTool));
			}
			else
			{
				bIsTool = true;
				ofs.write(reinterpret_cast<const char*>(&bIsTool), sizeof(bIsTool));
				//TODO - add save to file for tools and do the save
				saveTool(ofs,m_boardVec[i][j]);
			}
		}
	}
}

bool GameBase::checkGameToolIsValid(int row, int col)
{
	if (isValidPos(row, col) == false) {
		cout << endl << "-- Not in board range! --" << endl;
		return false;
	}
	else if (checkIfEmptyPanel(row, col)) {
		cout << endl << "-- The panel is empty! --" << endl;
		return false;
	}
	else
		return true;
}

void GameBase::allocateBoard()
{
	//allocates memory for the board. sets all the gametool pointers to null.
	//the derived classes should create the gameTools and put them in the 
	//correct positions to start the game
	m_boardVec.resize(m_boardSize); 

	for (int row = 0; row < m_boardSize; row++)
	{
		m_boardVec[row].resize(m_boardSize);
		for (int col = 0; col < m_boardSize; col++)
		{
			m_boardVec[row][col] = nullptr;
		}
	}
}

void GameBase::deallocateBoard()
{
	//deallocates memory for the board. 
	//the derived classes should delete the gameTools themselves 
	//no need to do anything here because we changed it to vector

}

void GameBase::setTurn(belongToPlayer pl)
{
	m_turn = pl;
}

Player& GameBase::getPlayer1()
{
	return m_pl1;
}

Player& GameBase::getPlayer2()
{
	return m_pl2;
}

belongToPlayer GameBase::getTurn() const
{
	return m_turn;
}

bool GameBase::getGameOn() const
{
	return m_gameOn;
}


ToolBase& GameBase::getGameToolInPosition(int row, int col)
{
	return *m_boardVec[row - 1][col - 1];
}

bool GameBase::isValidPos(int row, int col)
{
	if (row < 1 || col < 1 || row > m_boardSize || col > m_boardSize)
		return false;
	else
		return true;	
}

void GameBase::moveTool(int fromR, int fromC, int toR, int toC)
{
	//assuming that toR,toC are valid and there is nullptr there right now
	m_boardVec[toR - 1][toC - 1] = m_boardVec[fromR - 1][fromC - 1];
	m_boardVec[toR - 1][toC - 1]->setPos(toR, toC);
	m_boardVec[fromR - 1][fromC - 1] = nullptr;
}

belongToPlayer GameBase::getBelongToInPos(int r, int c)
{
	if (m_boardVec[r - 1][c - 1] == nullptr)
		return belongToPlayer::notExist;
	else
		return m_boardVec[r - 1][c - 1]->getWhoBelongTo();
}

void GameBase::removeTool(int r, int c)
{
	delete m_boardVec[r - 1][c - 1];
	m_boardVec[r - 1][c - 1] = nullptr; //remove the square
}

bool GameBase::checkIfEmptyPanel(int row, int col) {
	return (m_boardVec[row - 1][col - 1] == nullptr);

};

belongToPlayer GameBase::getWinner() const
{
	return m_winner;
}

void GameBase::setWinner(belongToPlayer pl)
{
	m_winner = pl;
	if (pl != belongToPlayer::notExist)
	{
		m_gameOn = false;
	}
}

void GameBase::printTurn() {
	belongToPlayer tempBelong = getTurn();
	if (tempBelong == belongToPlayer::player1)
		cout << "Player 1";
	else
		cout << "Player 2";
}
