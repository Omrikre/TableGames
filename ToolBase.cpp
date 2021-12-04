#include "ToolBase.h"
using namespace std;

std::ostream& operator<<(ostream& o, ToolBase& gt)
{
	o << gt.getLetter();
	return o;
}

ToolBase::ToolBase(int row, int col, belongToPlayer pl, GameBase* game)
{
	m_pos.r = row;
	m_pos.c = col;
	setBelongToPlayer(pl);
	m_game = game;
}

void ToolBase::saveToFile(ofstream& ofs)
{
	ofs.write(reinterpret_cast<const char*>(&m_belongTo), sizeof(m_belongTo));
	ofs.write(reinterpret_cast<const char*>(&m_pos.r), sizeof(m_pos.r));
	ofs.write(reinterpret_cast<const char*>(&m_pos.c), sizeof(m_pos.c));
}

void ToolBase::readFromFile(ifstream& ifs)
{
	ifs.read(reinterpret_cast<char*>(&m_belongTo), sizeof(m_belongTo));
	ifs.read(reinterpret_cast<char*>(&m_pos.r), sizeof(m_pos.r));
	ifs.read(reinterpret_cast<char*>(&m_pos.c), sizeof(m_pos.c));
}

void ToolBase::setPos(int row, int col)
{
	m_pos.r = row;
	m_pos.c = col;
}

void ToolBase::setGame(GameBase* game)
{
	m_game = game;
}

int ToolBase::getRow() const
{
	return m_pos.r;
}

int ToolBase::getCol() const
{
	return m_pos.c;
}

void ToolBase::setBelongToPlayer(belongToPlayer pl)
{
	m_belongTo = pl;
}

belongToPlayer ToolBase::getWhoBelongTo() const
{
	return m_belongTo;
}
