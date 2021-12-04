#include "King.h"
#include "GameBase.h"

King::King(int row, int col, belongToPlayer pl, GameBase* game)
	:ChessGameTool(row, col, pl, game, toolType::king)
{
}

King::King(GameBase* game)
	: ChessGameTool(0, 0, belongToPlayer::notExist, game, toolType::king)
{
}

Position* King::getPossibleMoves(int& size) const
{
	Position* arr = new Position[m_game->getBoardSize()];
	size = 0;
	//1 stepss up 1 steps east (dir 1)
	Position One_Up_One_East;
	One_Up_One_East.r = m_pos.r - 1;
	One_Up_One_East.c = m_pos.c + 1;
	if (m_game->isValidPos(One_Up_One_East.r, One_Up_One_East.c) == true && m_game->checkIfEmptyPanel(One_Up_One_East.r, One_Up_One_East.c) == true)
	{
		arr[size] = One_Up_One_East;
		size++;
	}
	//eating
	else if (m_game->isValidPos(One_Up_One_East.r, One_Up_One_East.c) == true)
	{
		if (m_belongTo == belongToPlayer::player2 && m_game->getBelongToInPos(One_Up_One_East.r, One_Up_One_East.c) == belongToPlayer::player1
			|| m_belongTo == belongToPlayer::player1 && m_game->getBelongToInPos(One_Up_One_East.r, One_Up_One_East.c) == belongToPlayer::player2)
		{
			addToPosArr(arr, size, One_Up_One_East.r, One_Up_One_East.c);
		}

	}
	//1 steps up 1 steps west (dir 2)
	Position One_Up_One_West;
	One_Up_One_West.r = m_pos.r - 1;
	One_Up_One_West.c = m_pos.c - 1;
	if (m_game->isValidPos(One_Up_One_West.r, One_Up_One_West.c) == true && m_game->checkIfEmptyPanel(One_Up_One_West.r, One_Up_One_West.c) == true)
	{
		arr[size] = One_Up_One_West;
		size++;
	}
	else if (m_game->isValidPos(One_Up_One_West.r, One_Up_One_West.c) == true)
	{
		if (m_belongTo == belongToPlayer::player2 && m_game->getBelongToInPos(One_Up_One_West.r, One_Up_One_West.c) == belongToPlayer::player1
			|| m_belongTo == belongToPlayer::player1 && m_game->getBelongToInPos(One_Up_One_West.r, One_Up_One_West.c) == belongToPlayer::player2)
		{
			addToPosArr(arr, size, One_Up_One_West.r, One_Up_One_West.c);
		}

	}
	//1 steps down 1 steps east (dir 3)
	Position One_Down_One_East;
	One_Down_One_East.r = m_pos.r + 1;
	One_Down_One_East.c = m_pos.c + 1;
	if (m_game->isValidPos(One_Down_One_East.r, One_Down_One_East.c) == true && m_game->checkIfEmptyPanel(One_Down_One_East.r, One_Down_One_East.c) == true)
	{
		arr[size] = One_Down_One_East;
		size++;
	}
	else if (m_game->isValidPos(One_Down_One_East.r, One_Down_One_East.c) == true)
	{
		if (m_belongTo == belongToPlayer::player2 && m_game->getBelongToInPos(One_Down_One_East.r, One_Down_One_East.c) == belongToPlayer::player1
			|| m_belongTo == belongToPlayer::player1 && m_game->getBelongToInPos(One_Down_One_East.r, One_Down_One_East.c) == belongToPlayer::player2)
		{
			addToPosArr(arr, size, One_Down_One_East.r, One_Down_One_East.c);
		}
	}
	//1 steps down 1 steps west (dir 4)
	Position One_Down_One_West;
	One_Down_One_West.r = m_pos.r + 1;
	One_Down_One_West.c = m_pos.c - 1;
	if (m_game->isValidPos(One_Down_One_West.r, One_Down_One_West.c) == true && m_game->checkIfEmptyPanel(One_Down_One_West.r, One_Down_One_West.c) == true)
	{
		arr[size] = One_Down_One_West;
		size++;
	}
	else if (m_game->isValidPos(One_Down_One_West.r, One_Down_One_West.c) == true)
	{
		if (m_belongTo == belongToPlayer::player2 && m_game->getBelongToInPos(One_Down_One_West.r, One_Down_One_West.c) == belongToPlayer::player1
			|| m_belongTo == belongToPlayer::player1 && m_game->getBelongToInPos(One_Down_One_West.r, One_Down_One_West.c) == belongToPlayer::player2)
		{
			addToPosArr(arr, size, One_Down_One_West.r + 1, One_Down_One_West.c - 1);
		}
	}
	// 1 step up (dir 5)
	Position Up;
	Up.r = m_pos.r - 1;
	Up.c = m_pos.c;
	if (m_game->isValidPos(Up.r, Up.c) == true && m_game->checkIfEmptyPanel(Up.r, Up.c) == true)
	{
		arr[size] = Up;
		size++;
	}
	else if (m_game->isValidPos(Up.r, Up.c) == true)
	{
		if (m_belongTo == belongToPlayer::player2 && m_game->getBelongToInPos(Up.r, Up.c) == belongToPlayer::player1
			|| m_belongTo == belongToPlayer::player1 && m_game->getBelongToInPos(Up.r, Up.c) == belongToPlayer::player2)
		{
			addToPosArr(arr, size, Up.r, Up.c);
		}

	}
	// 1 step down(dir 6)
	Position Down;
	Down.r = m_pos.r + 1;
	Down.c = m_pos.c;
	if (m_game->isValidPos(Down.r, Down.c) == true && m_game->checkIfEmptyPanel(Down.r, Down.c) == true)
	{
		arr[size] = Down;
		size++;
	}
	else if (m_game->isValidPos(Down.r, Down.c) == true)
	{
		if (m_belongTo == belongToPlayer::player2 && m_game->getBelongToInPos(Down.r, Down.c) == belongToPlayer::player1
			|| m_belongTo == belongToPlayer::player1 && m_game->getBelongToInPos(Down.r, Down.c) == belongToPlayer::player2)
		{
			addToPosArr(arr, size, Down.r, Down.c);
		}
	}
	//1 steps east (dir 7)
	Position East;
	East.r = m_pos.r;
	East.c = m_pos.c + 1;
	if (m_game->isValidPos(East.r, East.c) == true && m_game->checkIfEmptyPanel(East.r, East.c) == true)
	{
		arr[size] = East;
		size++;
	}
	else if (m_game->isValidPos(East.r, East.c) == true)
	{
		if (m_belongTo == belongToPlayer::player2 && m_game->getBelongToInPos(East.r, East.c) == belongToPlayer::player1
			|| m_belongTo == belongToPlayer::player1 && m_game->getBelongToInPos(East.r, East.c) == belongToPlayer::player2)
		{
			addToPosArr(arr, size, East.r, East.c);
		}
	}
	//2 steps east 1 step down (dir 8)
	Position West;
	West.r = m_pos.r;
	West.c = m_pos.c - 1;
	if (m_game->isValidPos(West.r, West.c) == true && m_game->checkIfEmptyPanel(West.r, West.c) == true)
	{
		arr[size] = West;
		size++;
	}
	else if (m_game->isValidPos(West.r, West.c) == true)
	{
		if (m_belongTo == belongToPlayer::player2 && m_game->getBelongToInPos(West.r, West.c) == belongToPlayer::player1
			|| m_belongTo == belongToPlayer::player1 && m_game->getBelongToInPos(West.r, West.c) == belongToPlayer::player2)
		{
			addToPosArr(arr, size, West.r, West.c);
		}

	}
	return arr;
}

char King::getLetter()
{
	if (this->m_belongTo == belongToPlayer::player1)
		return 'k';
	else
		return 'K';
}