#include "Steeple.h"
#include "GameBase.h"

Steeple::Steeple(int row, int col, belongToPlayer pl, GameBase* game)
	:ChessGameTool(row, col, pl, game, toolType::steeple)
{
}

Steeple::Steeple(GameBase* game)
	: ChessGameTool(0, 0, belongToPlayer::notExist, game, toolType::steeple)
{
}

Position* Steeple::getPossibleMoves(int& size) const

{
	Position* arr = new Position[2 * m_game->getBoardSize()];
	size = 0;
	Position East;
	East.r = m_pos.r;
	East.c = m_pos.c + 1;
	while (m_game->isValidPos(East.r, East.c) == true && m_game->checkIfEmptyPanel(East.r, East.c) == true)
	{
		arr[size] = East;
		size++;
		East.c++;
	}

	//eating
	
	if (m_game->isValidPos(East.r, East.c) == true)
	{
		if (m_belongTo == belongToPlayer::player1 && m_game->getBelongToInPos(East.r, East.c) == belongToPlayer::player2)
		{
			addToPosArr(arr, size, East.r, East.c);
		}
		else if (m_belongTo == belongToPlayer::player2 && m_game->getBelongToInPos(East.r, East.c) == belongToPlayer::player1)
		{
			addToPosArr(arr, size, East.r, East.c);
		}
	}
	
	Position West;
	West.r = m_pos.r;
	West.c = m_pos.c - 1;
	while (m_game->isValidPos(West.r, West.c) == true && m_game->checkIfEmptyPanel(West.r, West.c) == true)
	{
		arr[size] = West;
		size++;
		West.c--;
	}

	//eating

	if (m_game->isValidPos(West.r, West.c) == true)
	{
		if (m_belongTo == belongToPlayer::player1 && m_game->getBelongToInPos(West.r, West.c) == belongToPlayer::player2)
		{
			addToPosArr(arr, size, West.r, West.c);
		}
		else if (m_belongTo == belongToPlayer::player2 && m_game->getBelongToInPos(West.r, West.c) == belongToPlayer::player1)
		{
			addToPosArr(arr, size, West.r, West.c);
		}
	}


	Position Up;
	Up.c = m_pos.c;
	Up.r = m_pos.r - 1;
	while (m_game->isValidPos(Up.r, Up.c) == true && m_game->checkIfEmptyPanel(Up.r, Up.c) == true)
	{
		arr[size] = Up;
		size++;
		Up.r--;
	}

	//eating

	if (m_game->isValidPos(Up.r, Up.c) == true)
	{
		if (m_belongTo == belongToPlayer::player1 && m_game->getBelongToInPos(Up.r, Up.c) == belongToPlayer::player2)
		{
			addToPosArr(arr, size, Up.r, Up.c);
		}
		else if (m_belongTo == belongToPlayer::player2 && m_game->getBelongToInPos(Up.r, Up.c) == belongToPlayer::player1)
		{
			addToPosArr(arr, size, Up.r, Up.c);
		}
	}
	

	Position Down;
	Down.c = m_pos.c;
	Down.r = m_pos.r + 1;
	while (m_game->isValidPos(Down.r, Down.c) == true && m_game->checkIfEmptyPanel(Down.r, Down.c) == true)
	{
		arr[size] = Down;
		size++;
		Down.r++;
	}

	//eating
	if (m_game->isValidPos(Down.r, Down.c) == true)
	{
		if (m_belongTo == belongToPlayer::player1 && m_game->getBelongToInPos(Down.r, Down.c) == belongToPlayer::player2)
		{
			addToPosArr(arr, size, Down.r, Down.c);
		}
		else if (m_belongTo == belongToPlayer::player2 && m_game->getBelongToInPos(Down.r, Down.c) == belongToPlayer::player1)
		{
			addToPosArr(arr, size, Down.r, Down.c);
		}
	}

	return arr;
}

char Steeple::getLetter()
{
	if (this->m_belongTo == belongToPlayer::player1)
		return 's';
	else
		return 'S';
}