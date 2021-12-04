#include "Player.h"
#include "GameBase.h"
#include <iostream>
static int constexpr AMAZONAS_BOARDSIZE = 10;
static int constexpr AMAZONAS_NUMTOOLS = 4;

class AmazonasGame : public GameBase
{
public:
	AmazonasGame(bool bSetBoard);
	void setGameBoard(); 
	void printBoard();
	friend std::ostream& operator<<(std::ostream& o, AmazonasGame& g);
	void burnPos(int row, int col);
	int FindIndexInMovesArr(Position* arr, int size, int row, int col) const;
	virtual MoveResult move();


	virtual void saveTool(std::ofstream& ofs, ToolBase* tool);
	virtual ToolBase* readTool(std::ifstream& ifs);
private:
	void checkGameEnd();
	bool checkIfHavePossibleMoves(int row, int col);
};




