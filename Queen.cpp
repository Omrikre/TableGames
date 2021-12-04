#include "Queen.h"
#include "ChessGameTool.h"
#include "GameBase.h"

Queen::Queen(int row, int col, belongToPlayer pl, GameBase* game)
	:ChessGameTool(row, col, pl, game, toolType::queen)
{
}

Queen::Queen(GameBase* game)
	: ChessGameTool(0, 0, belongToPlayer::notExist, game, toolType::queen)
{
}

Position* Queen::getPossibleMoves(int& size) const
{
	Position* arr = new Position[m_game->getBoardSize() * 4];
	size = 0;
	int row, col;
	//move up left (1)
	row = m_pos.r - 1;
	col = m_pos.c - 1;
	//add empty places in this direction
	while (m_game->isValidPos(row, col) == true && m_game->checkIfEmptyPanel(row, col) == true)
	{
		addToPosArr(arr, size, row, col);
		row--;
		col--;
	}
	if (m_game->isValidPos(row, col) == true)
	{
		if (m_belongTo == belongToPlayer::player1 && m_game->getBelongToInPos(row, col) == belongToPlayer::player2)
		{
			addToPosArr(arr, size, row, col);
		}
		else if (m_belongTo == belongToPlayer::player2 && m_game->getBelongToInPos(row, col) == belongToPlayer::player1)
		{
			addToPosArr(arr, size, row, col);
		}
	}

	//move up right (2)
	row = m_pos.r - 1;
	col = m_pos.c + 1;
	//add empty places in this direction
	while (m_game->isValidPos(row, col) == true && m_game->checkIfEmptyPanel(row, col) == true)
	{
		addToPosArr(arr, size, row, col);
		row--;
		col++;
	}

	if (m_game->isValidPos(row, col) == true)
	{
		if (m_belongTo == belongToPlayer::player1 && m_game->getBelongToInPos(row, col) == belongToPlayer::player2)
		{
			addToPosArr(arr, size, row, col);
		}
		else if (m_belongTo == belongToPlayer::player2 && m_game->getBelongToInPos(row, col) == belongToPlayer::player1)
		{
			addToPosArr(arr, size, row, col);
		}
	}

	//move down left (3)
	row = m_pos.r + 1;
	col = m_pos.c - 1;
	//add empty places in this direction
	while (m_game->isValidPos(row, col) == true && m_game->checkIfEmptyPanel(row, col) == true)

	{
		addToPosArr(arr, size, row, col);
		row++;
		col--;
	}
	if (m_game->isValidPos(row, col) == true)
	{
		if (m_belongTo == belongToPlayer::player1 && m_game->getBelongToInPos(row, col) == belongToPlayer::player2)
		{
			addToPosArr(arr, size, row, col);
		}
		else if (m_belongTo == belongToPlayer::player2 && m_game->getBelongToInPos(row, col) == belongToPlayer::player1)
		{
			addToPosArr(arr, size, row, col);
		}
	}


	//move down right (4)
	row = m_pos.r + 1;
	col = m_pos.c + 1;

	//add empty places in this direction

	while (m_game->isValidPos(row, col) == true && m_game->checkIfEmptyPanel(row, col) == true)

	{
		addToPosArr(arr, size, row, col);
		row++;
		col++;
	}

	if (m_game->isValidPos(row, col) == true)
	{
		if (m_belongTo == belongToPlayer::player1 && m_game->getBelongToInPos(row, col) == belongToPlayer::player2)
		{
			addToPosArr(arr, size, row, col);
		}
		else if (m_belongTo == belongToPlayer::player2 && m_game->getBelongToInPos(row, col) == belongToPlayer::player1)
		{
			addToPosArr(arr, size, row, col);
		}
	}

	//move down down (5)
	row = m_pos.r + 1;
	col = m_pos.c;
	while (m_game->isValidPos(row, col) == true && m_game->checkIfEmptyPanel(row, col) == true)

	{
		addToPosArr(arr, size, row, col);
		row++;
	}
	//eating
	if (m_game->isValidPos(row, col) == true)
	{
		if (m_belongTo == belongToPlayer::player1 && m_game->getBelongToInPos(row, col) == belongToPlayer::player2)
		{
			addToPosArr(arr, size, row, col);
		}
		else if (m_belongTo == belongToPlayer::player2 && m_game->getBelongToInPos(row, col) == belongToPlayer::player1)
		{
			addToPosArr(arr, size, row, col);
		}
	}


	//move up up (6)
	row = m_pos.r - 1;
	col = m_pos.c;
	while (m_game->isValidPos(row, col) == true && m_game->checkIfEmptyPanel(row, col) == true)
	{
		addToPosArr(arr, size, row, col);
		row--;
	}
	//eating
	if (m_game->isValidPos(row, col) == true)
	{
		if (m_belongTo == belongToPlayer::player1 && m_game->getBelongToInPos(row, col) == belongToPlayer::player2)
		{
			addToPosArr(arr, size, row, col);
		}
		else if (m_belongTo == belongToPlayer::player2 && m_game->getBelongToInPos(row, col) == belongToPlayer::player1)
		{
			addToPosArr(arr, size, row, col);
		}
	}

	//move east (7)
	row = m_pos.r;
	col = m_pos.c + 1;
	while (m_game->isValidPos(row, col) == true && m_game->checkIfEmptyPanel(row, col) == true)

	{
		addToPosArr(arr, size, row, col);
		col++;
	}


	if (m_game->isValidPos(row, col) == true)
	{
		if (m_belongTo == belongToPlayer::player1 && m_game->getBelongToInPos(row, col) == belongToPlayer::player2)
		{
			addToPosArr(arr, size, row, col);
		}
		else if (m_belongTo == belongToPlayer::player2 && m_game->getBelongToInPos(row, col) == belongToPlayer::player1)
		{
			addToPosArr(arr, size, row, col);
		}
	}


	//move west (8)
	row = m_pos.r;
	col = m_pos.c - 1;
	while (m_game->isValidPos(row, col) == true && m_game->checkIfEmptyPanel(row, col) == true)

	{
		addToPosArr(arr, size, row, col);
		col--;
	}

	if (m_game->isValidPos(row, col) == true)
	{
		if (m_belongTo == belongToPlayer::player1 && m_game->getBelongToInPos(row, col) == belongToPlayer::player2)
		{
			addToPosArr(arr, size, row, col);
		}
		else if (m_belongTo == belongToPlayer::player2 && m_game->getBelongToInPos(row, col) == belongToPlayer::player1)
		{
			addToPosArr(arr, size, row, col);
		}
	}


	if (size == 0) //means that we cant move
	{
		delete[] arr;
		return nullptr;
	}
	else
		return arr;
}

char Queen::getLetter()
{
	if (this->m_belongTo == belongToPlayer::player1)
		return 'q';
	else
		return 'Q';
}

