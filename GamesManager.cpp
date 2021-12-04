#include "GamesManager.h"
#include "Checkers.h"
#include "AmazonasGame.h"
#include "Chess.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

void GameManager::menu() {
	int selectedMenuOp;
	bool continueToPlay = true;
	int row, col;

	while (continueToPlay) {
		selectedMenuOp = printMenu();
		if (selectedMenuOp < 1 && selectedMenuOp > 10) {
			clearScreen();
			cout << endl << "-- Please choose by the menu! --" << endl << endl;
			continue;
		}
		if ((selectedMenuOp != 8 && selectedMenuOp != 1 && selectedMenuOp != 10) && numOfGames == 0) {
			clearScreen();
			cout << endl << "-- Please create new Game before --" << endl << endl;
			continue;
		}

		switch (selectedMenuOp)
		{
		case 8:
			continueToPlay = false;
			clearScreen();
			freeAllGames(); 
			break;
		case 1:
			currGame = createNewGame();
			numOfGames++;
			clearScreen();
			cout << endl << "-- A new Game has been created --" << endl;
			cout << "-- There are " << numOfGames << " games in the memory --" << endl << endl;
			inWhichGameTypeAmI(currGame);
			break;

		case 2:
			if (numOfGames > 1) {
				currGame = moveToNextGame(currGame);
				clearScreen();
				cout << endl << "-- Sucssesfuly moved to the next Game --" << endl << endl;
			}
			else {
				clearScreen();
				cout << endl << "-- There is only one Game --" << endl << endl;
			}
			break;
		case 3:
			currGame = deleteGame(currGame);
			numOfGames--;
			clearScreen();
			cout << endl << "-- The current Game has been deleted --" << endl;
			break;
		case 4:
			clearScreen();
			printGameStats(currGame);
			break;
		case 5:
			cout << endl << "Please enter the row and col of the Game tool: " << endl;
			cin >> row >> col;
			clearScreen();
			printPossibleMoves(row, col, currGame);
			break;
		case 6:
			cout << endl << "Please enter the row and col of the Game tool: " << endl;
			cin >> row >> col;
			clearScreen();
			if (checkGameToolIsValid(row, col, currGame))
				printDangerousGameTools(row, col, currGame);
			break;
		case 7:
			moveTool(currGame);
			break;
		case 9:
			try
			{
				saveCurrGame(currGame);
			}
			catch (runtime_error& error)
			{
				cout << "The current game was not saved to the file." << endl;
				cout << error.what() << endl;
			}
			break;
		case 10:
			try
			{
				currGame = loadGame();
				numOfGames++;
				clearScreen();
				cout << endl << "-- A new Game has been loaded from file --" << endl;
				cout << "-- There are " << numOfGames << " games in the memory --" << endl << endl;
				inWhichGameTypeAmI(currGame);
			}
			catch (runtime_error& error)
			{
				cout << "The new game was not created something was bad in the file." << endl;
				cout << error.what() << endl;
			}
			break;
		}
	}
	cout << "Hope you enjoyed!" << endl << endl;
}

void GameManager::saveCurrGame(LstGameNode* currGame)
{
	string fileName;
	cout << "Please insert the file name:" << endl;
	cin >> fileName;

	ofstream o(fileName, ios::binary | ios::out);
	if (!o.good())
		cout << "Can't open the file. The game was not saved." << endl;
	else
	{
		int gameType = (int)currGame->Game->getGameType();
		o.write(reinterpret_cast<const char*>(&gameType), sizeof(int));
		currGame->Game->saveToFile(o);
	}
}

LstGameNode* GameManager::loadGame()
{
	string fileName;
	cout << "Please insert the file name:" << endl;
	cin >> fileName;

	ifstream ifs(fileName, ios::binary | ios::in);
	gameType gType;
	ifs.read(reinterpret_cast<char*>(&gType), sizeof(gType));
	LstGameNode* n = addTheGame(gType, false);
	n->Game->readFromFile(ifs);
	return n;
}

void GameManager::printTitle(gameType gT) {
	if (gT == gameType::amazons)
		cout << "Amazons";
	else if (gT == gameType::checkers)
		cout << "Checkers";
	else
		cout << "Chess";
}

void GameManager::inWhichGameTypeAmI(LstGameNode* currGame) {
	cout << "-- You're playing ";
	printTitle(currGame->Game->getGameType());
	cout << " --" << endl;
}

void GameManager::moveTool(LstGameNode* currGame)
{
	MoveResult res = currGame->Game->move();

	//check if winner
	if (currGame->Game->getGameOn() == false)
	{
		cout << "the winner is player:" << (int)currGame->Game->getWinner() << endl;
	}
}

int GameManager::printMenu() {
	int userChoise;

	cout << "Please choose:" << endl;
	cout << endl;
	cout << " 1.  New Game" << endl;
	cout << " 2.  Move to the next Game" << endl;
	cout << " 3.  Delete current Game" << endl;
	cout << " 4.  Show Game stats" << endl;
	cout << " 5.  Show GameTool's possible move" << endl;
	cout << " 6.  Show GameTool's risks" << endl;
	cout << " 7.  Make a move in the Game" << endl;
	cout << " 8.  Exit" << endl;
	cout << " 9.  Save curr game" << endl;
	cout << " 10. Load game" << endl;
	cout << endl;

	cin >> userChoise;
	return userChoise;
}

