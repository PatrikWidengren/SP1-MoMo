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
	mState = 3;
	mInGameMenu01 = new inGameMenu(window.getSize().x, window.getSize().y);
	mStartMenu01 = new startMenu(window.getSize().x, window.getSize().y);
	mOptionMenu01 = new optionMenu(window.getSize().x, window.getSize().y);
	mToolSelectMenu01 = new ToolSelectMenu(window.getSize().x, window.getSize().y);
	mGameOverMenu01 = new GameOverMenu(window.getSize().x, window.getSize().y);
	mWinMenu01 = new WinMenu(window.getSize().x, window.getSize().y);

	mMap01 = new Map1("Maps/maptest3.txt");
	
	mLawnMowers.push_back(new GoLawnMower);
	mLawnMowers.push_back(new LawnMower);
	mHedgeTools.push_back(new HedgeCutter(1, 1));
	mHedgeTools.push_back(new HedgeCutter(2, 1));
	mHedgeTools.push_back(new HedgeCutter(4, 2));

	mMap01->spawnObjects();
	mMap01->render(window);
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
	while (!mLawnMowers.empty()){
		mLawnMowers.pop_back();
	}
	while (!mHedgeTools.empty()){
		mHedgeTools.pop_back();
	}
}

void gameState::drawInGameMenu(sf::RenderWindow &window, sf::Vector2i &mouse, MusicManager &music, SoundManager &sound)
{
	
	mInGameMenu01->updateInGameMenu(window);
	mInGameMenu01->displayMenu01(window);
	mState = mInGameMenu01->checkState();
	
}

void gameState::drawStartMenu(sf::RenderWindow &window, sf::Vector2i &mouse, MusicManager &music, SoundManager &sound)
{
	mStartMenu01->updateStartMenu(window);
	mStartMenu01->displayMenu01(window);
	mState = mStartMenu01->checkState();
	
}

void gameState::drawInGame(sf::RenderWindow &window, sf::Vector2i &mouse, MusicManager &music, SoundManager &sound)
{
	/*
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
	}*/
	mMap01->render(window);


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5) && !swap5){
		swap5 = true;
		std::cout << "swapping" << std::endl;
		/*std::cout << "Swapped to ";
		if (mMap01->getPlayer()->getMowerEquipped()){
			std::cout << "lawnmower" << std::endl;
		}
		else {
			std::cout << "hedge cutter" << std::endl;
		}*/
		mMap01->getPlayer()->swapEquipped();
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5) && swap5){
		swap5 = false;
	}



	if (moveMeep != 1 && ((sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) &&
		sf::Keyboard::isKeyPressed(sf::Keyboard::A)) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1))){
		moveMeep = 1;
		std::cout << "movdir " << moveMeep << std::endl;
		keyPressed = true;
	}
	if (moveMeep != 3 && ((sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) &&
		sf::Keyboard::isKeyPressed(sf::Keyboard::S)) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3))){
		moveMeep = 3;
		//std::cout << "movdir " << moveMeep << std::endl;
		keyPressed = true;
	}
	if (moveMeep != 7 && ((sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) &&
		sf::Keyboard::isKeyPressed(sf::Keyboard::W)) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7))){
		moveMeep = 7;
		//std::cout << "movdir " << moveMeep << std::endl;
		keyPressed = true;
	}
	if (moveMeep != 9 && ((sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) &&
		sf::Keyboard::isKeyPressed(sf::Keyboard::D)) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad9))){
		moveMeep = 9;
		//std::cout << "movdir " << moveMeep << std::endl;
		keyPressed = true;
	}

	if (moveMeep != 2 && ((!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) &&
		sf::Keyboard::isKeyPressed(sf::Keyboard::S)) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))){
		moveMeep = 2;
		//std::cout << "movdir " << moveMeep << std::endl;
		keyPressed = true;
	}
	if (moveMeep != 4 && ((!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) &&
		sf::Keyboard::isKeyPressed(sf::Keyboard::A)) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4))){
		moveMeep = 4;
		//std::cout << "movdir " << moveMeep << std::endl;
		keyPressed = true;
	}
	if (moveMeep != 6 && ((!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) &&
		sf::Keyboard::isKeyPressed(sf::Keyboard::D)) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6))){
		moveMeep = 6;
		//std::cout << "movdir " << moveMeep << std::endl;
		keyPressed = true;
	}
	if (moveMeep != 8 && ((!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) &&
		sf::Keyboard::isKeyPressed(sf::Keyboard::W)) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8))){
		moveMeep = 8;
		//std::cout << "movdir " << moveMeep << std::endl;
		keyPressed = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !space && keyPressed){
		space = true;
		//std::cout << "confirm dir " << moveMeep << std::endl;
		mMap01->takeTurn(moveMeep, sound);
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
	mState = mOptionMenu01->checkState();
}

