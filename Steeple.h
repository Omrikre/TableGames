#pragma once
#include "ChessGameTool.h"
class Steeple : public ChessGameTool
{
public:
	char getLetter();
	Steeple(int row, int col, belongToPlayer pl, GameBase* game);
	Steeple(GameBase* game);
	virtual Position* getPossibleMoves(int& size)const;
};
