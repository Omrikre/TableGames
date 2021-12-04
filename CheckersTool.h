#pragma once
#include "ToolBase.h"

class CheckersTool :public ToolBase
{
private:
	bool m_isKing;

	Position* getMovesForKing(int& size)const;
	Position* getMovesForSoldier(int& size)const;
	void addToPosArr(Position* arr, int& size, int r, int c) const;
	bool getIfKing() const;
public:
	CheckersTool(int row, int col, belongToPlayer player, GameBase* game);
	CheckersTool(GameBase* game);

	void setIfKing(bool ifKing);

	virtual Position* getRisks(int& size) const override;
	virtual char getLetter() override;
	virtual Position* getPossibleMoves(int& size) const override;

	virtual void saveToFile(std::ofstream& ofs);
	virtual void readFromFile(std::ifstream& ifs);
};

