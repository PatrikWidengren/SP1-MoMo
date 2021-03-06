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

	mKeyboardMenu01 = new KeyboardOptionMenu((float)window.getSize().x, (float)window.getSize().y);
	mSoundmenu01 = new SoundMenu((float)window.getSize().x, (float)window.getSize().y);
	mInGameMenu01 = new inGameMenu((float)window.getSize().x, (float)window.getSize().y);
	mStartMenu01 = new startMenu((float)window.getSize().x, (float)window.getSize().y);
	mOptionMenu01 = new optionMenu((float)window.getSize().x, (float)window.getSize().y);
	mGameOverMenu01 = new GameOverMenu((float)window.getSize().x, (float)window.getSize().y);
	mWinMenu01 = new WinMenu((float)window.getSize().x, (float)window.getSize().y);
	mWorldMap01 = new WorldMap((float)window.getSize().x, (float)window.getSize().y);
	mRegionMap01 = new RegionMap((float)window.getSize().x, (float)window.getSize().y);
	mVideoOptionMenu = new VideoOptionMenu((float)window.getSize().x, (float)window.getSize().y);

	mInGameBackground = new InGameBackground();

	mDialogManager = new DialogManager(window);

	mLawnMowers.push_back(new LawnMower(2, 1, 1, 1, 10000));
	mLawnMowers.push_back(new LawnMower(3, 1, 1, 2, 2000));
	mLawnMowers.push_back(new LawnMower(4, 1, 1, 2, 3000));
	mLawnMowers.push_back(new LawnMower(3, 2, 1, 1, 3000));
	mLawnMowers.push_back(new LawnMower(4, 2, 2, 2, 3000));
	mHedgeTools.push_back(new HedgeCutter(1, 1));
	mHedgeTools.push_back(new HedgeCutter(2, 1));

	mPlayer = new Player(mLawnMowers.at(mCurMower), mHedgeTools.at(mCurHedgeTool));
	mMap01 = new Map1("map01a01.txt", mPlayer/*, "Maps/patrols/Patrols_testing.txt"*/);

	mMap01->spawnObjects();
	//mMap01->render(window, anime);
	//mObjects = mMap01->getObjects();
	//mPlayer = mMap01->getPlayer();
	//mNpcs = mMap01->getNpcs();
	//mLongObjects = mMap01->getLongObjects();
	// Skriver ut position f�r alla object

	//This thing broke the code, no clue why
	/*for (ObjectsVector::size_type i = 0; i < mObjects.size(); i++){
		std::cout << mObjects[i]->getPosX() << " " << mObjects[i]->getPosY() << std::endl;
	}*/
}

gameState::~gameState()
{
	while (!mLawnMowers.empty()) {
		delete mLawnMowers.at(0);
		mLawnMowers.erase(mLawnMowers.begin());
	}
	while (!mHedgeTools.empty()) {
		delete mHedgeTools.at(0);
		mHedgeTools.erase(mHedgeTools.begin());
	}
}