void gameState::drawToolSelectMenu(sf::RenderWindow &window, sf::Vector2i &mouse, MusicManager &music, SoundManager &sound)
{
	mToolSelectMenu01->updateToolSelectMenu(window);
	mToolSelectMenu01->displayMenu01(window);
	mState = mToolSelectMenu01->checkState();
}

void gameState::drawGameOverMenu(sf::RenderWindow &window, sf::Vector2i &mouse, MusicManager &music, SoundManager &sound)
{
	mGameOverMenu01->updateGameOverMenu(window);
	mGameOverMenu01->displayMenu01(window);
	mState = mGameOverMenu01->checkState();
}

void gameState::drawWinMenu(sf::RenderWindow &window, sf::Vector2i &mouse, MusicManager &music, SoundManager &sound)
{
	mWinMenu01->updateWinMenu(window);
	mWinMenu01->displayMenu01(window);
	mState = mWinMenu01->checkState();
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
		drawOptionMenu(window, mouse, music, sound);
		break;

	case 5: //state 5. GameOver.
		drawGameOverMenu(window, mouse, music, sound);
		break;

	case 6: //state 6. WinMenu.
		drawWinMenu(window, mouse, music, sound);
		break;

	case 8:
		mPlayer->setMower(mLawnMowers.at(mCurMower));
		std::cout << mLawnMowers.at(mCurMower)->getStats() << std::endl;
		mCurMower++;
		mCurMower = mCurMower%mLawnMowers.size();
		mState = 0;
		break;

	case 9:
		mPlayer->setHedgeTool(mHedgeTools.at(mCurHedgeTool));
		std::cout << mHedgeTools.at(mCurHedgeTool)->getStats() << std::endl;
		mCurHedgeTool++;
		mCurHedgeTool = mCurHedgeTool%mHedgeTools.size();
		mState = 0;
		break;

	case 0: //The illustrious state 0. Swap out equipment
		drawToolSelectMenu(window, mouse, music, sound);
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
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


	if (mStartMenu01->reset == true || mWinMenu01->reset == true)
	{
		mWinMenu01->reset = false;
		mStartMenu01->reset = false;
		resetMap();
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
	{
		mState = 0;
	}

	if (mMap01->mTurnCount >= 50
		)
	//Lägg till en maxvariabel för varje induviduell bana. Eventuellt lägga mappsen i en array så man
	//kan välja vilken banas maxvärde man ska anvädnda för att veta om det är gameover. Ex: Maps[i]->maxTurnCount
	if (mMap01->mTurnCount >= mMap01->mLoseRounds)
		mState = 5;

	//For now, just testing phase of Winning screen. Need Winning condition for the map.
	if (mMap01->mTurnCount >= mMap01->mWinRounds)
		mState = 6;

}

void gameState::resetMap()
{
	mMap01->resetGrid();
	//mMap01->deleteContent();
	//mMap01->spawnObjects();
	//mObjects = mMap01->getObjects();
	//mPlayer = mMap01->getPlayer();
	//mNpcs = mMap01->getNpcs();
	//mLongObjects = mMap01->getLongObjects();
	// Skriver ut position för alla object
	for (ObjectsVector::size_type i = 0; i < mObjects.size(); i++){
		std::cout << mObjects[i]->getPosX() << " " << mObjects[i]->getPosY() << std::endl;
	}
}
