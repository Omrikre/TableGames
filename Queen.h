#pragma once
#include "ChessGameTool.h"
class Queen : public ChessGameTool
{
public:
	char getLetter();
	Queen(int row, int col, belongToPlayer pl, GameBase* game);
	Queen(GameBase* game);
	virtual Position* getPossibleMoves(int& size)const;
};