void gameState::drawInGameMenu(sf::RenderWindow &window, sf::Vector2i &mouse, MusicManager &music, SoundManager &sound, AnimeManager &anime) // Draw In Game Menu
{
	mInGameMenu01->updateInGameMenu(window, mouse, sound);
	window.clear();
	mInGameBackground->write(mMap01->getTurnsLeft(), mMap01->getGrass(), mMap01->getHedges(), mMap01->getDandelions(), mMap01->getGoals());
	mInGameBackground->getInfo(mPlayer->mower()->getMaxMom(), mPlayer->mower()->getMinMom(), mPlayer->mower()->getCurMom(), mPlayer->mower()->getFallVal(), mPlayer->mower()->getRiseVal(), mPlayer->getMowerEquipped());
	mInGameBackground->selectMomentumSprite();
	mInGameBackground->scale(window);
	mInGameBackground->drawBackgroundTop(window);
	mInGameBackground->selectLawnmowerSprite(mRegionMap01->getMower());
	mInGameBackground->selectHedgecutterSprite();
	mMap01->render(window, mouse);
	mInGameBackground->drawBackgroundBottom(window);

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

void gameState::drawVideoOptionMenu(sf::RenderWindow &window, sf::Vector2i &mouse, MusicManager &music, SoundManager &sound) // Draw VideoOption Menu
{
	mVideoOptionMenu->updateVideoOptionMenu(window, mouse, sound);
	window.clear();
	mVideoOptionMenu->displayMenu01(window);
	mStartOptionState = checkStartOptionState(mVideoOptionMenu->checkOptionState());
	mOptionMenuState = mVideoOptionMenu->checkOptionState();
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
	mInGameBackground->write(mMap01->getTurnsLeft(), mMap01->getGrass(), mMap01->getHedges(), mMap01->getDandelions(), mMap01->getGoals());
	mInGameBackground->getInfo(mPlayer->mower()->getMaxMom(), mPlayer->mower()->getMinMom(), mPlayer->mower()->getCurMom(), mPlayer->mower()->getFallVal(), mPlayer->mower()->getRiseVal(), mPlayer->getMowerEquipped());
	mInGameBackground->selectMomentumSprite();
	mInGameBackground->scale(window);
	mInGameBackground->drawBackgroundTop(window);
	mInGameBackground->selectLawnmowerSprite(mRegionMap01->getMower());
	mInGameBackground->selectHedgecutterSprite();
	mMap01->render(window, mouse);
	mInGameBackground->drawBackgroundBottom(window);
	mWinMenu01->displayMenu01(window);
	if (mInGameBackground->getMedal() == "Gold") {
		mWorldMap01->addDemDopies(90);
		//sound.playSound(10.9f);
	}
	else
		if (mInGameBackground->getMedal() == "Silver") {
			mWorldMap01->addDemDopies(60);
			//sound.playSound(10.8f);
		}
		else
			if (mInGameBackground->getMedal() == "Bronze") {
				mWorldMap01->addDemDopies(40);
				//sound.playSound(10.7f);
			}
	mStartState = checkStartState(mWinMenu01->checkState());
	mState = mWinMenu01->checkState();
}
int gameState::getControlScheme()
{
	return mControlScheme;
}
void gameState::setControlScheme(int controlscheme)
{
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

	mPlayer->mdopies = mWorldMap01->getDemDopies();
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

	//mBeforeDialogue = mDialogManager->checkBeforeDialogue(mMap01->mSavefile);
	//mAfterDialogue = mDialogManager->checkAfterDialogue(mMap01->mSavefile);


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
#pragma endregion*/

	mInGameBackground->write(mMap01->getTurnsLeft(), mMap01->getGrass(), mMap01->getHedges(), mMap01->getDandelions(), mMap01->getGoals());
	mInGameBackground->getInfo(mPlayer->mower()->getMaxMom(), mPlayer->mower()->getMinMom(), mPlayer->mower()->getCurMom(), mPlayer->mower()->getFallVal(), mPlayer->mower()->getRiseVal(), mPlayer->getMowerEquipped());
	mInGameBackground->selectMomentumSprite();
	mInGameBackground->scale(window);
	mInGameBackground->drawBackgroundTop(window);
	mInGameBackground->selectLawnmowerSprite(mRegionMap01->getMower());
	mInGameBackground->selectHedgecutterSprite();
	mMap01->update(sound, window);
	mMap01->render(window, mouse);
	mInGameBackground->drawBackgroundBottom(window);

	switch (mDialogSwitch)
	{
	case 0: //Before, Dialogue
	{
		//mDialogManager->playBeforeDialogue(mMap01->mSavefile, window);
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
				mMap01->beginTurn(1);

			}
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1) && !flagDownLeft /*&& flagKeyPressed*/) {
				flagDownLeft = true;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2) && flagDown /*&& !flagKeyPressed*/) {
				flagDown = false;
				//flagKeyPressed = true;
				mMap01->beginTurn(2);
			}
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2) && !flagDown /*&& flagKeyPressed*/) {
				flagDown = true;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3) && flagDownRight /*&& !flagKeyPressed*/) {
				flagDownRight = false;
				//flagKeyPressed = true;
				mMap01->beginTurn(3);
			}
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3) && !flagDownRight /*&& flagKeyPressed*/) {
				flagDownRight = true;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4) && flagLeft /*&& !flagKeyPressed*/) {
				flagLeft = false;
				//					std::cout << "aaaaaaaaaaaaaaa" << std::endl;
									//flagKeyPressed = true;
				mMap01->beginTurn(4);
			}
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4) && !flagLeft /*&& flagKeyPressed*/) {
				flagLeft = true;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6) && flagRight /*&& !flagKeyPressed*/) {
				flagRight = false;
				//flagKeyPressed = true;
				mMap01->beginTurn(6);
			}
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6) && !flagRight /*&& flagKeyPressed*/) {
				flagRight = true;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7) && flagUpLeft /*&& !flagKeyPressed*/) {
				flagUpLeft = false;
				//flagKeyPressed = true;
				mMap01->beginTurn(7);
			}
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7) && !flagUpLeft /*&& flagKeyPressed*/) {
				flagUpLeft = true;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8) && flagUp /*&& !flagKeyPressed*/) {
				flagUp = false;
				//flagKeyPressed = true;
				mMap01->beginTurn(8);
			}
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8) && !flagUp /*&& flagKeyPressed*/) {
				flagUp = true;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad9) && flagUpRight /*&& !flagKeyPressed*/) {
				flagUpRight = false;
				//flagKeyPressed = true;
				mMap01->beginTurn(9);
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
			}
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && !flagDownLeft /*&& flagKeyPressed*/) {
				flagDownLeft = true;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && flagDown /*&& !flagKeyPressed*/) {
				flagDown = false;
				//flagKeyPressed = true;
				mMap01->beginTurn(2);
			}
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !flagDown /*&& flagKeyPressed*/) {
				flagDown = true;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::X) && flagDownRight /*&& !flagKeyPressed*/) {
				flagDownRight = false;
				//flagKeyPressed = true;
				mMap01->beginTurn(3);
			}
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::X) && !flagDownRight /*&& flagKeyPressed*/) {
				flagDownRight = true;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && flagLeft /*&& !flagKeyPressed*/) {
				flagLeft = false;
				//flagKeyPressed = true;
				mMap01->beginTurn(4);
			}
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !flagLeft /*&& flagKeyPressed*/) {
				flagLeft = true;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && flagRight /*&& !flagKeyPressed*/) {
				flagRight = false;
				//flagKeyPressed = true;
				mMap01->beginTurn(6);
			}
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !flagRight /*&& flagKeyPressed*/) {
				flagRight = true;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && flagUpLeft /*&& !flagKeyPressed*/) {
				flagUpLeft = false;
				//flagKeyPressed = true;
				mMap01->beginTurn(7);
			}
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && !flagUpLeft /*&& flagKeyPressed*/) {
				flagUpLeft = true;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && flagUp /*&& !flagKeyPressed*/) {
				flagUp = false;
				//flagKeyPressed = true;
				mMap01->beginTurn(8);
			}
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !flagUp /*&& flagKeyPressed*/) {
				flagUp = true;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && flagUpRight /*&& !flagKeyPressed*/) {
				flagUpRight = false;
				//flagKeyPressed = true;
				mMap01->beginTurn(9);
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
		//mDialogManager->playAfterDialogue(mMap01->mSavefile, window);
		break;
	}

	}


}

