#include "gameState.h"
#include <iostream>
#include <vector>


typedef std::vector<StaticObjects*> ObjectsVector;
ObjectsVector mObjects;
typedef std::vector<Character*> NpcVector;
Maps::NpcMap mNpcs;
Player* mPlayer;
ObjectsVector mLongObjects;

gameState::gameState(sf::RenderWindow &window)
{
	mState = 3;
	mOptionMenuState = 1;
	mStartState = true;
	mStartOptionState = true;
	mRegionState = 0;
	
	mKeyboardMenu01 = new KeyboardOptionMenu(window.getSize().x, window.getSize().y);
	mSoundmenu01 = new SoundMenu(window.getSize().x, window.getSize().y);
	mInGameMenu01 = new inGameMenu(window.getSize().x, window.getSize().y);
	mStartMenu01 = new startMenu(window.getSize().x, window.getSize().y);
	mOptionMenu01 = new optionMenu(window.getSize().x, window.getSize().y);
	mToolSelectMenu01 = new ToolSelectMenu(window.getSize().x, window.getSize().y);
	mGameOverMenu01 = new GameOverMenu(window.getSize().x, window.getSize().y);
	mWinMenu01 = new WinMenu(window.getSize().x, window.getSize().y);
	mWorldMap01 = new WorldMap(window.getSize().x, window.getSize().y);
	mRegionMap01 = new RegionMap(window.getSize().x, window.getSize().y);
	mInGameBackground = new InGameBackground();

	mDialogManager = new DialogManager(window);

	mLawnMowers.push_back(new LawnMower(2, 1, 1, 1, 10000));
	mLawnMowers.push_back(new LawnMower(3, 2, 1, 1, 3000));
	mLawnMowers.push_back(new LawnMower(4, 2, 2, 2, 3000));
	mLawnMowers.push_back(new LawnMower(3, 1, 1, 2, 2000));
	mLawnMowers.push_back(new LawnMower(4, 1, 1, 2, 3000));
	mHedgeTools.push_back(new HedgeCutter(1, 1));
	mHedgeTools.push_back(new HedgeCutter(2, 1));

	mPlayer = new Player(mLawnMowers.at(mCurMower), mHedgeTools.at(mCurHedgeTool));
	mMap01 = new Map1("map04a02.txt", mPlayer/*, "Maps/patrols/Patrols_testing.txt"*/);
	
	mMap01->spawnObjects();
	//mMap01->render(window, anime);
	//mObjects = mMap01->getObjects();
	//mPlayer = mMap01->getPlayer();
	//mNpcs = mMap01->getNpcs();
	//mLongObjects = mMap01->getLongObjects();
	// Skriver ut position för alla object

	//This thing broke the code, no clue why
	/*for (ObjectsVector::size_type i = 0; i < mObjects.size(); i++){
		std::cout << mObjects[i]->getPosX() << " " << mObjects[i]->getPosY() << std::endl;
	}*/
}

gameState::~gameState()
{
	while (!mLawnMowers.empty()){
		delete mLawnMowers.at(0);
		mLawnMowers.erase(mLawnMowers.begin());
	}
	while (!mHedgeTools.empty()){
		delete mHedgeTools.at(0);
		mHedgeTools.erase(mHedgeTools.begin());
	}
}

void gameState::drawInGameMenu(sf::RenderWindow &window, sf::Vector2i &mouse, MusicManager &music, SoundManager &sound) // Draw In Game Menu
{
	mInGameMenu01->updateInGameMenu(window, mouse, sound);
	window.clear();
	mInGameMenu01->displayMenu01(window);
	mStartState = checkStartState(mInGameMenu01->checkState());
	mState = mInGameMenu01->checkState();
	
}

void gameState::drawStartMenu(sf::RenderWindow &window, sf::Vector2i &mouse, MusicManager &music, SoundManager &sound) // Draw Start Menu
{
	mStartMenu01->updateStartMenu(window, mouse, sound);
	window.clear();
	mStartMenu01->displayMenu01(window); //Update mouse in update...
	mStartState = checkStartState(mStartMenu01->checkState());
	mState = mStartMenu01->checkState();
	
}

