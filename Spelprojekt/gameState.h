#ifndef GAMESTATE
#define GAMESTATE
#include "Menu/inGameMenu.h"
#include "Menu/startMenu.h"
#include "Menu/optionMenu.h"
#include "Menu/GameOverMenu.h"
#include "Menu/WinMenu.h"
#include "Menu/ToolSelectMenu.h"
#include "WorldMap.h"
#include "SoundMenu.h"
#include "KeyboardOptionMenu.h"

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
	void drawToolSelectMenu(sf::RenderWindow &window, sf::Vector2i &mouse, MusicManager &music, SoundManager &sound);
	void drawInGameMenu(sf::RenderWindow &window, sf::Vector2i &mouse, MusicManager &music, SoundManager &sound);
	void drawGameOverMenu(sf::RenderWindow &window, sf::Vector2i &mouse, MusicManager &music, SoundManager &sound);
	void drawWinMenu(sf::RenderWindow &window, sf::Vector2i &mouse, MusicManager &music, SoundManager &sound);
	void drawSoundMenu(sf::RenderWindow &window, sf::Vector2i &mouse, MusicManager &music, SoundManager &sound);
	void drawKeyboardMenu(sf::RenderWindow &window, sf::Vector2i &mouse, MusicManager &music, SoundManager &sound);
	void drawWorldMap(sf::RenderWindow &window, sf::Vector2i &mouse, MusicManager &music, SoundManager &sound);

	void gameStatesHandler(sf::RenderWindow &window, sf::Vector2i &mouse, MusicManager &music, SoundManager &sound);

	void resetMap();
	optionMenu *mOptionMenu01;

	~gameState();
	int mState; //Witch state the game curently are in
	int mOptionMenuState;


private:

	KeyboardOptionMenu *mKeyboardMenu01;
	SoundMenu *mSoundmenu01;
	WinMenu *mWinMenu01;
	GameOverMenu *mGameOverMenu01;
	inGameMenu *mInGameMenu01;
	startMenu *mStartMenu01;
	ToolSelectMenu *mToolSelectMenu01;
	WorldMap *mWorldMap01;
	Map1 *mMap01;
	int mCurMower = 0;
	int mCurHedgeTool = 0;
	std::vector<Mower*> mLawnMowers;
	std::vector<Shears*> mHedgeTools;
	int moveMeep = 0;
	bool keyPressed = false;
	bool space = false;
	bool swap5 = false;
};

#endif
