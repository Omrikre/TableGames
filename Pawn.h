#pragma once
#include "ChessGameTool.h"

class Pawn : public ChessGameTool
{
public:
	char getLetter();
	Pawn(int row, int col, belongToPlayer pl, GameBase* game);
	Pawn(GameBase* game);
	virtual Position* getPossibleMoves(int& size)const;
};

