#ifndef GAMESTATE
#define GAMESTATE
#include "GameStates/Menu/inGameMenu.h"
#include "GameStates/Menu/startMenu.h"
#include "GameStates/Menu/optionMenu.h"
#include "GameStates/Menu/GameOverMenu.h"
#include "GameStates/Menu/WinMenu.h"
#include "GameStates/Menu/ToolSelectMenu.h"
#include "GameStates/WorldMap.h"
#include "GameStates/RegionMap.h"
#include "GameStates/Menu/SoundMenu.h"
#include "GameStates/Menu/KeyboardOptionMenu.h"

#include "Managers\DialogManager.h"
#include "Managers/MusicManager.h"
#include "Managers/SoundManager.h"
#include "Managers/AnimeManager.h"
#include "GameStates/Map1.h"
#include <iostream>

class gameState
{
public:
	gameState(sf::RenderWindow &window);

	void drawInGame(sf::RenderWindow &window, sf::Vector2i &mouse, MusicManager &music, SoundManager &sound, AnimeManager &anime);
	void drawInGameHud(sf::RenderWindow &window);
	void drawStartMenu(sf::RenderWindow &window, sf::Vector2i &mouse, MusicManager &music, SoundManager &sound);
	void drawOptionMenu(sf::RenderWindow &window, sf::Vector2i &mouse, MusicManager &music, SoundManager &sound);
	void drawToolSelectMenu(sf::RenderWindow &window, sf::Vector2i &mouse, MusicManager &music, SoundManager &sound);
	void drawInGameMenu(sf::RenderWindow &window, sf::Vector2i &mouse, MusicManager &music, SoundManager &sound);
	void drawGameOverMenu(sf::RenderWindow &window, sf::Vector2i &mouse, MusicManager &music, SoundManager &sound);
	void drawWinMenu(sf::RenderWindow &window, sf::Vector2i &mouse, MusicManager &music, SoundManager &sound);
	void drawSoundMenu(sf::RenderWindow &window, sf::Vector2i &mouse, MusicManager &music, SoundManager &sound);
	void drawKeyboardMenu(sf::RenderWindow &window, sf::Vector2i &mouse, MusicManager &music, SoundManager &sound);
	void drawWorldMap(sf::RenderWindow &window, sf::Vector2i &mouse, MusicManager &music, SoundManager &sound);
	void drawRegionMap(sf::RenderWindow &window, sf::Vector2i &mouse, MusicManager &music, SoundManager &sound);

	void gameStatesHandler(sf::RenderWindow &window, sf::Vector2i &mouse, MusicManager &music, SoundManager &sound, AnimeManager &anime);
	
	bool checkStartState(int lowerState);
	bool checkStartOptionState(int lowerState);
	bool checkStartRegionState(int lowerState);
	void resetMap();
	optionMenu *mOptionMenu01;

	~gameState();
	int mState; //Witch state the game curently are in
	int mOptionMenuState;
	bool mStartState;
	bool mStartOptionState;
	bool mStartRegionState;
	int mRegionState;


private:

	KeyboardOptionMenu *mKeyboardMenu01;
	SoundMenu *mSoundmenu01;
	WinMenu *mWinMenu01;
	GameOverMenu *mGameOverMenu01;
	inGameMenu *mInGameMenu01;
	startMenu *mStartMenu01;
	ToolSelectMenu *mToolSelectMenu01;
	WorldMap *mWorldMap01;
	RegionMap *mRegionMap01;
	Map1 *mMap01;
	DialogManager *mDialogManager;
	void loadMap();
	int mCurMower = 0;
	int mCurHedgeTool = 0;
	std::string meepHeightAnimation;
	std::vector<Mower*> mLawnMowers;
	std::vector<Shears*> mHedgeTools;
	int moveMeep = 0;
	bool keyPressed = false;
	bool space = false;
	bool swap5 = false;
};

#endif
