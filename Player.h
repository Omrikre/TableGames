#pragma once
#include <fstream>

enum class gameStat { GameOn, Winner, Loser };
class ToolBase;
class Player
{
private:
	int m_numOfTools;
	ToolBase** m_toolsArr = nullptr;
	int m_maxTools;
	//gameStat m_playerStat;
public:
	Player(int maxTools);
	~Player();

	//void setNumOfTools(int boardSize);
	void addTool(ToolBase& daTool);
	void removeTool(ToolBase& daTool);
	int getNumOfTools();
	ToolBase** getToolArr();

	void saveToFile(std::ofstream& ofs);
	void readFromFile(std::ifstream& ifs);

};

