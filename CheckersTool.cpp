#include "CheckersTool.h"
#include "Checkers.h"

using namespace std;

CheckersTool::CheckersTool(int row, int col, belongToPlayer player, GameBase* game)
	:ToolBase(row,col,player,game)
{
	setIfKing(false);
}

CheckersTool::CheckersTool(GameBase* game)
	: ToolBase(0, 0, belongToPlayer::notExist, game)
{
	setIfKing(false);
}

void CheckersTool::saveToFile(ofstream& ofs)
{
	ToolBase::saveToFile(ofs);
	ofs.write(reinterpret_cast<const char*>(&m_isKing), sizeof(m_isKing));
}

void CheckersTool::readFromFile(ifstream& ifs)
{
	ToolBase::readFromFile(ifs);
	ifs.read(reinterpret_cast<char*>(&m_isKing), sizeof(m_isKing));
}

char CheckersTool::getLetter()
{
	if (m_belongTo == belongToPlayer::player1)
	{
		if (m_isKing)
			return 'O';
		else
			return 'o';
	}
	else if (m_belongTo == belongToPlayer::player2)
	{
		if (m_isKing)
			return 'X';
		else
			return 'x';
	}
	else
		return ' ';
}

Position* CheckersTool::getPossibleMoves(int& size)const
{
	if (m_isKing == false)
		return getMovesForSoldier(size);
	else
		return getMovesForKing(size);
}

void CheckersTool::setIfKing(bool ifKing)
{ 
	m_isKing = ifKing; 
}

Position* CheckersTool::getMovesForKing(int& size)const
{
	Position* arr = new Position[CHECKERS_BOARDSIZE + CHECKERS_BOARDSIZE - 2];
	size = 0;
	int row, col;
	//move up left
	row = m_pos.r - 1; 
	col = m_pos.c - 1;
	//add empty places in this direction
	while (m_game->isValidPos(row, col) && m_game->getBelongToInPos(row, col) == belongToPlayer::notExist)
	{
		addToPosArr(arr, size, row, col);
		row--;
		col--;
	}
	//add eat in this direction
	if (m_game->isValidPos(row, col) && m_game->isValidPos(row - 1, col - 1) &&
		m_game->getBelongToInPos(row,col) != m_belongTo &&
		m_game->getBelongToInPos(row,col) == belongToPlayer::notExist)
	{
		addToPosArr(arr,size,row - 1, col - 1);
	}

	//move up right
	row = m_pos.r - 1;
	col = m_pos.c + 1;
	//add empty places in this direction
	while (m_game->isValidPos(row, col) && m_game->getBelongToInPos(row, col) == belongToPlayer::notExist)
	{
		addToPosArr(arr, size, row - 1, col + 1);
		row--;
		col++;
	}
	//add eat in this direction
	if (m_game->isValidPos(row, col) && m_game->isValidPos(row - 1, col + 1) &&
		m_game->getBelongToInPos(row,col) != m_belongTo &&
		m_game->getBelongToInPos(row-1,col+1) == belongToPlayer::notExist)
	{
		addToPosArr(arr, size, row - 1, col + 1);
		size++;
	}

	//move down left
	row = m_pos.r + 1;
	col = m_pos.c - 1;
	//add empty places in this direction
	while (m_game->isValidPos(row, col) && m_game->getBelongToInPos(row,col) == belongToPlayer::notExist)
	{
		addToPosArr(arr, size, row , col );
		row++;
		col--;
	}
	//add eat in this direction
	if (m_game->isValidPos(row, col) && m_game->isValidPos(row + 1, col - 1) &&
		m_game->getBelongToInPos(row,col) != m_belongTo &&
		m_game->getBelongToInPos(row,col) == belongToPlayer::notExist)
	{
		addToPosArr(arr, size, row+1, col-1);
	}
	//move down right
	row = m_pos.r + 1;
	col = m_pos.c + 1;
	//add empty places in this direction
	while (m_game->isValidPos(row, col) && m_game->getBelongToInPos(row,col) == belongToPlayer::notExist)
	{
		addToPosArr(arr, size, row , col);
		row++;
		col++;
	}
	//add eat in this direction
	if (m_game->isValidPos(row, col) && m_game->isValidPos(row + 1, col + 1) &&
		m_game->getBelongToInPos(row,col) != m_belongTo &&
		m_game->getBelongToInPos(row+1,col+1) == belongToPlayer::notExist)
	{
		addToPosArr(arr, size, row+1, col+1);
	}

	if (size == 0)
	{
		delete[] arr;
		return nullptr;
	}
	else
		return arr;
}

