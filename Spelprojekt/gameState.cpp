#include "gameState.h"
#include <iostream>
#include <vector>

typedef std::vector<StaticObjects*> ObjectsVector;
ObjectsVector mObjects;
typedef std::vector<Character*> NpcVector;
NpcVector mNpcs;
Player* mPlayer;
ObjectsVector mLongObjects;

gameState::gameState(sf::RenderWindow &window)
{
	mState = 1;
	mInGameMenu01 = new inGameMenu(window.getSize().x, window.getSize().y);
	mStartMenu01 = new startMenu(window.getSize().x, window.getSize().y);
	mOptionMenu01 = new optionMenu(window.getSize().x, window.getSize().y);

	mMap01 = new Map1("map1.txt");
	
	mMap01->spawnObjects();
	mObjects = mMap01->getObjects();
	mPlayer = mMap01->getPlayer();
	mNpcs = mMap01->getNpcs();
	mLongObjects = mMap01->getLongObjects();
	// Skriver ut position för alla object
	for (ObjectsVector::size_type i = 0; i < mObjects.size(); i++){
		std::cout << mObjects[i]->getPosX() << " " << mObjects[i]->getPosY() << std::endl;
	}
}

gameState::~gameState()
{
}

void gameState::drawInGameMenu(sf::RenderWindow &window, sf::Vector2i &mouse, MusicManager &music, SoundManager &sound)
{
	
	mInGameMenu01->updateInGameMenu(window);
	mInGameMenu01->displayMenu01(window);
	
}

void gameState::drawStartMenu(sf::RenderWindow &window, sf::Vector2i &mouse, MusicManager &music, SoundManager &sound)
{
	mStartMenu01->updateStartMenu(window);
	mStartMenu01->displayMenu01(window);
	
}

void gameState::drawInGame(sf::RenderWindow &window, sf::Vector2i &mouse, MusicManager &music, SoundManager &sound)
{
	//Ritar ut objekten
	for (ObjectsVector::size_type i = 0; i < mObjects.size(); i++){
		window.draw(mObjects[i]->getSprite());
		//mObjects[i]->render();
	}
	for (NpcVector::size_type i = 0; i < mNpcs.size(); i++){
		window.draw(mNpcs[i]->getSprite());
	}
	window.draw(mPlayer->getSprite());
	for (ObjectsVector::size_type i = 0; i < mLongObjects.size(); i++){
		window.draw(mLongObjects[i]->getSprite());
		//mObjects[i]->render();
	}
	mMap01->render();

	if (moveMeep != 1 && ((sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) &&
		sf::Keyboard::isKeyPressed(sf::Keyboard::A)) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1))){
		moveMeep = 1;
		keyPressed = true;
	}
	if (moveMeep != 3 && ((sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) &&
		sf::Keyboard::isKeyPressed(sf::Keyboard::S)) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3))){
		moveMeep = 3;
		keyPressed = true;
	}
	if (moveMeep != 7 && ((sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) &&
		sf::Keyboard::isKeyPressed(sf::Keyboard::W)) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7))){
		moveMeep = 7;
		keyPressed = true;
	}
	if (moveMeep != 9 && ((sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) &&
		sf::Keyboard::isKeyPressed(sf::Keyboard::D)) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad9))){
		moveMeep = 9;
		keyPressed = true;
	}

	if (moveMeep != 2 && ((!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) &&
		sf::Keyboard::isKeyPressed(sf::Keyboard::S)) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))){
		moveMeep = 2;
		keyPressed = true;
	}
	if (moveMeep != 4 && ((!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) &&
		sf::Keyboard::isKeyPressed(sf::Keyboard::A)) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4))){
		moveMeep = 4;
		keyPressed = true;
	}
	if (moveMeep != 6 && ((!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) &&
		sf::Keyboard::isKeyPressed(sf::Keyboard::D)) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6))){
		moveMeep = 6;
		keyPressed = true;
	}
	if (moveMeep != 8 && ((!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) &&
		sf::Keyboard::isKeyPressed(sf::Keyboard::W)) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8))){
		moveMeep = 8;
		keyPressed = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !space && keyPressed){
		space = true;
		mMap01->takeTurn(moveMeep);
		moveMeep = 0;
		keyPressed = false;
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && space){
		space = false;
	}
}

void gameState::drawOptionMenu(sf::RenderWindow &window, sf::Vector2i &mouse, MusicManager &music, SoundManager &sound)
{
	mOptionMenu01->updateoptionMenu(window);
	mOptionMenu01->displayMenu01(window);
}

void gameState::gameStatesHandler(sf::RenderWindow &window, sf::Vector2i &mouse, MusicManager &music, SoundManager &sound)
{
	switch (mState) //switch that hold the states of the game
	{
	case 1: //Game state 1. in game. 
		drawInGame(window, mouse, music, sound);
		break;

	case 2: //Case 2, Draw ingame menu
		drawInGameMenu(window, mouse, music, sound);
		break;

	case 3: //State 3. Start menu.
		drawStartMenu(window, mouse, music, sound);
		break;

	case 4: //state 4. option.

		break;

	default:
		std::cout << "default gamestate";
		break;
	}

	//Outside the gamestates, check if the user changes the gamestate.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		mState = 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		mState = 2;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		mState = 3;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
	{
		mState = 4;
	}

}
