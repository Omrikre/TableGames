#pragma once
#include "ToolBase.h"
#include <iostream>

class AmazonaTool: public ToolBase
{
private:
	void addToPosArr(Position* arr, int& size, int r, int c) const;
	Position* getMovesForArrow(int& size)const;
	Position* getMovesForAmazona(int& size)const;
public:
	AmazonaTool(int row, int col, belongToPlayer pl, GameBase* game);
	AmazonaTool(GameBase* game);

	virtual Position* getPossibleMoves(int& size)const;
	virtual char getLetter();
	virtual Position* getRisks(int& size)const;
};

