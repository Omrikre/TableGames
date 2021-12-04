#pragma once
#include <iostream>
#include "ToolBase.h"

enum class toolType {
	checker=0,
	amazon=1,
	pawn=2, // חייל רק אחד קדימה אוכל באלכסון
	steeple=3, // צריח מקבילים
	bishop=4, // רץ אלכסונים
	knight=5, // פרש שתיים מקבילים ועוד אחד מקביל לכיוון אחר
	queen=6, // מלכה אלכסונים ומקבילים
	king=7 // מלך צעד אחד לכל כיוון
};


class ChessGameTool : public ToolBase
{
protected:
	toolType m_tType;
public:
	// Ctor // Dtor
	ChessGameTool(int row, int col, belongToPlayer pl, GameBase* game, toolType tType);
	ChessGameTool(GameBase* game, toolType tType);
	//ChessGameTool();

	~ChessGameTool();
	void addToPosArr(Position* arr, int& size, int r, int c) const;

	virtual Position* getRisks(int& size)const;
	toolType getToolType() { return m_tType; }

private:
	ToolBase** getOpponentTools(int& size) const;
};