gameType GameManager::printGameTypeMenu() {
	int userChoise;
	clearScreen();
	cout << endl << " Please choose game type:" << endl << endl;
	cout << " 1. Checkers" << endl;
	cout << " 2. Amazons" << endl;
	cout << " 3. Chess" << endl << endl;

	cin >> userChoise;
	while (userChoise < 1 || userChoise > 3)
	{
		clearScreen();
		cout << "Wrong game type." << endl;
		cout << endl << " Please choose game type:" << endl << endl;
		cout << " 1. Checkers" << endl;
		cout << " 2. Amazons" << endl;
		cout << " 3. Chess" << endl << endl;
		cin >> userChoise;
	}

	if (userChoise == 1)
		return gameType::checkers;
	else if (userChoise == 2)
		return gameType::amazons;
	else
		return gameType::chess;
} 

LstGameNode* GameManager::createNewGame() {
	gameType gType = printGameTypeMenu();
	return addTheGame(gType,true);
}

LstGameNode* GameManager::addTheGame(gameType gType, bool bSetBoard) 
{
	LstGameNode* newGameNode = new LstGameNode;

	GameBase* newGame = nullptr;
	if (gType == gameType::amazons)
		newGame = new AmazonasGame(bSetBoard);
	else if (gType == gameType::chess)
		newGame = new Chess(bSetBoard);
	else if (gType == gameType::checkers)
		newGame = new Checkers(bSetBoard);
	else
	{
		delete newGameNode;
		throw runtime_error("the game type is wrong");
	}

	newGameNode->Game = newGame;
	newGameNode->next = nullptr;

	addToTail(newGameNode);
	return newGameNode;
}

void GameManager::addToTail(LstGameNode* newGame) {
	if (lst.head == nullptr)
		lst.head = lst.tail = newGame;
	else {
		lst.tail->next = newGame;
		lst.tail = newGame;
	}
}

LstGameNode* GameManager::moveToNextGame(LstGameNode* currGame) {
	if (currGame == lst.tail) 
		return lst.head;
	else
		return currGame->next;
}

void GameManager::clearScreen() {
	//system("CLS"); TODO REUTNR
}

LstGameNode* GameManager::deleteGame(LstGameNode* gameToDelete) {
	LstGameNode* newCurrGame;
	LstGameNode* prev;
	LstGameNode* curr;
	//find next game
	if (gameToDelete == lst.head && gameToDelete == lst.tail)
		newCurrGame = nullptr;
	else if (gameToDelete->next == nullptr)
		newCurrGame = lst.head;
	else
		newCurrGame = gameToDelete->next;

	//from start
	if (gameToDelete == lst.head)
	{
		if (gameToDelete == lst.tail)
		{
			lst.head = lst.tail = nullptr;
		}
		else
		{
			lst.head = gameToDelete->next;
		}
	}
	else
	{
		prev = nullptr;
		curr = lst.head;
		while (curr != gameToDelete)
		{
			prev = curr;
			curr = curr->next;
		}

		if (gameToDelete == lst.tail)//from tail but not from head too
		{
			prev->next = nullptr;
			lst.tail = prev;
		}
		else
		{
			prev->next = prev->next->next;
		}
	}

	delete gameToDelete->Game;
	delete gameToDelete;

	return newCurrGame;
}

bool GameManager::checkGameToolIsValid(int row, int col, LstGameNode* currGame) {
	if(currGame->Game->isValidPos(row,col) == false) {
		cout << endl << "-- Not in board range! --" << endl;
		return false;
	}
	else if (currGame->Game->checkIfEmptyPanel(row, col)) {
		cout << endl << "-- The panel is empty! --" << endl;
		return false;
	}
	else
		return true;
}

void GameManager::printGameStats(LstGameNode* currGame) {
	if (currGame->Game->getGameOn() == true)
	{
		cout << "Game is on. Curr player is: " << (int)currGame->Game->getTurn() << endl;
	}
	else
	{
		cout << "This game is over. The Winner is: Player " << (int)currGame->Game->getWinner() << endl;
	}

	currGame->Game->printBoard();
}

void GameManager::printPossibleMoves(int row, int col, LstGameNode* currGame) {
	int size;
	if (checkGameToolIsValid(row, col, currGame) == false)
	{
		cout << "This position is not valid" << endl;
	}
	else
	{
		Position* arr = currGame->Game->getGameToolInPosition(row, col).getPossibleMoves(size);
		if (size == 0)
		{
			cout << "no posible moves for this tile" << endl;
		}
		else
		{
			cout << "you can move to these locations:" << endl;

			for (int i = 0; i < size; i++)
			{
				cout << "( " << arr[i].r << " , " << arr[i].c << " )" << endl;
			}
			delete[] arr;
		}
	}
}

void GameManager::printDangerousGameTools(int row, int col, LstGameNode* currGame) {
	//move to class
	int size;
	Position* arr = currGame->Game->getGameToolInPosition(row, col).getRisks(size);
	if (size == 0)
	{
		cout << "no danger from this square" << endl;
	}
	else
	{
		cout << "this is the danger moves! : " << endl;

		for (int i = 0; i < size; i++)
		{
			cout << "(" << arr[i].r << " ," << arr[i].c << ")" << endl;
		}
		delete[] arr;
	}
}

void GameManager::freeAllGames() {
	LstGameNode* curr = lst.head;
	LstGameNode* next = nullptr;
	while (curr != nullptr)
	{
		next = curr->next;
		delete curr->Game;
		delete curr;
		curr = next;
	}
	lst.head = lst.tail = nullptr;
}
