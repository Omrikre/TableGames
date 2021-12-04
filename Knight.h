#pragma once
#include "ChessGameTool.h"
class Knight : public ChessGameTool
{
public:
	char getLetter();
	Knight(int row, int col, belongToPlayer pl, GameBase* game);
	Knight(GameBase* game);
	virtual Position* getPossibleMoves(int& size)const;
};

