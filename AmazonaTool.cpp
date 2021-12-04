#include "AmazonaTool.h"
#include "GameBase.h"

using namespace std;

AmazonaTool::AmazonaTool(int row, int col, belongToPlayer pl,GameBase* game)
	:ToolBase(row, col, pl, game)
{
}

AmazonaTool::AmazonaTool(GameBase* game)
	:ToolBase(0, 0, belongToPlayer::notExist, game)
{
}

void AmazonaTool::addToPosArr(Position* arr, int& size, int r, int c) const
{
	arr[size].r = r;
	arr[size].c = c;
	size++;
}

Position* AmazonaTool::getMovesForAmazona(int& size)const
{
	Position*arr = new Position [m_game->getBoardSize() * 4];
	size = 0;
	int row, col;
	//move up left (1)
	row = m_pos.r - 1; 
	col = m_pos.c - 1;
	//add empty places in this direction
	while (m_game->isValidPos(row,col) && m_game->getBelongToInPos(row, col) == belongToPlayer::notExist)
	{
		addToPosArr(arr, size, row, col);
		row--;
		col--;
	}

	//move up right (2)
	row = m_pos.r - 1;
	col = m_pos.c + 1;
	//add empty places in this direction
	while (m_game->isValidPos(row, col) && m_game->getBelongToInPos(row, col) == belongToPlayer::notExist)
	{
		addToPosArr(arr, size, row, col);
		row--;
		col++;
	}
	
	//move down left (3)
	row = m_pos.r + 1;
	col = m_pos.c - 1;
	//add empty places in this direction
	while (m_game->isValidPos(row, col) && m_game->getBelongToInPos(row, col) == belongToPlayer::notExist)
	{
		addToPosArr(arr, size, row, col);
		row++;
		col--;
	}
	
	//move down right (4)
	row = m_pos.r + 1;
	col = m_pos.c + 1;
	
	//add empty places in this direction

	while (m_game->isValidPos(row, col) && m_game->getBelongToInPos(row, col) == belongToPlayer::notExist)
	{
		addToPosArr(arr, size, row, col);
		row++;
		col++;
	}
	//move down down (5)
	row = m_pos.r + 1;
	col = m_pos.c;
	while (m_game->isValidPos(row, col) && m_game->getBelongToInPos(row, col) == belongToPlayer::notExist)
	{
		addToPosArr(arr, size, row, col);
		row++;
	}

	//move up up (6)
	row = m_pos.r - 1;
	col = m_pos.c;
	while (m_game->isValidPos(row, col) && m_game->getBelongToInPos(row, col) == belongToPlayer::notExist)
	{
		addToPosArr(arr, size, row, col);
		row--;
	}

	//move east (7)
	row = m_pos.r;
	col = m_pos.c + 1;
	while (m_game->isValidPos(row, col) && m_game->getBelongToInPos(row, col) == belongToPlayer::notExist)
	{
		addToPosArr(arr, size, row, col);
		col++;
	}

	//move west (8)
	row = m_pos.r;
	col = m_pos.c - 1;
	while (m_game->isValidPos(row, col) && m_game->getBelongToInPos(row, col) == belongToPlayer::notExist)
	{
		addToPosArr(arr, size, row, col);
		col--;
	}

	if (size == 0) //means that we cant move
	{
		delete[] arr;
		return nullptr;
	}
	else
		return arr;
}

Position* AmazonaTool::getMovesForArrow(int& size)const
{
	return getMovesForAmazona(size);
}

char AmazonaTool::getLetter()
{
	if (m_belongTo == belongToPlayer::notExist)
		return ' ';
	else if (m_belongTo == belongToPlayer::burned)
		return '#';
	else if (m_belongTo == belongToPlayer::player1)
		return '0';
	else
		return 'X';
}

Position* AmazonaTool::getRisks(int& size)const
{
	if (m_belongTo != belongToPlayer::notExist)
	{
		size = 0;
		return nullptr;
	}
	else
	{
		return  getMovesForArrow(size);
	}
}

Position* AmazonaTool::getPossibleMoves(int& size)const
{
	return getMovesForAmazona(size);
}
