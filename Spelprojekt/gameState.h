#ifndef GAMESTATE
#define GAMESTATE
#include "inGameMenu.h"
#include "startMenu.h"
#include "optionMenu.h"
#include <iostream>

class gameState
{
public:
	gameState(sf::RenderWindow &window);

	void drawInGame(sf::RenderWindow &window, sf::Vector2i mouse);
	void drawStartMenu(sf::RenderWindow &window, sf::Vector2i mouse);
	void drawOptionMenu(sf::RenderWindow &window, sf::Vector2i mouse);
	void drawInGameMenu(sf::RenderWindow &window, sf::Vector2i mouse);
	void gameStatesHandler(sf::RenderWindow &window, sf::Vector2i mouse);

	~gameState();

private:
	int mState; //Witch state the game curently are in

	inGameMenu *mInGameMenu01;
	startMenu *mStartMenu01;
	optionMenu *mOptionMenu01;
};

#endif
