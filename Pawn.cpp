#include "Pawn.h"
#include "GameBase.h"

Pawn::Pawn(int row, int col, belongToPlayer pl, GameBase* game)
	:ChessGameTool(row, col, pl, game, toolType::pawn)
{
}

Pawn::Pawn(GameBase* game)
	: ChessGameTool(0, 0, belongToPlayer::notExist, game, toolType::pawn)
{
}

Position* Pawn::getPossibleMoves(int& size)const
{
	Position* arr = new Position[4];
	size = 0;
	if (m_belongTo == belongToPlayer::player1)
	{
		Position pos;
		pos.c = m_pos.c;
		pos.r = m_pos.r + 1;
		if (m_game->isValidPos(pos.r, pos.c) == true && m_game->checkIfEmptyPanel(pos.r, pos.c) == true)
		{
			arr[size] = pos;
			size++;
		}

		//eating
		pos.r = m_pos.r + 1;
		pos.c = m_pos.c + 1;
		if (m_game->isValidPos(pos.r, pos.c) == true && m_game->checkIfEmptyPanel(pos.r, pos.c) == false && 
			m_game->getBelongToInPos(pos.r, pos.c) == belongToPlayer::player2)
		{
			addToPosArr(arr, size, pos.r, pos.c);
		}

		pos.r = m_pos.r + 1;
		pos.c = m_pos.c - 1;
		if (m_game->isValidPos(pos.r, pos.c) == true && m_game->checkIfEmptyPanel(pos.r, pos.c) == false &&
			m_game->getBelongToInPos(pos.r, pos.c) == belongToPlayer::player2)
		{
			addToPosArr(arr, size, pos.r, pos.c);
		}
	}
	else //player 2 
	{
		Position pos;
		pos.c = m_pos.c;
		pos.r = m_pos.r - 1;
		if (m_game->isValidPos(pos.r, pos.c) == true && m_game->checkIfEmptyPanel(pos.r, pos.c) == true)
		{
			arr[size] = pos;
			size++;
		}

		//eating
		pos.r = m_pos.r - 1;
		pos.c = m_pos.c + 1;
		if (m_game->isValidPos(pos.r, pos.c) == true && m_game->checkIfEmptyPanel(pos.r, pos.c) == false &&
			m_game->getBelongToInPos(pos.r, pos.c) == belongToPlayer::player1)
		{
			addToPosArr(arr, size, pos.r, pos.c);
		}

		pos.r = m_pos.r - 1;
		pos.c = m_pos.c - 1;
		if (m_game->isValidPos(pos.r, pos.c) == true && m_game->checkIfEmptyPanel(pos.r, pos.c) == false &&
			m_game->getBelongToInPos(pos.r, pos.c) == belongToPlayer::player1)
		{
			addToPosArr(arr, size, pos.r, pos.c);
		}
	}
	return arr;
}

char Pawn::getLetter()
{
	if (this->m_belongTo == belongToPlayer::player1)
		return 'p';
	else
		return 'P';
}