Position* CheckersTool::getMovesForSoldier(int& size)const
{
	Position* arr; 
	size = 0;
	if (this->m_belongTo == belongToPlayer::notExist)
	{
		return nullptr;
	}
	else if (m_belongTo == belongToPlayer::player1)
	{
		arr = new Position [2];
		//down left
		if (m_game->isValidPos(m_pos.r + 1, m_pos.c - 1))
		{
			Position downLeftTool;
			downLeftTool.r = m_pos.r + 1;
			downLeftTool.c = m_pos.c - 1;
			if (m_game->checkIfEmptyPanel(downLeftTool.r,downLeftTool.c)==true)
			{
				arr[size] = downLeftTool;
				size++;
			}
			else if (m_game->isValidPos(m_pos.r + 2, m_pos.c - 2))
			{
				Position downDownLeftTool;
				downDownLeftTool.r = m_pos.r + 2;
				downDownLeftTool.c = m_pos.c - 2;
				if (m_game->getBelongToInPos(m_pos.r+2,m_pos.c-2)==belongToPlayer::notExist && 
					m_game->getBelongToInPos(m_pos.r+1,m_pos.c-1)==belongToPlayer::player2)
				{
					arr[size] = downDownLeftTool;
					size++;
				}
			}
		}
		//down right
		if (m_game->isValidPos(m_pos.r + 1, m_pos.c + 1))
		{
			Position downRightTool;
			downRightTool.c = m_pos.c + 1;
			downRightTool.r = m_pos.r + 1;
			if (m_game->checkIfEmptyPanel(downRightTool.r,downRightTool.c)==true)
			{
				arr[size] = downRightTool;
				size++;
			}
			else if (m_game->isValidPos(downRightTool.r + 1, downRightTool.c + 1) &&
				m_game->checkIfEmptyPanel(downRightTool.r+1,downRightTool.c+1 ) )//with eating
			{
				Position downDownRightTool;
				downDownRightTool.r = downRightTool.r + 1;
				downDownRightTool.c = downRightTool.c + 1;
				if (m_game->checkIfEmptyPanel(downDownRightTool.r,downDownRightTool.c)==true &&
					m_game->getBelongToInPos(m_pos.r+1,m_pos.c+1)==belongToPlayer::player2)
				{
					arr[size] = downDownRightTool;
					size++;
				}
			}
		}
	}
	else //player 2
	{
		arr = new Position [2];

		//up left
		if (m_game->isValidPos(m_pos.r - 1, m_pos.c - 1))
		{
			Position upLeftTool;
			upLeftTool.c = m_pos.c - 1;
			upLeftTool.r = m_pos.r - 1;
			if (m_game->checkIfEmptyPanel(upLeftTool.r,upLeftTool.c)==true)
			{
				arr[size] = upLeftTool;
				size++;
			}
			else if (m_game->isValidPos(m_pos.r - 2, m_pos.c - 2))
			{
				Position upUpLeftTool;
				upUpLeftTool.r = m_pos.r - 2;
				upUpLeftTool.c = m_pos.c - 2;
				if (m_game->checkIfEmptyPanel(upUpLeftTool.r,upUpLeftTool.c)==true &&
					m_game->getBelongToInPos(upLeftTool.r,upLeftTool.c) == belongToPlayer::player1)
				{
					arr[size] = upUpLeftTool;
					size++;
				}
			}
		}
		//up right
		if (m_game->isValidPos(m_pos.r - 1, m_pos.c + 1))
		{
			Position upRightTool;
			upRightTool.c = m_pos.c + 1;
			upRightTool.r = m_pos.r - 1;
			if (m_game->checkIfEmptyPanel(upRightTool.r,upRightTool.c)==true)
			{
				arr[size] = upRightTool;
				size++;
			}
			else if (m_game->isValidPos(m_pos.r - 2, m_pos.c + 2))
			{
				Position upUpRightTool;
				upUpRightTool.r = m_pos.r - 2;
				upUpRightTool.c = m_pos.c + 2;
				if (m_game->checkIfEmptyPanel(upUpRightTool.r,upUpRightTool.c)==true &&
					m_game->getBelongToInPos(upRightTool.r,upRightTool.c)==belongToPlayer::player1)
				{
					arr[size] = upUpRightTool;
					size++;
				}
			}
		}

	}
	return arr;
}

