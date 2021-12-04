#pragma once
#include "Player.h"
#include "ToolBase.h"
#include <fstream>
#include <vector>

enum class MoveResult
{
	Success = 0,
	GameIsOver,
	InvalidPosition,
	PanelIsEmpty,
	ToolBelongToOtherPlayer,
	NoPossibleMoves,
	NotAPossibleMove
};

enum class gameType {
	checkers = 0,
	amazons = 1,
	chess = 2,
};

class ToolBase;
class GameBase
{
protected:
	int				m_boardSize;
	//ToolBase*** m_board;
	std::vector<std::vector<ToolBase*>>       m_boardVec;
	Player			m_pl1;
	Player			m_pl2;
	belongToPlayer	m_turn;
	belongToPlayer	m_winner;
	bool			m_gameOn = true;
	gameType		m_gType;

	void freePartOfBoard(int r, int c);
private:
	void allocateBoard();
	void deallocateBoard();

	void saveBoardToFile(std::ofstream& ofs);
	void readBoardFromFile(std::ifstream& ifs);	
	virtual void saveTool(std::ofstream& ofs, ToolBase* tool) = 0;
	virtual ToolBase* readTool(std::ifstream& ifs) = 0;	

	//virtual void saveTool(std::ofstream& ofs, ToolBase* tool) {}
	//virtual ToolBase* readTool(std::ifstream& ifs) { return nullptr; }
public:
	GameBase(int boardSize, int numPlayerTools);
	virtual ~GameBase();

	int getBoardSize() { return m_boardSize; }
	belongToPlayer	getTurn() const;
	void			setTurn(belongToPlayer pl);

	belongToPlayer	getWinner() const;
	void			setWinner(belongToPlayer pl);

	bool getGameOn() const;
	Player& getPlayer1();
	Player& getPlayer2();
	ToolBase& getGameToolInPosition(int row, int col);

	bool isValidPos(int row, int col);
	bool checkIfEmptyPanel(int row, int col);

	belongToPlayer getBelongToInPos(int r, int c);

	virtual MoveResult move() = 0;
	void moveTool(int fromR, int fromC, int toR, int toC);
	void removeTool(int r, int c);
	bool checkGameToolIsValid(int row, int col);

	virtual void printBoard() = 0;
	void printTurn();

	gameType getGameType() { return m_gType; }
	void saveToFile(std::ofstream& ofs);
	void readFromFile(std::ifstream& ifs);


};

