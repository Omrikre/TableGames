#include "ChessGameTool.h"
#include "GameBase.h"
using namespace std;

void ChessGameTool::addToPosArr(Position* arr, int& size, int r, int c) const
{
	arr[size].r = r;
	arr[size].c = c;
	size++;
}

ToolBase** ChessGameTool::getOpponentTools(int& size) const
{
	ToolBase** arr;
	if (m_belongTo == belongToPlayer::player1)
	{
		arr = m_game->getPlayer2().getToolArr();
		size = m_game->getPlayer2().getNumOfTools();
	}
	else
	{
		arr = m_game->getPlayer1().getToolArr();
		size = m_game->getPlayer1().getNumOfTools();
	}
	return arr;
}

Position* ChessGameTool::getRisks(int& size)const
{
	Position* arr = new Position[16];
	size = 0;
	ToolBase** opponentTools;
	int opponentSize;
	Position* moves;
	int movesSize;

	opponentTools = getOpponentTools(opponentSize);
	for (int i = 0; i < opponentSize; i++)
	{
		moves = opponentTools[i]->getPossibleMoves(movesSize);
		for (int j = 0; j < movesSize; j++)
		{
			if (moves[j].r == this->m_pos.r && moves[j].c == this->m_pos.c)
			{
				Position pos;
				pos.r = opponentTools[i]->getRow();
				pos.c = opponentTools[i]->getCol();
				arr[size] = pos;
				size++;
			}
		}
		delete[] moves;
	}

	return arr;
}

ChessGameTool::ChessGameTool(int row, int col, belongToPlayer pl, GameBase* game, toolType tType) 
	:ToolBase( row,col,pl,game),m_tType(tType)
{
}
/*
ChessGameTool::ChessGameTool() 
	: ToolBase(0, 0, belongToPlayer::notExist, nullptr)
{
}
*/
ChessGameTool::ChessGameTool(GameBase* game, toolType tType)
	:ToolBase(0, 0, belongToPlayer::notExist, game), m_tType(tType)
{
}

ChessGameTool::~ChessGameTool() {
	 //nothing to do here we fullfil it for the foture
 }
