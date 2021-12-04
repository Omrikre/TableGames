#pragma once
#include "ChessGameTool.h"
class Bishop  : public ChessGameTool
{
public:
	char getLetter();
	Bishop(int row, int col, belongToPlayer pl, GameBase* game);
	Bishop(GameBase* game);
	virtual Position* getPossibleMoves(int& size)const;
};

