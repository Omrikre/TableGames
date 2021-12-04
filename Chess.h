#pragma once
#include "GameBase.h"

static int constexpr CHESS_BOARDSIZE = 8;
static int constexpr CHESS_NUMTOOLS = 16;

class Chess : public GameBase
{
private:
	void setGameBoardRow2(belongToPlayer pl);
	void setGameBoardRow1(belongToPlayer pl);
	bool checkIfGameEnded();
	void setGameBoard();

	virtual void saveTool(std::ofstream& ofs, ToolBase* tool);
	virtual ToolBase* readTool(std::ifstream& ifs);
public:
	Chess(bool bSetBoard);
	~Chess();
	// Setters
	virtual MoveResult move();
	int FindIndexInMovesArr(Position* arr, int size, int row, int col) const;
	//void removeTool(int r, int c);

	void printBoard();

	friend std::ostream& operator<<(std::ostream& o, Chess& g);
	//void moveTool(int fromR, int fromC, int toR, int toC);
};