void gameState::drawSoundMenu(sf::RenderWindow &window, sf::Vector2i &mouse, MusicManager &music, SoundManager &sound) // Draw Sound Menu
{
	mSoundmenu01->updateSoundMenu(window, mouse, sound, music);
	window.clear();
	mSoundmenu01->displayMenu01(window);
	mStartOptionState = checkStartOptionState(mSoundmenu01->checkOptionState());
	mOptionMenuState = mSoundmenu01->checkOptionState();
}

void gameState::drawOptionMenu(sf::RenderWindow &window, sf::Vector2i &mouse, MusicManager &music, SoundManager &sound) // Draw Option Menu
{
	mOptionMenu01->updateoptionMenu(window, mouse, sound);
	window.clear();
	mOptionMenu01->displayMenu01(window);
	mStartOptionState = checkStartState(mOptionMenu01->checkState());
	mStartState = checkStartState(mOptionMenu01->checkState());
	mState = mOptionMenu01->checkState();
	if (mState == 4) {
		mStartOptionState = checkStartOptionState(mOptionMenu01->checkOptionState());
		mOptionMenuState = mOptionMenu01->checkOptionState();
	}
}

void gameState::drawToolSelectMenu(sf::RenderWindow &window, sf::Vector2i &mouse, MusicManager &music, SoundManager &sound) // Draw Tool Select Menu
{
	mToolSelectMenu01->updateToolSelectMenu(window, mouse);
	window.clear();
	mToolSelectMenu01->displayMenu01(window);
	mStartState = checkStartState(mToolSelectMenu01->checkState());
	mState = mToolSelectMenu01->checkState();
}

void gameState::drawGameOverMenu(sf::RenderWindow &window, sf::Vector2i &mouse, MusicManager &music, SoundManager &sound) // Draw Game Over Menu
{
	mGameOverMenu01->updateGameOverMenu(window, mouse);
	window.clear();
	mGameOverMenu01->displayMenu01(window);
	mStartState = checkStartState(mGameOverMenu01->checkState());
	mState = mGameOverMenu01->checkState();
}

void gameState::drawWinMenu(sf::RenderWindow &window, sf::Vector2i &mouse, MusicManager &music, SoundManager &sound) // Draw Win Menu
{
	mWinMenu01->updateWinMenu(window, mouse);
	window.clear();
	mWinMenu01->displayMenu01(window);
	mStartState = checkStartState(mWinMenu01->checkState());
	mState = mWinMenu01->checkState();
}
int gameState::getControlScheme() {
	return mControlScheme;
}
void gameState::setControlScheme(int controlscheme) {
	mControlScheme = controlscheme;
}
void gameState::drawKeyboardMenu(sf::RenderWindow &window, sf::Vector2i &mouse, MusicManager &music, SoundManager &sound) // Draw Keyboard Menu
{
	mKeyboardMenu01->updateKeyboardOptionMenu(window, mouse, sound, mControlScheme);
	window.clear();
	mKeyboardMenu01->displayMenu01(window);
	mStartOptionState = checkStartOptionState(mKeyboardMenu01->checkOptionState());
	mOptionMenuState = mKeyboardMenu01->checkOptionState();
}

void gameState::drawWorldMap(sf::RenderWindow &window, sf::Vector2i &mouse, MusicManager &music, SoundManager &sound) // Draw World Map
{
	mWorldMap01->updateWorldMap(window, mouse);
	window.clear();
	mWorldMap01->displayMenu01(window); //Update mouse in update...
	mStartState = checkStartState(mWorldMap01->checkState());
	mState = mWorldMap01->checkState();
	mStartRegionState = checkStartRegionState(mWorldMap01->getRegion());
	mRegionState = mWorldMap01->getRegion();
	//std::cout << mRegionState << " from world map" << std::endl;

}

void gameState::drawRegionMap(sf::RenderWindow &window, sf::Vector2i &mouse, MusicManager &music, SoundManager &sound) // Draw Region Map
{
	mRegionMap01->updateRegionMap(window, mouse);
	window.clear();
	mRegionMap01->displayMenu01(window); //Update mouse in update...
	mStartState = checkStartState(mRegionMap01->checkState());
	mState = mRegionMap01->checkState();
	mStartRegionState = checkStartRegionState(mRegionMap01->checkRegionState());
	mRegionState = mRegionMap01->checkRegionState();
	//std::cout << mRegionState << " from region map" << std::endl;
}


