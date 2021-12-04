#include "Bishop.h"
#include "GameBase.h"
#include "ChessGameTool.h"

Bishop::Bishop(int row, int col, belongToPlayer pl, GameBase* game)
	:ChessGameTool(row, col, pl, game, toolType::bishop)
{
}
Bishop::Bishop(GameBase* game)
	: ChessGameTool(0, 0, belongToPlayer::notExist, game, toolType::bishop)
{
}

Position* Bishop::getPossibleMoves(int& size) const
{
	Position* arr = new Position[2 * m_game->getBoardSize()];
	size = 0;
	Position Down_Left;
	Down_Left.c = m_pos.c - 1;
	Down_Left.r = m_pos.r + 1;
	while (m_game->isValidPos(Down_Left.r, Down_Left.c) == true && m_game->checkIfEmptyPanel(Down_Left.r, Down_Left.c) == true)
	{
		arr[size] = Down_Left;
		size++;
		Down_Left.c--;
		Down_Left.r++;
	}

	// eating
	
	if (m_game->isValidPos(Down_Left.r, Down_Left.c) == true)
	{
		if (m_belongTo == belongToPlayer::player1 && m_game->getBelongToInPos(Down_Left.r, Down_Left.c) == belongToPlayer::player2)
		{
			addToPosArr(arr, size, Down_Left.r, Down_Left.c);
		}

		else if (m_belongTo == belongToPlayer::player2 && m_game->getBelongToInPos(Down_Left.r, Down_Left.c) == belongToPlayer::player1)
		{
			addToPosArr(arr, size, Down_Left.r, Down_Left.c);

		}
	}

	
	Position Down_Right;
	Down_Right.r = m_pos.r + 1;
	Down_Right.c = m_pos.c + 1;
	while (m_game->isValidPos(Down_Right.r, Down_Right.c) == true && m_game->checkIfEmptyPanel(Down_Right.r, Down_Right.c) == true)
	{
		arr[size] = Down_Right;
		size++;
		Down_Right.c++;
		Down_Right.r++;
	}

	//eating

	if (m_game->isValidPos(Down_Right.r, Down_Right.c) == true)
	{
		if (m_belongTo == belongToPlayer::player1 && m_game->getBelongToInPos(Down_Right.r, Down_Right.c) == belongToPlayer::player2)
		{
			addToPosArr(arr, size, Down_Right.r, Down_Right.c);
		}

		else if (m_belongTo == belongToPlayer::player2 && m_game->getBelongToInPos(Down_Right.r, Down_Right.c) == belongToPlayer::player1)
		{
			addToPosArr(arr, size, Down_Right.r, Down_Right.c);

		}
	}

	Position Up_Right;
	Up_Right.r = m_pos.r - 1;
	Up_Right.c = m_pos.c + 1;
	while (m_game->isValidPos(Up_Right.r, Up_Right.c) == true && m_game->checkIfEmptyPanel(Up_Right.r, Up_Right.c) == true)
	{
		arr[size] = Up_Right;
		size++;
		Up_Right.c++;
		Up_Right.r--;
	}

	// eating
	
	if (m_game->isValidPos(Up_Right.r, Up_Right.c) == true)
	{
		if (m_belongTo == belongToPlayer::player1 && m_game->getBelongToInPos(Up_Right.r, Up_Right.c) == belongToPlayer::player2)
		{
			addToPosArr(arr, size, Up_Right.r, Up_Right.c);
		}
		else if (m_belongTo == belongToPlayer::player2 && m_game->getBelongToInPos(Up_Right.r, Up_Right.c) == belongToPlayer::player1)
		{
			addToPosArr(arr, size, Up_Right.r, Up_Right.c);

		}
	}

	Position Up_Left;
	Up_Left.r = m_pos.r - 1;
	Up_Left.c = m_pos.c - 1;
	while (m_game->isValidPos(Up_Left.r, Up_Left.c) == true && m_game->checkIfEmptyPanel(Up_Left.r, Up_Left.c) == true)
	{
		arr[size] = Up_Left;
		size++;
		Up_Left.c--;
		Up_Left.r--;
	}

	//eating
	
	
	if (m_game->isValidPos(Up_Left.r, Up_Left.c) == true)
	{
		if (m_belongTo == belongToPlayer::player1 && m_game->getBelongToInPos(Up_Left.r, Up_Left.c) == belongToPlayer::player2)
		{
			addToPosArr(arr, size, Up_Left.r, Up_Left.c);
		}

		else if (m_belongTo == belongToPlayer::player2 && m_game->getBelongToInPos(Up_Left.r, Up_Left.c) == belongToPlayer::player1)
		{
			addToPosArr(arr, size, Up_Left.r, Up_Left.c);

		}
	}
	return arr;
}

char Bishop::getLetter()
{
	if (this->m_belongTo == belongToPlayer::player1)
		return 'r';
	else
		return 'R';
}