Position* CheckersTool::getRisks(int& size)const
{
	size = 0;
	Position* arr = new Position [2];
	if (m_belongTo == belongToPlayer::player1)
	{
		if (m_game->isValidPos(m_pos.r - 1, m_pos.c + 1) == true && 
			  m_game->getBelongToInPos(m_pos.r-1,m_pos.c+1) == belongToPlayer::notExist)
		{
			if (m_game->isValidPos(m_pos.r + 1, m_pos.c - 1) == true)
			{
				if (m_game->getBelongToInPos(m_pos.r+1,m_pos.c-1) == belongToPlayer::player2)
				{
					arr[size].r = m_pos.r + 1;
					arr[size].c = m_pos.c - 1;
					size++;
				}
				else if (m_game->getBelongToInPos(m_pos.r+1,m_pos.c-1) == belongToPlayer::notExist)
				{
					/*we go until we still on the board and cheak if the king is in one of the square want to eat us*/
					int row = m_pos.r + 1;
					int col = m_pos.c - 1;
					while (m_game->isValidPos(row, col) == true &&
						m_game->getBelongToInPos(row,col) == belongToPlayer::notExist)
					{
						row++;
						col--;
					}
					if (m_game->isValidPos(row, col) == true)
					{
						if (m_game->getBelongToInPos(row,col) == belongToPlayer::player2)
						{
							if (dynamic_cast<CheckersTool&>(m_game->getGameToolInPosition(row, col)).getIfKing() == true)
							{
								arr[size].c = col;
								arr[size].r = row;
								size++;
							}
						}
					}
				}
			}
		}

		if (m_game->isValidPos(m_pos.r - 1, m_pos.c - 1) == true &&
			m_game->getGameToolInPosition(m_pos.r - 1, m_pos.c - 1).getWhoBelongTo() == belongToPlayer::notExist)
		{
			if (m_game->isValidPos(m_pos.r + 1, m_pos.c + 1) == true)
			{
				if (m_game->getGameToolInPosition(m_pos.r + 1, m_pos.c + 1).getWhoBelongTo() == belongToPlayer::player2)
				{
					//cheak if in the opposite direction have rival player and in the other direction empty tool
					arr[size].c = m_pos.c;
					arr[size].r = m_pos.r;
					size++;
				}
				else if (m_game->getGameToolInPosition(m_pos.r + 1, m_pos.c + 1).getWhoBelongTo() == belongToPlayer::notExist)
				{
					/*we go until we still on the board and cheak if the king is in one of the square want to eat us*/
					int row = m_pos.r + 1;
					int col = m_pos.c + 1;
					while (m_game->isValidPos(row, col) == true &&
						m_game->getGameToolInPosition(row, col).getWhoBelongTo() == belongToPlayer::notExist)
					{
						row++;
						col++;
					}
					if (m_game->isValidPos(row, col) == true)
					{
						if (m_game->getGameToolInPosition(row, col).getWhoBelongTo() == belongToPlayer::player2)
						{
							if (dynamic_cast<CheckersTool&>(m_game->getGameToolInPosition(row, col)).getIfKing() == true)
							{
								arr[size].c = col;
								arr[size].r = row;
								size++;
							}
						}
					}
				}
			}
		}
	}
	else // player 2
	{
		if (m_game->isValidPos(m_pos.r + 1, m_pos.c - 1) == true &&
			m_game->getGameToolInPosition(m_pos.r + 1, m_pos.c - 1).getWhoBelongTo() == belongToPlayer::notExist)
		{
			if (m_game->isValidPos(m_pos.r + 1, m_pos.c - 1) == true)
			{
				if (m_game->getGameToolInPosition(m_pos.r + 1, m_pos.c - 1).getWhoBelongTo() == belongToPlayer::player1)
				{
					arr[size].c = m_pos.c -1;
					arr[size].r = m_pos.r + 1;
					size++;
				}
				else if (m_game->getGameToolInPosition(m_pos.r + 1, m_pos.c - 1).getWhoBelongTo() == belongToPlayer::notExist)
				{
					/*we go until we still on the board and cheak if the king is in one of the square want to eat us*/
					int row = m_pos.r + 1;
					int col = m_pos.c - 1;
					while (m_game->isValidPos(row, col) == true &&
						m_game->getGameToolInPosition(row, col).getWhoBelongTo() == belongToPlayer::notExist)
					{
						row--;
						col++;
					}
					if (m_game->isValidPos(row, col) == true)
					{
						if (m_game->getGameToolInPosition(row, col).getWhoBelongTo() == belongToPlayer::player2)
						{
							if (dynamic_cast<CheckersTool&>(m_game->getGameToolInPosition(row, col)).getIfKing() == true)
							{
								arr[size].r = row;
								arr[size].c = col;
								size++;
							}
						}
					}
				}
			}
		}

		if (m_game->isValidPos(m_pos.r + 1, m_pos.c + 1) == true &&
			m_game->getGameToolInPosition(m_pos.r + 1, m_pos.c + 1).getWhoBelongTo() == belongToPlayer::notExist)
		{
			if (m_game->isValidPos(m_pos.r - 1, m_pos.c - 1) == true)
			{
				if (m_game->getGameToolInPosition(m_pos.r - 1, m_pos.c - 1).getWhoBelongTo() == belongToPlayer::player1)
				{
					arr[size].c = m_pos.c - 1;
					arr[size].r = m_pos.r - 1;
					size++;
				}
				else if (m_game->getGameToolInPosition(m_pos.r - 1, m_pos.c - 1).getWhoBelongTo() == belongToPlayer::notExist)
				{
					/*we go until we still on the board and cheak if the king is in one of the square want to eat us*/
					int row = m_pos.r - 1;
					int col = m_pos.c - 1;
					while (m_game->isValidPos(row, col) == true &&
						m_game->getGameToolInPosition(row, col).getWhoBelongTo() == belongToPlayer::notExist)
					{
						row--;
						col--;
					}
					if (m_game->isValidPos(row, col) == true)
					{
						if (m_game->getGameToolInPosition(row, col).getWhoBelongTo() == belongToPlayer::player1)
						{
							if (dynamic_cast<CheckersTool&>(m_game->getGameToolInPosition(row, col)).getIfKing() == true)
							{
								arr[size].c = col;
								arr[size].r = row;
								size++;
							}
						}
					}
				}
			}
		}
	}

	if (size == 0 )
	{
		delete[] arr;
		return nullptr;
	}
	return arr;
}

bool CheckersTool::getIfKing() const{ 
	return m_isKing; 
}

void CheckersTool::addToPosArr(Position* arr, int& size, int r, int c) const
{
	arr[size].r = r;
	arr[size].c = c;
	size++;
}