void gameState::drawInGame(sf::RenderWindow &window, sf::Vector2i &mouse, MusicManager &music, SoundManager &sound, AnimeManager &anime) // Draw and Update Ingame
{
#pragma region Outdate
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
#pragma endregion

	window.clear();

	mInGameBackground->setMapname(mMap01->mSavefile);
	mBeforeDialogue = mDialogManager->checkBeforeDialogue(mMap01->mSavefile);
	mAfterDialogue = mDialogManager->checkAfterDialogue(mMap01->mSavefile);


#pragma region Check if there is Dialogue
	if (mBeforeDialogue)
	{
		mDialogSwitch = 0;
		//mDialogSwitch = 1;
	}
	else if (mAfterDialogue)
	{
		mDialogSwitch = 2;
		//mDialogSwitch = 1;
	}
	else
	{
		mDialogSwitch = 1;
	}
#pragma endregion

	mInGameBackground->write(mMap01->getTurnCount(), mMap01->getGrass(), mMap01->getHedges(), mMap01->getDandelions(), mMap01->getGoals());
	mInGameBackground->drawBackgroundTop(window);
	mMap01->update(sound);
	mMap01->render(window, anime, mouse);
	mInGameBackground->drawBackgroundBottom(window);


	switch (mDialogSwitch)
	{
		case 0: //Before, Dialogue
		{
			mDialogManager->playBeforeDialogue(mMap01->mSavefile, window);
			break;
		}
		case 1:
		{
			#pragma region Structure

			if (mControlScheme == 0) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0) && flagSwap) {
					flagSwap = false;
					//flagKeyPressed = true;
					mMap01->getPlayer()->swapEquipped();
				}
				if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0) && !flagSwap) {
					flagSwap = true;
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1) && flagDownLeft /*&& !flagKeyPressed*/) {
					flagDownLeft = false;
					//flagKeyPressed = true;
					mMap01->getPlayer()->changeAnimation(2);
					mMap01->beginTurn(1);

				}
				if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1) && !flagDownLeft /*&& flagKeyPressed*/) {
					flagDownLeft = true;
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2) && flagDown /*&& !flagKeyPressed*/) {
					flagDown = false;
					//flagKeyPressed = true;
					mMap01->beginTurn(2);
					mMap01->getPlayer()->changeAnimation(1);
				}
				if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2) && !flagDown /*&& flagKeyPressed*/) {
					flagDown = true;
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3) && flagDownRight /*&& !flagKeyPressed*/) {
					flagDownRight = false;
					//flagKeyPressed = true;
					mMap01->beginTurn(3);
					mMap01->getPlayer()->changeAnimation(8);
				}
				if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3) && !flagDownRight /*&& flagKeyPressed*/) {
					flagDownRight = true;
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4) && flagLeft /*&& !flagKeyPressed*/) {
					flagLeft = false;
//					std::cout << "aaaaaaaaaaaaaaa" << std::endl;
					//flagKeyPressed = true;
					mMap01->getPlayer()->changeAnimation(3);
					mMap01->beginTurn(4);
				}
				if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4) && !flagLeft /*&& flagKeyPressed*/) {
					flagLeft = true;
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6) && flagRight /*&& !flagKeyPressed*/) {
					flagRight = false;
					//flagKeyPressed = true;
					mMap01->beginTurn(6);
					mMap01->getPlayer()->changeAnimation(7);
				}
				if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6) && !flagRight /*&& flagKeyPressed*/) {
					flagRight = true;
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7) && flagUpLeft /*&& !flagKeyPressed*/) {
					flagUpLeft = false;
					//flagKeyPressed = true;
					mMap01->beginTurn(7);
					mMap01->getPlayer()->changeAnimation(4);
				}
				if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7) && !flagUpLeft /*&& flagKeyPressed*/) {
					flagUpLeft = true;
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8) && flagUp /*&& !flagKeyPressed*/) {
					flagUp = false;
					//flagKeyPressed = true;
					mMap01->beginTurn(8);
					mMap01->getPlayer()->changeAnimation(5);
				}
				if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8) && !flagUp /*&& flagKeyPressed*/) {
					flagUp = true;
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad9) && flagUpRight /*&& !flagKeyPressed*/) {
					flagUpRight = false;
					//flagKeyPressed = true;
					mMap01->beginTurn(9);
					mMap01->getPlayer()->changeAnimation(6);
				}
				if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad9) && !flagUpRight /*&& flagKeyPressed*/) {
					flagUpRight = true;
				}

				}

			if (mControlScheme == 1) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && flagSwap) {
					flagSwap = false;
					//flagKeyPressed = true;
				mMap01->getPlayer()->swapEquipped();
			}
				if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !flagSwap) {
					flagSwap = true;
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && flagDownLeft /*&& !flagKeyPressed*/) {
					flagDownLeft = false;
					//flagKeyPressed = true;
					mMap01->beginTurn(1);
					mMap01->getPlayer()->changeAnimation(2);

			}
				if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && !flagDownLeft /*&& flagKeyPressed*/) {
					flagDownLeft = true;
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && flagDown /*&& !flagKeyPressed*/) {
					flagDown = false;
					//flagKeyPressed = true;
					mMap01->beginTurn(2);
					mMap01->getPlayer()->changeAnimation(1);
				}
				if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !flagDown /*&& flagKeyPressed*/) {
					flagDown = true;
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::X) && flagDownRight /*&& !flagKeyPressed*/) {
					flagDownRight = false;
					//flagKeyPressed = true;
					mMap01->beginTurn(3);
					mMap01->getPlayer()->changeAnimation(8);
				}
				if (!sf::Keyboard::isKeyPressed(sf::Keyboard::X) && !flagDownRight /*&& flagKeyPressed*/) {
					flagDownRight = true;
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && flagLeft /*&& !flagKeyPressed*/) {
					flagLeft = false;
					//flagKeyPressed = true;
					mMap01->beginTurn(4);
					mMap01->getPlayer()->changeAnimation(3);
			}
				if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !flagLeft /*&& flagKeyPressed*/) {
					flagLeft = true;
			}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && flagRight /*&& !flagKeyPressed*/) {
					flagRight = false;
					//flagKeyPressed = true;
					mMap01->beginTurn(6);
					mMap01->getPlayer()->changeAnimation(7);
			}
				if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !flagRight /*&& flagKeyPressed*/) {
					flagRight = true;
			}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && flagUpLeft /*&& !flagKeyPressed*/) {
					flagUpLeft = false;
					//flagKeyPressed = true;
					mMap01->beginTurn(7);
					mMap01->getPlayer()->changeAnimation(4);
			}
				if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && !flagUpLeft /*&& flagKeyPressed*/) {
					flagUpLeft = true;
			}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && flagUp /*&& !flagKeyPressed*/) {
					flagUp = false;
					//flagKeyPressed = true;
					mMap01->beginTurn(8);
					mMap01->getPlayer()->changeAnimation(5);
			}
				if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !flagUp /*&& flagKeyPressed*/) {
					flagUp = true;
			}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && flagUpRight /*&& !flagKeyPressed*/) {
					flagUpRight = false;
					//flagKeyPressed = true;
					mMap01->beginTurn(9);
					mMap01->getPlayer()->changeAnimation(6);
				}
				if (!sf::Keyboard::isKeyPressed(sf::Keyboard::E) && !flagUpRight /*&& flagKeyPressed*/) {
					flagUpRight = true;
			}

			}


			mStartState = checkStartState(mMap01->checkState());
			mState = mMap01->checkState();
