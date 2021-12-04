#include "Knight.h"
#include "GameBase.h"

Knight::Knight(int row, int col, belongToPlayer pl, GameBase* game)
	:ChessGameTool(row, col, pl, game, toolType::knight)
{
}

Knight::Knight(GameBase* game)
	: ChessGameTool(0, 0, belongToPlayer::notExist, game, toolType::knight)
{
}

Position* Knight::getPossibleMoves(int& size) const
{
	Position addArr[8] = { {-2,-1},{-2,1},{-1,-2},{-1,+2},{2,-1},{2,1},{1,-2},{1,+2} };
	Position* arr = new Position[m_game->getBoardSize()];
	size = 0;
	//2 stepss up 1 steps east (dir 1)
	Position movePos;
	for (int i = 0; i < 8; i++)
	{
		movePos.r = m_pos.r + addArr[i].r;
		movePos.c = m_pos.c + addArr[i].c;

		if (m_game->isValidPos(movePos.r, movePos.c) == true)
		{
			if (m_game->checkIfEmptyPanel(movePos.r, movePos.c) == true ||
				m_game->getGameToolInPosition(movePos.r, movePos.c).getWhoBelongTo() != m_belongTo)
			{
				arr[size] = movePos;
				size++;
			}
		}
	}

	return arr;
}

 char Knight::getLetter()
 {
	 if (this->m_belongTo == belongToPlayer::player1)
		 return 'h';
	 else
		 return 'H';
 }
