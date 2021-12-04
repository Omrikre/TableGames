#pragma once
#include "ChessGameTool.h"
class King : public ChessGameTool
{
public:
	char getLetter();
	King(int row, int col, belongToPlayer pl, GameBase* game);
	King(GameBase* game);
	virtual Position* getPossibleMoves(int& size)const;
};

