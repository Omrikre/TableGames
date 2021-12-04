#include "player.h"

using namespace std;

Player::Player(int maxTools)
	:m_numOfTools(0), m_maxTools(maxTools)
{
	m_toolsArr = new ToolBase*[m_maxTools];
}

Player::~Player()
{
	delete[] m_toolsArr;
}

void Player::saveToFile(ofstream& ofs)
{
	if (!ofs.good())
		throw runtime_error("something in the file is bad.");
	ofs.write(reinterpret_cast<const char*>(&m_maxTools), sizeof(m_maxTools));
}

void Player::readFromFile(ifstream& ifs)
{
	ifs.read(reinterpret_cast<char*>(&m_maxTools), sizeof(m_maxTools));
	m_toolsArr = new ToolBase * [m_maxTools];
}

void Player::addTool(ToolBase& daTool)
{
	m_toolsArr[m_numOfTools] = &daTool;
	m_numOfTools++;
}

void Player::removeTool(ToolBase& daTool)
{
	int i = 0;
	while (i < m_numOfTools && &daTool != m_toolsArr[i])
	{
		i++;
	}
	for (int j = i; j < m_numOfTools - 1; j++)
	{
		m_toolsArr[j] = m_toolsArr[j + 1];
	}
	m_numOfTools--;
}

int Player::getNumOfTools()
{
	return m_numOfTools;
}

ToolBase** Player::getToolArr()
{ 
	return m_toolsArr; 
}