void gameState::gameStatesHandler(sf::RenderWindow &window, sf::Vector2i &mouse, MusicManager &music, SoundManager &sound, AnimeManager &anime) // Game State Handler
{
	switch (mState) //switch that hold the states of the game
	{
	case 0:
		loadMap(window);
		mPlayer->reset();
		mState = 1;
		break;
	case 1:
	{ //Game state 1. in game. 

		if (mStartState) {
			mInGameBackground->resetInGameHud();

			if (mRegionMusic == 1 || mRegionMusic == 2 || mRegionMusic == 3) {
				mBankName = "Resource Files/Audio/Build/Desktop/Generic.bank";
			}
			else if (mRegionMusic == 4) {
				mBankName = "Resource Files/Audio/Build/Desktop/Asia.bank";
			}
			else if (mRegionMusic == 5) {
				mBankName = "Resource Files/Audio/Build/Desktop/Temple.bank";
			}


			if (mBankName != mSaveBank || mSaveBank == NULL) {
				delete mBank;
				sound.unload();

				mBank = new AudioBank(mBankName);
				mSaveBank = mBankName;

				std::string str = "Loaded: ";
				str += mSaveBank;
				LogHandler::log("State", str.c_str());
			}
			else
			{
				std::string str = mSaveBank;
				str += " already loaded";
				LogHandler::log("State", str.c_str());
			}

			if (mRegionMusic == 1 || mRegionMusic == 2 || mRegionMusic == 3) {
				sound.loadSounds(1);
				int i = rand() % 3 + 1;
				std::string str = "Music/Levels/Generic" + std::to_string(i);
				music.setMusic(str.c_str()); //Generic123
			}

			else if (mRegionMusic == 4)
			{
				sound.loadSounds(3);
				music.setMusic("Music/Levels/Asia"); //Temple8
			}
			else if (mRegionMusic == 5) {
				sound.loadSounds(2);
				std::string str = mRegionMap01->loadLevel();

				if (str != "map05a08.txt")
				music.setMusic("Music/Levels/Temple1-7"); //Temple1-7
				else
				music.setMusic("Music/Levels/Temple8"); //Temple8
			}

			if (sound.getParamValue(1, "End") == 1)
			{
				sound.setParamValue(1, "End", 0);
			}


			sound.playSound(1);
			//mMap01->scale(window);
			mStartState = false;
			//Startar musik osv
		}

		if (mMap01->getTurnCount() >= mMap01->getMaxTurns()) {
			//L�gg till en maxvariabel f�r varje induviduell bana. Eventuellt l�gga mappsen i en array s� man
			//kan v�lja vilken banas maxv�rde man ska anv�dnda f�r att veta om det �r gameover. Ex: Maps[i]->maxTurnCount
			if (mInGameBackground->getMedal() == "Gold") {
				mWorldMap01->addDemDopies(90);
				//sound.playSound(10.9f);
			}
			else
				if (mInGameBackground->getMedal() == "Silver") {
					mWorldMap01->addDemDopies(60);
					//sound.playSound(10.8f);
				}
				else
					if (mInGameBackground->getMedal() == "Bronze") {
						mWorldMap01->addDemDopies(40);
						//sound.playSound(10.7f);
					}
			/*mInGameBackground->write(mMap01->getTurnsLeft(), mMap01->getGrass(), mMap01->getHedges(), mMap01->getDandelions(), mMap01->getGoals());
			mInGameBackground->getInfo(mPlayer->mower()->getMaxMom(), mPlayer->mower()->getMinMom(), mPlayer->mower()->getCurMom(), mPlayer->mower()->getFallVal(), mPlayer->mower()->getRiseVal(), mPlayer->getMowerEquipped());
			mInGameBackground->selectMomentumSprite();
			mInGameBackground->scale(window);
			mInGameBackground->drawBackgroundTop(window);
			mInGameBackground->selectLawnmowerSprite(mRegionMap01->getMower());
			mInGameBackground->selectHedgecutterSprite();
			mMap01->render(window, mouse);
			mInGameBackground->drawBackgroundBottom(window);

			std::cout << mWorldMap01->getDemDopies() << std::endl;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){*/
			mState = 6;
			mStartState = true;
			//}	
		}
		/*else if(mMap01->mTurnCount >= mMap01->mLoseRounds) {
			mState = 5;
			mStartState = true;
		}*/
		else {
			drawInGame(window, mouse, music, sound, anime);
		}
		break;
	}
	case 2: { //Case 2, Draw ingame menu
		if (mStartState) {
			music.setMusic("Music/Levels/Ice");
			mInGameMenu01->scale(window);
			mStartState = false;
			sound.setParamValue(1, "End", 1);
			//Starta musik osv
		}
		drawInGameMenu(window, mouse, music, sound, anime);
		break;
	}
	case 3: { //State 3. Start menu.
		if (mStartState) {
			music.setMusic("Music/Menu/Title");
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
				music.setMusic("Music/Levels/Ice");
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
				music.setMusic("Music/Levels/Ice");
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
				music.setMusic("Music/Levels/Ice");
				mKeyboardMenu01->scale(window);
				mStartOptionState = false;
				mStartState = false;
				//Starta musik osv
			}
			drawKeyboardMenu(window, mouse, music, sound);
			break;
		}
		case 4:
		{ //state 3. VideoSettings.
			if (mStartOptionState) {
				music.setMusic("Music/Levels/Ice");
				mVideoOptionMenu->scale(window);
				mStartOptionState = false;
				mStartState = false;
				//Starta musik osv
			}
			drawVideoOptionMenu(window, mouse, music, sound);
			break;
		}

		}

		break;
	}
	case 5: { //state 5. GameOver.
		if (mStartState) {
			music.setMusic("Music/Levels/Asian");
			mGameOverMenu01->scale(window);
			mStartState = false;
			sound.setParamValue(1, "End", 1);
			//Starta musik osv
		}
		drawGameOverMenu(window, mouse, music, sound);
		break;
	}
	case 6: { //state 6. WinMenu.
		if (mStartState) {
			music.setMusic("Music/Menu/Title");
			mWinMenu01->scale(window);
			mStartState = false;
			sound.setParamValue(1, "End", 1);
			//Starta musik osv
		}
		drawWinMenu(window, mouse, music, sound);
		break;
	}
	case 7: { //State 7. World Map
		mPlayer->setMower(mLawnMowers.at(mRegionMap01->getMower()), mRegionMap01->getMower());
		mPlayer->setHedgeTool(mHedgeTools.at(mRegionMap01->getHedgeCutter()), mRegionMap01->getHedgeCutter());

		switch (mRegionState) {
		case 0:
			if (mStartRegionState || mStartState) {
				music.setMusic("Music/Menu/WorldMap");
				mWorldMap01->scale(window);
				mStartState = false;
				mStartRegionState = false;
				//Starta musik osv
			}
			drawWorldMap(window, mouse, music, sound);
			break;
		case 1:
			if (mStartRegionState || mStartState) {
				music.setMusic("Music/Menu/Miyoda");
				mRegionMusic = 1;
				mRegionMap01->scale(window);
				mStartState = false;
				mStartRegionState = false;
				//Starta musik osv
				mRegionMap01->setRegionState(1);
			}
			drawRegionMap(window, mouse, music, sound);
			break;
		case 2:
			if (mStartRegionState || mStartState) {
				music.setMusic("Music/Menu/Miyoda");
				mRegionMusic = 2;
				mRegionMap01->scale(window);
				mStartState = false;
				mStartRegionState = false;
				//Starta musik osv
				mRegionMap01->setRegionState(2);
			}
			drawRegionMap(window, mouse, music, sound);
			break;
		case 3:
			if (mStartRegionState || mStartState) {
				music.setMusic("Music/Menu/Miyoda");
				mRegionMusic = 3;
				mRegionMap01->scale(window);
				mStartState = false;
				mStartRegionState = false;
				//Starta musik osv
				mRegionMap01->setRegionState(3);
			}
			drawRegionMap(window, mouse, music, sound);
			break;

		case 4:
			if (mStartRegionState || mStartState) {
				music.setMusic("Music/Menu/Miyoda");
				mRegionMusic = 4;
				mRegionMap01->scale(window);
				mStartState = false;
				mStartRegionState = false;
				//Starta musik osv
				mRegionMap01->setRegionState(4);
			}
			drawRegionMap(window, mouse, music, sound);
			break;

		case 5:
			if (mStartRegionState || mStartState) {
				music.setMusic("Music/Menu/Miyoda");
				mRegionMusic = 5;
				mRegionMap01->scale(window);
				mStartState = false;
				mStartRegionState = false;
				//Starta musik osv
				mRegionMap01->setRegionState(5);
			}
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
	}
	case 8: {
		mRegionState = 0;
		loadMap(window);
		mPlayer->reset();
		mState = 1;
		break;
	}
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
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
			{
				mState = 1;
				mStartState = true;
			}
			/*
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


			//if (mStartMenu01->reset == true || mWinMenu01->reset == true)
			//{
			//	mWinMenu01->reset = false;
			//	mStartMenu01->reset = false;
			//	resetMap();
			//}


			/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
			{
				mState = 0;
			}*/


	}
}


