#pragma once
#include <iostream>
#include <fstream>

enum class belongToPlayer
{
	notExist = 0,
	player1 = 1,
	player2 = 2,
	burned = 3
};

struct Position
{
	int r;
	int c;
};

class GameBase;

class ToolBase
{
protected:
	belongToPlayer m_belongTo;
	GameBase* m_game = nullptr;
	Position m_pos;
public:
	ToolBase(int row, int col, belongToPlayer pl, GameBase* game);

	// setters
	belongToPlayer getWhoBelongTo() const;
	void setBelongToPlayer(belongToPlayer pl);

	void setGame(GameBase* game);
	void setPos(int row, int col);
	int getRow() const;
	int getCol() const;

	friend std::ostream& operator<<(std::ostream& o, ToolBase& gt);

	virtual char getLetter() = 0;
	virtual Position* getPossibleMoves(int& size) const = 0;
	virtual Position* getRisks(int& size) const = 0;

	virtual void saveToFile(std::ofstream& ofs);
	virtual void readFromFile(std::ifstream& ifs);

};

