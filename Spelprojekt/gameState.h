#ifndef GAMESTATE
#define GAMESTATE
#include "Menu/inGameMenu.h"
#include "Menu/startMenu.h"
#include "Menu/optionMenu.h"
#include "GameOverMenu.h"

#include "MusicManager.h"
#include "SoundManager.h"
#include "Map1.h"
#include <iostream>

class gameState
{
public:
	gameState(sf::RenderWindow &window);

	void drawInGame(sf::RenderWindow &window, sf::Vector2i &mouse, MusicManager &music, SoundManager &sound);
	void drawStartMenu(sf::RenderWindow &window, sf::Vector2i &mouse, MusicManager &music, SoundManager &sound);
	void drawOptionMenu(sf::RenderWindow &window, sf::Vector2i &mouse, MusicManager &music, SoundManager &sound);
	void drawInGameMenu(sf::RenderWindow &window, sf::Vector2i &mouse, MusicManager &music, SoundManager &sound);
	void gameStatesHandler(sf::RenderWindow &window, sf::Vector2i &mouse, MusicManager &music, SoundManager &sound);
	void drawGameOverMenu(sf::RenderWindow &window, sf::Vector2i &mouse, MusicManager &music, SoundManager &sound);

	~gameState();

private:
	int mState; //Witch state the game curently are in

	GameOverMenu *mGameOverMenu01;
	inGameMenu *mInGameMenu01;
	startMenu *mStartMenu01;
	optionMenu *mOptionMenu01;
	Map1 *mMap01;
	int moveMeep = 0;
	bool keyPressed = false;
	bool space = false;
};

#endif