bool gameState::checkStartState(int lowerState)
{
	if (mState == lowerState) {
		return false;
	}

	else {
		return true;
	}
}

bool gameState::checkStartOptionState(int lowerState)
{
	if (mOptionMenuState == lowerState) {
		return false;
	}
	else {
		return true;
	}
}

bool gameState::checkStartRegionState(int lowerState)
{
	if (mRegionState == lowerState) {
		return false;
	}
	else {
		return true;
	}
}

void gameState::loadMap(sf::RenderWindow &window)
{
	//mMap01->~Map1();
	delete mMap01;

	std::string levelToLoad = mRegionMap01->loadLevel();

	mMap01 = new Map1(levelToLoad, mPlayer/*, "Maps/patrols/Patrols_testing.txt"*/);
	mInGameBackground->setMapname(levelToLoad);
	int meepStartAnimation = mMap01->getMeepSpawnDirection();

	if (meepStartAnimation == 1) {
		mPlayer->changeAnimation(4);
	}
	if (meepStartAnimation == 2) {
		mPlayer->changeAnimation(6);
	}
	if (meepStartAnimation == 3) {
		mPlayer->changeAnimation(8);
	}
	if (meepStartAnimation == 4) {
		mPlayer->changeAnimation(2);
	}

	mMap01->spawnObjects();

	/*mObjects.clear();
	mObjects = mMap01->getObjects();

	mNpcs.clear();
	mNpcs = mMap01->getNpcs();

	mLongObjects.clear();
	mLongObjects = mMap01->getLongObjects();*/
}