#pragma endregion

			break;
		}
		case 2: //After, Dialogue
		{
			mDialogManager->playAfterDialogue(mMap01->mSavefile, window);
			break;
		}

	}


}

void gameState::gameStatesHandler(sf::RenderWindow &window, sf::Vector2i &mouse, MusicManager &music, SoundManager &sound, AnimeManager &anime) // Game State Handler
{
	switch (mState) //switch that hold the states of the game
	{
	case 1:
	{ //Game state 1. in game. 

		if (mStartState) {
			if (mRegionMusic == 1) {
				music.setMusic(3);
			}
			else if (mRegionMusic == 2) {
				music.setMusic(4);
			}
			else if (mRegionMusic == 3) {
				music.setMusic(5);
			}
			else if (mRegionMusic == 4) {
				music.setMusic(7);
			}
			else if (mRegionMusic == 5) {
				music.setMusic(8);
			}
			sound.playSound(10.5f);
			sound.playSound(10.4f);
			//mMap01->scale(window);
			mStartState = false;
			//Startar musik osv
		}
		drawInGame(window, mouse, music, sound, anime);
		if (mMap01->getTurnCount() >= mMap01->getMaxTurns()) {
			//Lägg till en maxvariabel för varje induviduell bana. Eventuellt lägga mappsen i en array så man
			//kan välja vilken banas maxvärde man ska anvädnda för att veta om det är gameover. Ex: Maps[i]->maxTurnCount

				mState = 6;
				mStartState = true;


			//if (mMap01->mTurnCount >= mMap01->mLoseRounds) {
			//	mState = 5;
			//	mStartState = true;
			//}

			////For now, just testing phase of Winning screen. Need Winning condition for the map.
			//if (mMap01->mTurnCount >= mMap01->mWinRounds) {
			//	mState = 6;
			//	mStartState = true;
			//}
		}
		break;
	}
	case 2: { //Case 2, Draw ingame menu
		if (mStartState) {
			music.setMusic(6);
			mInGameMenu01->scale(window);
			mStartState = false;
			sound.stopSound(10.4f);
			sound.stopSound(10.5f);
			sound.playSound(10.6f);
			//Starta musik osv
		}
		drawInGameMenu(window, mouse, music, sound);
		break;
	}
	case 3: { //State 3. Start menu.
		if (mStartState) {
			music.setMusic(0);
			mStartMenu01->scale(window);
			mStartState = false;
			//Startar musik osv
		}
		drawStartMenu(window, mouse, music, sound);
		break;
	}
	case 4: { //state 4. option.

		switch (mOptionMenuState)
		{
		case 1: { //state 1. Option.
			if (mStartOptionState) {
				music.setMusic(6);
				mOptionMenu01->scale(window);
				mStartOptionState = false;
				mStartState = false;
				//Starta musik osv
			}
			drawOptionMenu(window, mouse, music, sound);
			break;
		}
		case 2: { //state 2. SoundMenu.
			if (mStartOptionState) {
				music.setMusic(6);
				mSoundmenu01->scale(window);
				mStartOptionState = false;
				mStartState = false;
				//Starta musik osv
			}
			drawSoundMenu(window, mouse, music, sound);
			break;
		}
		case 3: { //state 3. KeyboardSettings.
			if (mStartOptionState) {
				music.setMusic(6);
				mKeyboardMenu01->scale(window);
				mStartOptionState = false;
				mStartState = false;
				//Starta musik osv
			}
			drawKeyboardMenu(window, mouse, music, sound);
			break;
		}
				/*default:
					break;*/
		}

		break;
	}
	case 5: { //state 5. GameOver.
		if (mStartState) {
			music.setMusic(8);
			mGameOverMenu01->scale(window);
			mStartState = false;
			sound.stopSound(10.4f);
			sound.playSound(10.6f);
			//Starta musik osv
		}
		drawGameOverMenu(window, mouse, music, sound);
		break;
	}
	case 6: { //state 6. WinMenu.
		if (mStartState) {
			music.setMusic(0);
			mWinMenu01->scale(window);
			mStartState = false;
			sound.stopSound(10.4f);
			sound.playSound(10.6f);
			//Starta musik osv
		}
		drawWinMenu(window, mouse, music, sound);
		break;
	}
	case 7: //State 7. World Map
		mPlayer->setMower(mLawnMowers.at(mRegionMap01->getMower()));
		mPlayer->setHedgeTool(mHedgeTools.at(mRegionMap01->getHedgeCutter()));

		switch (mRegionState) {
		case 0:
			if (mStartRegionState || mStartState) {
				music.setMusic(2);
				mWorldMap01->scale(window);
				mStartState = false;
				mStartRegionState = false;
				//Starta musik osv
			}
			drawWorldMap(window, mouse, music, sound);
			break;
		case 1:
			mRegionMap01->setRegionState(1);
			if (mStartRegionState || mStartState) {
				music.setMusic(1);
				mRegionMusic = 1;
				mRegionMap01->scale(window);
				mStartState = false;
				mStartRegionState = false;
				//Starta musik osv
			}
			mRegionMap01->setRegionState(1);
			drawRegionMap(window, mouse, music, sound);
			break;
		case 2:
			if (mStartRegionState || mStartState) {
				music.setMusic(1);
				mRegionMusic = 2;
				mRegionMap01->scale(window);
				mStartState = false;
				mStartRegionState = false;
				//Starta musik osv
			}
			mRegionMap01->setRegionState(2);
			drawRegionMap(window, mouse, music, sound);
			break;
		case 3:
			if (mStartRegionState || mStartState) {
				music.setMusic(1);
				mRegionMusic = 3;
				mRegionMap01->scale(window);
				mStartState = false;
				mStartRegionState = false;
				//Starta musik osv
			}
			mRegionMap01->setRegionState(3);
			drawRegionMap(window, mouse, music, sound);
			break;

		case 4:
			if (mStartRegionState || mStartState) {
				music.setMusic(1);
				mRegionMusic = 4;
				mRegionMap01->scale(window);
				mStartState = false;
				mStartRegionState = false;
				//Starta musik osv
			}
			mRegionMap01->setRegionState(4);
			drawRegionMap(window, mouse, music, sound);
			break;

		case 5:
			if (mStartRegionState || mStartState) {
				music.setMusic(1);
				mRegionMusic = 5;
				mRegionMap01->scale(window);
				mStartState = false;
				mStartRegionState = false;
				//Starta musik osv
			}
			mRegionMap01->setRegionState(5);
			drawRegionMap(window, mouse, music, sound);
			break;

			//testinggg
			/*		case 1:
			mRegionMap01->setRegionState(mRegionState);
			drawRegionMap(window, mouse, music, sound);
			break;
		case 2:
			mRegionMap01->setRegionState(mRegionState);
			drawRegionMap(window, mouse, music, sound);
			break;*/
		}
		break;

	case 8:
		mRegionState = 0;
		loadMap();
		mState = 1;
		break;
		/*case 8:
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
			break;*/

			/*default:
				std::cout << "default gamestate";
				break;
			}*/

			//Outside the gamestates, check if the user changes the gamestate.
			/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
			{
				mState = 1;
				mStartState = true;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				mState = 2;
				mStartState = true;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
			{
				mState = 3;
				mStartState = true;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
			{
				mState = 4;
				mStartState = true;
			}*/


		if (mStartMenu01->reset == true || mWinMenu01->reset == true)
		{
			mWinMenu01->reset = false;
			mStartMenu01->reset = false;
			resetMap();
		}


		/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
		{
			mState = 0;
		}*/


	}
}

void gameState::resetMap(){
	for (std::vector<Mower*>::size_type i = 0; i < mLawnMowers.size(); i++) {
		mLawnMowers[i]->resetStats();
	}
	//mMap01->deleteContent();
	std::cout << "reset" << "" << "reset" << "" << "reset" << "" << "reset" << "" << "reset" << "" << "reset" << "" << "reset" << "" << "reset";

	mMap01->resetGrid();
	//mMap01->spawnObjects();
	//mObjects = mMap01->getObjects();
	//mPlayer = mMap01->getPlayer();
	//mNpcs = mMap01->getNpcs();
	//mLongObjects = mMap01->getLongObjects();
	// Skriver ut position för alla object
	/*for (ObjectsVector::size_type i = 0; i < mObjects.size(); i++){
		std::cout << mObjects[i]->getPosX() << " " << mObjects[i]->getPosY() << std::endl;
	}*/
}

bool gameState::checkStartState(int lowerState){
	if (mState == lowerState) {
		return false;
	}
	else {
		return true;
	}
}

bool gameState::checkStartOptionState(int lowerState) {
	if (mOptionMenuState == lowerState) {
		return false;
	}
	else {
		return true;
	}
}

bool gameState::checkStartRegionState(int lowerState) {
	if (mRegionState == lowerState) {
		return false;
	}
	else {
		return true;
	}
}

void gameState::loadMap() {
	//mMap01->~Map1();
	delete mMap01;
	
	std::string levelToLoad = mRegionMap01->loadLevel();

	mMap01 = new Map1(levelToLoad, mPlayer/*, "Maps/patrols/Patrols_testing.txt"*/);

	mMap01->spawnObjects();

	/*mObjects.clear();
	mObjects = mMap01->getObjects();

	mNpcs.clear();
	mNpcs = mMap01->getNpcs();

	mLongObjects.clear();
	mLongObjects = mMap01->getLongObjects();*/
}