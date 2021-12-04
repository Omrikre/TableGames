#include "GameBase.h"
#include <iostream>
static int constexpr CHECKERS_BOARDSIZE = 8;
static int constexpr CHECKERS_NUMTOOLS = 12;

class Checkers : public GameBase
{
private:
	void setGameBoard();
	virtual void saveTool(std::ofstream& ofs, ToolBase* tool);
	virtual ToolBase* readTool(std::ifstream& ifs);
public:
	Checkers(bool bSetBoard);
	
	friend std::ostream& operator<<(std::ostream& o, Checkers& g);
	virtual MoveResult move();

	virtual void printBoard();
};




