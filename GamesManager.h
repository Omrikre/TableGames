#pragma once
#include "GameBase.h"

//to do: move to separate h file (list and node can be together)
struct LstGameNode {
	GameBase* Game;
	LstGameNode* next;
};

struct lstGame {
	LstGameNode* head = nullptr;
	LstGameNode* tail = nullptr;
};


class GameManager
{
private:
	lstGame		lst;
	int			numOfGames = 0;
	LstGameNode* currGame = nullptr;
private:
	void clearScreen();
	int printMenu();
	void addToTail(LstGameNode* newGame);
	bool checkGameToolIsValid(int row, int col, LstGameNode* currGame);
	LstGameNode* deleteGame(LstGameNode* gameToDelete);
	LstGameNode* createNewGame();
	LstGameNode* addTheGame(gameType gType, bool bSetBoard);

	LstGameNode* moveToNextGame(LstGameNode* currGame);
	
	void printGameStats(LstGameNode* currGame);
	void printPossibleMoves(int row, int col, LstGameNode* currGame);
	void printDangerousGameTools(int row, int col, LstGameNode* currGame);
	void freeAllGames();
	void moveTool(LstGameNode* currGame);
	gameType printGameTypeMenu();
	void inWhichGameTypeAmI(LstGameNode* currGame);
	void printTitle(gameType gT);
	void saveCurrGame(LstGameNode* currGame);
	LstGameNode* loadGame();

public:
	void menu();
};