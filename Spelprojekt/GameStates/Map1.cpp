#include "Map1.h"
#include <iostream>
#include <iomanip>
//test

using namespace std;

static const float widthOnTile = 64.0f;
static const float heightOnTile = 52.0f;
static const int widthTile = 64;
static const int heightTile = 52;
static const int pushGrassX = -32;
static const int pushGrassY = -76;
static const int pushFenceY = -76;
static const int pushMeepX = -96;
static const int pushMeepY = -116;
static const int pushNpcX = 0;
static const int pushNpcY = -20;

Map1::Map1(string savefile, Player *p /*, string patrolpath*/) {
	mPlayer = p;
	mSavefile = savefile;
	//mPatrolPath = patrolpath;
	getMapInfo();
	Stone::initialize();
	Grass::initialize();
	Fence::initialize();
	Tree::initialize();
	Hedge::initialize();
	Gravel::initialize();
	Dandelion::initialize();
	//Player::initialize();
	CharRand::initialize();
	CharPatrol::initialize();
	Fountain::initialize();
	mRects[0] = new sf::IntRect(sf::Vector2i(1630, 17), sf::Vector2i(265, 90));
}

Map1::~Map1() {
	Stone::finalize();
	Grass::finalize();
	Fence::finalize();
	Tree::finalize();
	Hedge::finalize();
	Gravel::finalize();
	Dandelion::finalize();
	CharRand::finalize();
	CharPatrol::finalize();
	Fountain::finalize();
	for (ObjectsVector::size_type i = 0; i < mObjects.size(); i++) {
		delete mObjects.back();
		mObjects.pop_back();
	}
	for (ObjectsVector::size_type i = 0; i < mLongObjects.size(); i++) {
		delete mLongObjects.back();
		mLongObjects.pop_back();
	}
	//delete mPlayer;
	delete mGrid;
	mNpcs.clear();
	while (!mNpcVector.empty()) {
		delete mNpcVector[0];
		mNpcVector.erase(mNpcVector.begin());
}
}

void Map1::resetGrid(){
	cout << "reset " << "reset " << "reset " << "reset " << "reset " << "reset " << "reset " << "reset " << "reset " << "reset " << "reset " << endl;
	std::vector<coords> startPosList;
	NpcVector npcList;
	for (int j = 0; j < mHeight; j++) {
		for (int i = 0; i < mWidth; i++) {
			coords tempCoords = { i, j };
			if (mNpcs[tempCoords] != 0) {
				mNpcs[tempCoords]->reset();
				coords baseCoords{ mNpcs[tempCoords]->getX(), mNpcs[tempCoords]->getY() };
				startPosList.push_back(baseCoords);
				npcList.push_back(mNpcs[tempCoords]);
				mNpcs.erase(tempCoords);
			}
		}
	}
	for (NpcVector::size_type i = 0; i < npcList.size(); i++) {
		mNpcs[startPosList[i]] = npcList[i];
	}
	//mGrid = createGrid(mWidth, mHeight);
	turnsLeft = 50;
	cutGrass = 0;
	cutHedges = 0;
	cutDandelions = 0;
	mTurnCount = 0;
	mSkipLines = 0;
}

//Skapar array
float** Map1::createGrid(int width, int height) {
	getMapInfo();
	float tempValue;
	const string saveFilePath = "Maps/" + mSavefile;
	ifstream file(saveFilePath);
	file >> tempValue >> tempValue >> tempValue >> tempValue >> tempValue >> tempValue >> tempValue >> tempValue >> tempValue >> tempValue >> tempValue >> tempValue >> tempValue >> tempValue >> tempValue;

	float** array2d;
//	if (width > height) {
		array2d = new float*[height];
		for (int i = 0; i < height; i++) {
			array2d[i] = new float[width];
			for (int j = 0; j < width; j++) {
				//file >> tempValue;
				//array2d[i][j] = tempValue; //anv�nds de h�r s� blir det ingen breakpoint(inte efter typ 20 f�rs�k iallafall)
				//array2d[i][j] = 0.0f;
			}
		}
//	}
	//Skapar grid p� annat s�tt om height �r st�rre �n width
	/*else {
		array2d = new float*[height];
		for (int i = 0; i < height; i++) {
			array2d[i] = new float[width];
			for (int j = 0; j < width; j++) {
				//file >> tempValue;
				//array2d[i][j] = tempValue; //anv�nds de h�r s� blir det ingen breakpoint(inte efter typ 20 f�rs�k iallafall)
				array2d[i][j] = 0.0f;
			}
		}
	}*/

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			file >> tempValue;
			array2d[i][j] = tempValue; //Det �r h�r som det blir n�got fel i heapen + titta uvan f�r mer info
		}
	}

	//cout << "Height=" << mHeight << endl;
	//cout << "Width=" << mWidth << endl;
	//for (int i = 0; i < mHeight; i++) {
	//	for (int j = 0; j < mWidth; j++) {
	//		cout << array2d[i][j] << " ";
	//}
	//	cout << endl;
	//	}


	return array2d;

}

//Loopar igenom array och spawnar alla objekt
//Variabeln totalAmoutOfGrass h�ller koll p� hur m�nga gr�s som skall kunna klippas, samma med hedge & dandelions
//skipLines r�knar varje v�rde som sparas fr�n patrullens .txt fil, f�r att inte ladda samma v�rden f�r flera patruller
int** Map1::getPatrolPath(int &skipLines) {
	string patrolFilePath = "Maps/patrols/patrols_" + mSavefile;
	ifstream file(patrolFilePath);
	int tempValue;
	int patrolPathWidth;
	int patrolPathHeight;

	//Loop f�r att komma f�rbi tidigare patrull-paths
	for (int i = 0; i < skipLines; i++) {
		file >> tempValue;
	}

	file >> patrolPathHeight >> patrolPathWidth;
	skipLines += 2;

	//patrolPathHeight + 1 och patrolPathWidth + 1, eftersom mapeditorn inte sparar en extra nolla, dvs vi skapar en extra nollor h�r
	//h�r sparas bara nollor i hela arrayen
	int** patrolPath;
	patrolPath = new int*[patrolPathHeight + 1];
	for (int i = 0; i < patrolPathHeight + 1; i++) {
		patrolPath[i] = new int[patrolPathWidth + 1];
		for (int j = 0; j < patrolPathWidth + 1; j++) {
			//file >> tempValue;
			patrolPath[i][j] = 0;
		}
	}

	//h�r s�tts v�rdena till patrolPath fr�n .txt fil
	for (int i = 0; i < patrolPathHeight; i++) {
		for (int j = 0; j < patrolPathWidth; j++) {
			file >> tempValue;
			patrolPath[i][j] = tempValue;
			skipLines++;
		}
	}

	return patrolPath;
}

void Map1::spawnObjects() {
	//mPlayer = new Player(new LawnMower(), new HedgeCutter(2, 1));
	mObjects.push_back(new Grass(0, 0, (widthOnTile), (heightOnTile)));
	mObjects.push_back(new Grass(0, 0, (widthOnTile), (heightOnTile)));
	mObjects[1]->setCut();
	mObjects.push_back(new Stone(0, 0, (widthOnTile), (heightOnTile)));
	mObjects.push_back(new Dandelion(0, 0, widthOnTile, heightOnTile));
	mObjects.push_back(new Dandelion(0, 0, widthOnTile, heightOnTile));
	mObjects[4]->setCut();
	mObjects.push_back(new Gravel(0, 0, widthOnTile, heightOnTile));

	mLongObjects.push_back(new Tree(0, 0, (widthOnTile)-31, (heightOnTile)-200)); //Tr�d: plats 0
	mLongObjects.push_back(new Fence(0, 0, (widthOnTile), (heightOnTile)+pushFenceY, 1));
	mLongObjects.push_back(new Fence(0, 0, (widthOnTile), (heightOnTile)+pushFenceY, 2));
	mLongObjects.push_back(new Fence(0, 0, (widthOnTile), (heightOnTile)+pushFenceY, 3));
	mLongObjects.push_back(new Fence(0, 0, (widthOnTile), (heightOnTile)+pushFenceY, 4));
	mLongObjects.push_back(new Fence(0, 0, (widthOnTile), (heightOnTile)+pushFenceY, 5));
	mLongObjects.push_back(new Fence(0, 0, (widthOnTile), (heightOnTile)+pushFenceY, 6));
	mLongObjects.push_back(new Fence(0, 0, (widthOnTile), (heightOnTile)+pushFenceY, 7));
	mLongObjects.push_back(new Fence(0, 0, (widthOnTile), (heightOnTile)+pushFenceY, 8));
	mLongObjects.push_back(new Fence(0, 0, (widthOnTile), (heightOnTile)+pushFenceY, 9));
	mLongObjects.push_back(new Hedge(0, 0, (widthOnTile), (heightOnTile)));
	mLongObjects.push_back(new Hedge(0, 0, (widthOnTile), (heightOnTile)));
	mLongObjects[11]->setCut();
	mLongObjects.push_back(new Fountain(0, 0, widthOnTile, heightOnTile));
	//mNpcs.push_back(new CharRand(0, 0, (widthOnTile), (heightOnTile), 1, true));
	//mNpcs.push_back(new CharPatrol(0, 0, (widthOnTile), (heightOnTile), patrolPath));

	for (ObjectsVector::size_type i = 0; i < mObjects.size(); i++) {
		mObjects[i]->render();
	}

	/*for (NpcMap::size_type i = 0; i < mNpcs.size(); i++){
		mNpcs[i]->render();
	}*/

	for (ObjectsVector::size_type i = 0; i < mLongObjects.size(); i++) {
		mLongObjects[i]->render();
	}
	//mPlayer->render();

	mGrid = createGrid(mWidth, mHeight);
	
	/*for (int i = 0; i < mHeight; i++) {
		for (int j = 0; j < mWidth; j++) {
			cout << mGrid[i][j] << " ";
		}
		cout << endl;
	}*/


	cout << endl << endl << endl;
	for (int j = 0; j < mHeight; j++) {
		for (int i = 0; i < mWidth; i++) {
			if (mGrid[j][i] == 2.0f) {
				totalAmountOfGrass++;
			}
			if (mGrid[j][i] == 2.2f) {
				totalAmountOfDandelions++;
			}
			if (mGrid[j][i] == 6.2f) {
				totalAmountOfDandelions++;
			}
			if (mGrid[j][i] == 7.2f) {
				totalAmountOfDandelions++;
			}
			if (mGrid[j][i] == 6.0f) {
				totalAmountOfGrass++;
			}
			if (mGrid[j][i] == 7.0f) {
				totalAmountOfGrass++;
			}
			if (mGrid[j][i] == 9.0f) {
				totalAmountOfHedges++;
			}
		}
	}

	for (int j = 0; j < mHeight; j++) {
		for (int i = 0; i < mWidth; i++) {
			if (mGrid[j][i] >= 6.0f && mGrid[j][i] < 7.0f) { //Rand Npc Gr�s, temp innan animation
				coords c = { i, j };
				mNpcs[c] = new CharRand(i, j, 2, true);
			}
			else if (mGrid[j][i] >= 7.0f && mGrid[j][i] < 8.0f) {
				coords c = { i, j };
				mNpcs[c] = new CharPatrol(i, j, getPatrolPath(mSkipLines));
			}
			else if (mGrid[j][i] >= 5.0f && mGrid[j][i] < 6.0f) {
				mPlayer->setLast(2.0f+(mGrid[j][i]-5));
				mPlayer->setX(i);
				mPlayer->setY(j);
			}
		}
	}

	/*
	for (int j = 0; j < mHeight; j++){
		for (int i = 0; i < mWidth; i++){
			if (mGrid[j][i] == 1){
				mObjects.push_back(new Grass(i, j, (i * widthOnTile) + pushGrassX, (j * heightOnTile) + pushGrassY));

				mLongObjects.push_back(new Fence(i, j, (i * widthOnTile), (j * heightOnTile) + pushFenceY, 1));
			}
			if (mGrid[j][i] == 1.1f){
				mObjects.push_back(new Grass(i, j, (i * widthOnTile) + pushGrassX, (j * heightOnTile) + pushGrassY));

				mLongObjects.push_back(new Fence(i, j, (i * widthOnTile), (j * heightOnTile) + pushFenceY, 1));
			}
			if (mGrid[j][i] == 1.2f){
				mObjects.push_back(new Grass(i, j, (i * widthOnTile) + pushGrassX, (j * heightOnTile) + pushGrassY));

				mLongObjects.push_back(new Fence(i, j, (i * widthOnTile), (j * heightOnTile) + pushFenceY, 2));
			}
			if (mGrid[j][i] == 1.3f){
				mObjects.push_back(new Grass(i, j, (i * widthOnTile) + pushGrassX, (j * heightOnTile) + pushGrassY));

				mLongObjects.push_back(new Fence(i, j, (i * widthOnTile), (j * heightOnTile) + pushFenceY, 3));
			}
			if (mGrid[j][i] == 1.4f){
				mObjects.push_back(new Grass(i, j, (i * widthOnTile) + pushGrassX, (j * heightOnTile) + pushGrassY));

				mLongObjects.push_back(new Fence(i, j, (i * widthOnTile), (j * heightOnTile) + pushFenceY, 4));
			}
			if (mGrid[j][i] == 1.5f){
				mObjects.push_back(new Grass(i, j, (i * widthOnTile) + pushGrassX, (j * heightOnTile) + pushGrassY));

				mLongObjects.push_back(new Fence(i, j, (i * widthOnTile), (j * heightOnTile) + pushFenceY, 5));
			}
			if (mGrid[j][i] == 1.6f){
				mObjects.push_back(new Grass(i, j, (i * widthOnTile) + pushGrassX, (j * heightOnTile) + pushGrassY));

				mLongObjects.push_back(new Fence(i, j, (i * widthOnTile), (j * heightOnTile) + pushFenceY, 6));
			}
			if (mGrid[j][i] == 1.7f){
				mObjects.push_back(new Grass(i, j, (i * widthOnTile) + pushGrassX, (j * heightOnTile) + pushGrassY));

				mLongObjects.push_back(new Fence(i, j, (i * widthOnTile), (j * heightOnTile) + pushFenceY, 7));
			}
			if (mGrid[j][i] == 1.8f){
				mObjects.push_back(new Grass(i, j, (i * widthOnTile) + pushGrassX, (j * heightOnTile) + pushGrassY));

				mLongObjects.push_back(new Fence(i, j, (i * widthOnTile), (j * heightOnTile) + pushFenceY, 8));
			}
			if (mGrid[j][i] == 1.9f){
				mObjects.push_back(new Grass(i, j, (i * widthOnTile) + pushGrassX, (j * heightOnTile) + pushGrassY));
				mLongObjects.push_back(new Fence(i, j, (i * widthOnTile), (j * heightOnTile) + pushFenceY, 9));
			}
			if (mGrid[j][i] == 2){
				totalAmountOfGrass++;
				mObjects.push_back(new Grass(i, j, (i * widthOnTile) + pushGrassX, (j * heightOnTile) + pushGrassY));
			}
			if (mGrid[j][i] == 3){
				mObjects.push_back(new Stone(i, j, (i * widthOnTile), (j * heightOnTile)));
			}
			if (mGrid[j][i] == 4){
				mObjects.push_back(new Grass(i, j, (i * widthOnTile) + pushGrassX, (j * heightOnTile) + pushGrassY));
				mLongObjects.push_back(new Tree(i, j, (i * widthOnTile) - 31, (j * heightOnTile) - 200));
			}
			if (mGrid[j][i] == 5){
				mObjects.push_back(new Grass(i, j, (i * widthOnTile) + pushGrassX, (j * heightOnTile) + pushGrassY));
				mPlayer = new Player(i, j, new LawnMower(), new HedgeCutter(2, 1), (i * widthOnTile), (j * heightOnTile));
			}
			if (mGrid[j][i] == 6){
				totalAmountOfGrass++;
				mObjects.push_back(new Grass(i, j, (i * widthOnTile) + pushGrassX, (j * heightOnTile) + pushGrassY));
				mNpcs.push_back(new CharRand(i, j, (i * widthOnTile), (j * heightOnTile), 1, true));
			}	
			if (mGrid[j][i] == 7){
				totalAmountOfGrass++;
				mObjects.push_back(new Grass(i, j, (i * widthOnTile) + pushGrassX, (j * heightOnTile) + pushGrassY));
				mNpcs.push_back(new CharPatrol(i, j, (i * widthOnTile), (j * heightOnTile), patrolPath));
			}
			if (mGrid[j][i] == 9){
				totalAmountOfHedges++;
				mObjects.push_back(new Grass(i, j, (i * widthOnTile) + pushGrassX, (j * heightOnTile) + pushGrassY));
				mLongObjects.push_back(new Hedge(i, j, (i * widthOnTile), (j * heightOnTile)));
			}
		}
	}*/
}

void Map1::render(sf::RenderWindow &window, sf::Vector2i &mouse) {
	mState = 1;
	float scaleX = (float)window.getSize().x / 1920;
	float scaleY = (float)window.getSize().y / 1080;
	//float scaleX = 0.1f;
	//float scaleY = 0.1f;
	sf::Vector2i mousepos;
	mousepos.x = mouse.x;
	mousepos.y = mouse.y;

	if (mTurnCount == 50) {
		for (int j = 0; j < mHeight; j++) {
			for (int i = 0; i < mWidth; i++) {
				if (mGrid[j][i] == 2.0f) {
					mGrid[j][i] = 2.1f;
				}else
				if (mGrid[j][i] == 9.0f) {
					mGrid[j][i] = 9.1f;
				}else
				if (mGrid[j][i] == 2.2f) {
					mGrid[j][i] = 2.3f;
				}else
				if (mGrid[j][i] == 3.0f) {
					mGrid[j][i] = 3.1f;
				}else
				if (mGrid[j][i] == 4.0f) {
					mGrid[j][i] = 4.1f;
				}
			}
		}
	}

	mObjects[0]->getSprite()->setScale(sf::Vector2f(scaleX, scaleY));
	mObjects[1]->getSprite()->setScale(sf::Vector2f(scaleX, scaleY));
	mObjects[2]->getSprite()->setScale(sf::Vector2f(scaleX, scaleY));
	mObjects[3]->getSprite()->setScale(sf::Vector2f(scaleX, scaleY));
	mObjects[4]->getSprite()->setScale(sf::Vector2f(scaleX, scaleY));
	mObjects[5]->getSprite()->setScale(sf::Vector2f(scaleX, scaleY));

	mLongObjects[0]->getSprite()->setScale(sf::Vector2f(scaleX, scaleY));
	mLongObjects[1]->getSprite()->setScale(sf::Vector2f(scaleX, scaleY));
	mLongObjects[2]->getSprite()->setScale(sf::Vector2f(scaleX, scaleY));
	mLongObjects[3]->getSprite()->setScale(sf::Vector2f(scaleX, scaleY));
	mLongObjects[4]->getSprite()->setScale(sf::Vector2f(scaleX, scaleY));
	mLongObjects[5]->getSprite()->setScale(sf::Vector2f(scaleX, scaleY));
	mLongObjects[6]->getSprite()->setScale(sf::Vector2f(scaleX, scaleY));
	mLongObjects[7]->getSprite()->setScale(sf::Vector2f(scaleX, scaleY));
	mLongObjects[8]->getSprite()->setScale(sf::Vector2f(scaleX, scaleY));
	mLongObjects[9]->getSprite()->setScale(sf::Vector2f(scaleX, scaleY));
	mLongObjects[10]->getSprite()->setScale(sf::Vector2f(scaleX, scaleY));
	mLongObjects[11]->getSprite()->setScale(sf::Vector2f(scaleX, scaleY));
	mLongObjects[12]->getSprite()->setScale(sf::Vector2f(scaleX, scaleY));

	

	if (mRects[0]->contains(sf::Vector2i(mouse.x, mouse.y))){ // temp l�sning f�r ingame meny
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick){
			mClick = false;
			mState = 2;
			//sound.playSound(10.3f);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && mClick){
		mClick = false;
		mState = 2;
		//sound.playSound(10.3f);
	}
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mClick) {
		mClick = true;
	}

	for (int j = 0; j < mHeight; j++) {
		for (int i = 0; i < mWidth; i++) {
			/*if (mGrid[j][i] == 0.1f) {
				mObjects[0]->getSprite()->setPosition(( + pushMapXi * widthOnTile) + pushGrassX, (j * heightOnTile) + pushGrassY); //S�tter positionen enligt grid
				window.draw(mObjects[0]->getDrawSprite());
			}*/
			if (mGrid[j][i] == 1.1f) {
				mObjects[0]->getSprite()->setPosition((pushMapX + i * widthOnTile) + pushGrassX, pushMapY + (j * heightOnTile) + pushGrassY); //S�tter positionen enligt grid
				window.draw(mObjects[0]->getDrawSprite());
			}
			else if (mGrid[j][i] == 1.2f) {
				mObjects[0]->getSprite()->setPosition((pushMapX + i * widthOnTile) + pushGrassX, pushMapY + (j * heightOnTile) + pushGrassY); //S�tter positionen enligt grid
				window.draw(mObjects[0]->getDrawSprite());
			}
			else if (mGrid[j][i] == 1.3f) {
				mObjects[0]->getSprite()->setPosition((pushMapX + i * widthOnTile) + pushGrassX, pushMapY + (j * heightOnTile) + pushGrassY); //S�tter positionen enligt grid
				window.draw(mObjects[0]->getDrawSprite());
			}
			else if (mGrid[j][i] == 1.4f) {
				mObjects[0]->getSprite()->setPosition((pushMapX + i * widthOnTile) + pushGrassX, pushMapY + (j * heightOnTile) + pushGrassY); //S�tter positionen enligt grid
				window.draw(mObjects[0]->getDrawSprite());
			}
			else if (mGrid[j][i] == 1.5f) {
				mObjects[0]->getSprite()->setPosition((pushMapX + i * widthOnTile) + pushGrassX, pushMapY + (j * heightOnTile) + pushGrassY); //S�tter positionen enligt grid
				window.draw(mObjects[0]->getDrawSprite());
			}
			else if (mGrid[j][i] == 1.6f) {
				mObjects[0]->getSprite()->setPosition((pushMapX + i * widthOnTile) + pushGrassX, pushMapY + (j * heightOnTile) + pushGrassY); //S�tter positionen enligt grid
				window.draw(mObjects[0]->getDrawSprite());
			}
			else if (mGrid[j][i] == 1.7f) {
				mObjects[0]->getSprite()->setPosition((pushMapX + i * widthOnTile) + pushGrassX, pushMapY + (j * heightOnTile) + pushGrassY); //S�tter positionen enligt grid
				window.draw(mObjects[0]->getDrawSprite());
			}
			else if (mGrid[j][i] == 1.8f) {
				mObjects[0]->getSprite()->setPosition((pushMapX + i * widthOnTile) + pushGrassX, pushMapY + (j * heightOnTile) + pushGrassY); //S�tter positionen enligt grid
				window.draw(mObjects[0]->getDrawSprite());
			}
			else if (mGrid[j][i] == 1.9f) {
				mObjects[0]->getSprite()->setPosition((pushMapX + i * widthOnTile) + pushGrassX, pushMapY + (j * heightOnTile) + pushGrassY); //S�tter positionen enligt grid
				window.draw(mObjects[0]->getDrawSprite());
			}
			else if (mGrid[j][i] == 2.0f) { //Gr�s
				mObjects[0]->getSprite()->setPosition(((pushMapX + i * widthOnTile) + pushGrassX) * scaleX, (pushMapY + (j * heightOnTile) + pushGrassY) * scaleY); //S�tter positionen enligt grid
				window.draw(mObjects[0]->getDrawSprite());
			}
			else if (mGrid[j][i] == 2.1f) { //Klippt gr�s
				mObjects[1]->getSprite()->setPosition(((pushMapX + i * widthOnTile) + pushGrassX) * scaleX, (pushMapY + (j * heightOnTile) + pushGrassY) * scaleY); //S�tter positionen enligt grid
				window.draw(mObjects[1]->getDrawSprite());
			}
			else if (mGrid[j][i] == 2.2f) { //Maskros
				mObjects[3]->getSprite()->setPosition(((pushMapX + i * widthOnTile) + pushGrassX) * scaleX, (pushMapY + (j * heightOnTile) + pushGrassY) * scaleY); //S�tter positionen enligt grid
				window.draw(mObjects[3]->getDrawSprite());
			}
			else if (mGrid[j][i] == 2.3f) { //Klippt Maskros
				mObjects[4]->getSprite()->setPosition(((pushMapX + i * widthOnTile) + pushGrassX) * scaleX, (pushMapY + (j * heightOnTile) + pushGrassY) * scaleY); //S�tter positionen enligt grid
				window.draw(mObjects[4]->getDrawSprite());
			}
			else if (mGrid[j][i] == 2.4f) { //Grusv�g
				mObjects[5]->getSprite()->setPosition(((pushMapX + i * widthOnTile)) * scaleX, (pushMapY + (j * heightOnTile)) * scaleY); //S�tter positionen enligt grid
				window.draw(mObjects[5]->getDrawSprite());
			}
			else if (mGrid[j][i] == 3.0f) { //Sten
				mObjects[0]->getSprite()->setPosition(((pushMapX + i * widthOnTile) + pushGrassX) * scaleX, (pushMapY + (j * heightOnTile) + pushGrassY) * scaleY); //S�tter positionen enligt grid
				window.draw(mObjects[0]->getDrawSprite());
				mObjects[2]->getSprite()->setPosition(((pushMapX + i * widthOnTile)) * scaleX, (pushMapY + (j * heightOnTile) - 15) * scaleY); //S�tter positionen enligt grid
				window.draw(mObjects[2]->getDrawSprite());
			}
			else if (mGrid[j][i] == 3.1f) { //Sten
				mObjects[1]->getSprite()->setPosition(((pushMapX + i * widthOnTile) + pushGrassX) * scaleX, (pushMapY + (j * heightOnTile) + pushGrassY) * scaleY); //S�tter positionen enligt grid
				window.draw(mObjects[1]->getDrawSprite());
				mObjects[2]->getSprite()->setPosition(((pushMapX + i * widthOnTile)) * scaleX, (pushMapY + (j * heightOnTile) - 15) * scaleY); //S�tter positionen enligt grid
				window.draw(mObjects[2]->getDrawSprite());
			}
			else if (mGrid[j][i] == 4.0f) { //Tr�d
				mObjects[0]->getSprite()->setPosition(((pushMapX + i * widthOnTile) + pushGrassX) * scaleX, (pushMapY + (j * heightOnTile) + pushGrassY) * scaleY); //S�tter positionen enligt grid
				window.draw(mObjects[0]->getDrawSprite());
			}
			else if (mGrid[j][i] == 4.1f) { //Tr�d
				mObjects[1]->getSprite()->setPosition(((pushMapX + i * widthOnTile) + pushGrassX) * scaleX, (pushMapY + (j * heightOnTile) + pushGrassY) * scaleY); //S�tter positionen enligt grid
				window.draw(mObjects[1]->getDrawSprite());
			}
			else if (mGrid[j][i] == 5.0f) { //Spelare Gr�s, temp innan animation
				mObjects[0]->getSprite()->setPosition(((pushMapX + i * widthOnTile) + pushGrassX) * scaleX, (pushMapY + (j * heightOnTile) + pushGrassY) * scaleY); //S�tter positionen enligt grid
				window.draw(mObjects[0]->getDrawSprite());
			}
			else if (mGrid[j][i] == 5.1f) { //Spelare klippt Gr�s, temp innan animation
				mObjects[1]->getSprite()->setPosition(((pushMapX + i * widthOnTile) + pushGrassX) * scaleX, (pushMapY + (j * heightOnTile) + pushGrassY) * scaleY); //S�tter positionen enligt grid
				window.draw(mObjects[1]->getDrawSprite());
			}
			else if (mGrid[j][i] == 5.2f) { //Spelare maskros, temp innan animation
				mObjects[3]->getSprite()->setPosition(((pushMapX + i * widthOnTile) + pushGrassX) * scaleX, (pushMapY + (j * heightOnTile) + pushGrassY) * scaleY); //S�tter positionen enligt grid
				window.draw(mObjects[3]->getDrawSprite());
			}
			else if (mGrid[j][i] == 5.3f) { //Spelare klippt maskros, temp innan animation
				mObjects[4]->getSprite()->setPosition(((pushMapX + i * widthOnTile) + pushGrassX) * scaleX, (pushMapY + (j * heightOnTile) + pushGrassY) * scaleY); //S�tter positionen enligt grid
				window.draw(mObjects[4]->getDrawSprite());
			}
			else if (mGrid[j][i] == 5.4f) { //Spelare grusv�g, temp innan animation
				mObjects[5]->getSprite()->setPosition((pushMapX + i * widthOnTile) * scaleX, (pushMapY + (j * heightOnTile)) * scaleY); //S�tter positionen enligt grid
				window.draw(mObjects[5]->getDrawSprite());
			}
			else if (mGrid[j][i] == 6.0f) { //Rand Npc p� Gr�s, temp innan animation
				mObjects[0]->getSprite()->setPosition(((pushMapX + i * widthOnTile) + pushGrassX) * scaleX, (pushMapY + (j * heightOnTile) + pushGrassY) * scaleY); //S�tter positionen enligt grid
				window.draw(mObjects[0]->getDrawSprite());
			}
			else if (mGrid[j][i] == 6.1f) { //Rand Npc p� Klippt Gr�s, temp innan animation
				mObjects[1]->getSprite()->setPosition(((pushMapX + i * widthOnTile) + pushGrassX) * scaleX, (pushMapY + (j * heightOnTile) + pushGrassY) * scaleY); //S�tter positionen enligt grid
				window.draw(mObjects[1]->getDrawSprite());
			}
			else if (mGrid[j][i] == 6.2f) { //Rand Npc p� maskros, temp innan animation
				mObjects[3]->getSprite()->setPosition(((pushMapX + i * widthOnTile) + pushGrassX) * scaleX, (pushMapY + (j * heightOnTile) + pushGrassY) * scaleY); //S�tter positionen enligt grid
				window.draw(mObjects[3]->getDrawSprite());
			}
			else if (mGrid[j][i] == 6.3f) { //Rand Npc p� Klippt maskros, temp innan animation
				mObjects[4]->getSprite()->setPosition(((pushMapX + i * widthOnTile) + pushGrassX) * scaleX, (pushMapY + (j * heightOnTile) + pushGrassY) * scaleY); //S�tter positionen enligt grid
				window.draw(mObjects[4]->getDrawSprite());
			}
			else if (mGrid[j][i] == 6.4f) { //Rand Npc p� grusv�g, temp innan animation
				mObjects[5]->getSprite()->setPosition((pushMapX + i * widthOnTile) * scaleX, (pushMapY + (j * heightOnTile)) * scaleY); //S�tter positionen enligt grid
				window.draw(mObjects[5]->getDrawSprite());
			}
			else if (mGrid[j][i] == 7.0f) { //Patrull Npc p� Gr�s, temp innan animation
				mObjects[0]->getSprite()->setPosition(((pushMapX + i * widthOnTile) + pushGrassX) * scaleX, (pushMapY + (j * heightOnTile) + pushGrassY) * scaleY); //S�tter positionen enligt grid
				window.draw(mObjects[0]->getDrawSprite());
			}
			else if (mGrid[j][i] == 7.1f) { //Patrull Npc p� Klippt Gr�s, temp innan animation
				mObjects[1]->getSprite()->setPosition(((pushMapX + i * widthOnTile) + pushGrassX) * scaleX, (pushMapY + (j * heightOnTile) + pushGrassY) * scaleY); //S�tter positionen enligt grid
				window.draw(mObjects[1]->getDrawSprite());
			}
			else if (mGrid[j][i] == 7.2f) { //Patrull Npc p� maskros, temp innan animation
				mObjects[3]->getSprite()->setPosition(((pushMapX + i * widthOnTile) + pushGrassX) * scaleX, (pushMapY + (j * heightOnTile) + pushGrassY) * scaleY); //S�tter positionen enligt grid
				window.draw(mObjects[3]->getDrawSprite());
			}
			else if (mGrid[j][i] == 7.3f) { //Patrull Npc p� Klippt maskros, temp innan animation
				mObjects[4]->getSprite()->setPosition(((pushMapX + i * widthOnTile) + pushGrassX) * scaleX, (pushMapY + (j * heightOnTile) + pushGrassY) * scaleY); //S�tter positionen enligt grid
				window.draw(mObjects[4]->getDrawSprite());
			}
			else if (mGrid[j][i] == 7.4f) { //Patrull Npc p� grusv�g, temp innan animation
				mObjects[5]->getSprite()->setPosition((pushMapX + i * widthOnTile) * scaleX, (pushMapY + (j * heightOnTile)) * scaleY); //S�tter positionen enligt grid
				window.draw(mObjects[5]->getDrawSprite());
			}
			else if (mGrid[j][i] == 9.0f) { //H�ck
				mObjects[0]->getSprite()->setPosition((pushMapX + i * widthOnTile + pushGrassX) * scaleX, (pushMapY + (j * heightOnTile) + pushGrassY) * scaleY); //S�tter positionen enligt grid
				window.draw(mObjects[0]->getDrawSprite());
			}
			else if (mGrid[j][i] == 9.1f) { //Klippt H�ck
				mObjects[1]->getSprite()->setPosition(((pushMapX + i * widthOnTile) + pushGrassX) * scaleX, (pushMapY + (j * heightOnTile) + pushGrassY) * scaleY); //S�tter positionen enligt grid
				window.draw(mObjects[1]->getDrawSprite());
			}
			else if (mGrid[j][i] == 10.0f) { //Font�n
				for (int k = 0; k < 3; k++) {
					for (int l = 0; l < 3; l++) {
						mObjects[5]->getSprite()->setPosition(((pushMapX + i * widthOnTile) + l * widthOnTile) * scaleX, (pushMapY + (j * heightOnTile) + k * heightOnTile) * scaleY); //S�tter positionen enligt grid
						window.draw(mObjects[5]->getDrawSprite());
					}
				}
			}
		}
	}

	for (int j = 0; j < mHeight; j++) {
		for (int i = 0; i < mWidth; i++) {
			if (mGrid[j][i] == 1.1f) {
				mLongObjects[1]->getSprite()->setPosition((pushMapX + i * widthOnTile) * scaleX, (pushMapY + (j * heightOnTile) + pushFenceY) * scaleY); //S�tter positionen enligt grid
				window.draw(mLongObjects[1]->getDrawSprite());
			}
			else if (mGrid[j][i] == 1.3f) {
				mLongObjects[3]->getSprite()->setPosition((pushMapX + i * widthOnTile) * scaleX, (pushMapY + (j * heightOnTile) + pushFenceY) * scaleY); //S�tter positionen enligt grid
				window.draw(mLongObjects[3]->getDrawSprite());
			}
			else if (mGrid[j][i] == 1.4f) {
				mLongObjects[4]->getSprite()->setPosition((pushMapX + i * widthOnTile) * scaleX, (pushMapY + (j * heightOnTile) + pushFenceY) * scaleY); //S�tter positionen enligt grid
				window.draw(mLongObjects[4]->getDrawSprite());
			}
			else if (mGrid[j][i] == 1.5f) {
				mLongObjects[5]->getSprite()->setPosition((pushMapX + i * widthOnTile) * scaleX, (pushMapY + (j * heightOnTile) + pushFenceY) * scaleY); //S�tter positionen enligt grid
				window.draw(mLongObjects[5]->getDrawSprite());
			}
			else if (mGrid[j][i] == 1.6f) {
				mLongObjects[6]->getSprite()->setPosition((pushMapX + i * widthOnTile) * scaleX, (pushMapY + (j * heightOnTile) + pushFenceY) * scaleY); //S�tter positionen enligt grid
				window.draw(mLongObjects[6]->getDrawSprite());
			}
			else if (mGrid[j][i] == 1.7f) {
				mLongObjects[7]->getSprite()->setPosition((pushMapX + i * widthOnTile) * scaleX, (pushMapY + (j * heightOnTile) + pushFenceY) * scaleY); //S�tter positionen enligt grid
				window.draw(mLongObjects[7]->getDrawSprite());
			}
			else if (mGrid[j][i] == 1.8f) {
				mLongObjects[8]->getSprite()->setPosition((pushMapX + i * widthOnTile) * scaleX, (pushMapY + (j * heightOnTile) + pushFenceY) * scaleY); //S�tter positionen enligt grid
				window.draw(mLongObjects[8]->getDrawSprite());
			}
			else if (mGrid[j][i] == 1.9f) {
				mLongObjects[9]->getSprite()->setPosition((pushMapX + i * widthOnTile) * scaleX, (pushMapY + (j * heightOnTile) + pushFenceY) * scaleY); //S�tter positionen enligt grid
				window.draw(mLongObjects[9]->getDrawSprite());
			}
			else if (mGrid[j][i] == 9.0f) { //H�ck
				mLongObjects[10]->getSprite()->setPosition(((pushMapX + i * widthOnTile) + pushGrassX)  * scaleX, (pushMapY + (j * heightOnTile) + pushGrassY - 12) * scaleY); //S�tter positionen enligt grid
				window.draw(mLongObjects[10]->getDrawSprite());
			}
			else if (mGrid[j][i] == 9.1f) { //Klippt H�ck
				mLongObjects[11]->getSprite()->setPosition(((pushMapX + i * widthOnTile) + pushGrassX)  * scaleX, (pushMapY + (j * heightOnTile) + pushGrassY - 22) * scaleY); //S�tter positionen enligt grid
				window.draw(mLongObjects[11]->getDrawSprite());
			}
		}
	}
	for (int j = 0; j < mHeight; j++) {
		for (int i = 0; i < mWidth; i++) {
			if (mGrid[j][i] == 4.0f) { //Tr�d
				mLongObjects[0]->getSprite()->setPosition(((pushMapX + i * widthOnTile) - 31) * scaleX, pushMapY + ((j * heightOnTile) - 148) * scaleY); //S�tter positionen enligt grid
				window.draw(mLongObjects[0]->getDrawSprite());
			}
			else
			if (mGrid[j][i] == 4.1f) { //Tr�d
				mLongObjects[0]->getSprite()->setPosition(((pushMapX + i * widthOnTile) - 31) * scaleX, pushMapY + ((j * heightOnTile) - 148) * scaleY); //S�tter positionen enligt grid
				window.draw(mLongObjects[0]->getDrawSprite());
			}
			else if (mGrid[j][i] == 10.0f) { //Font�n
				mLongObjects[12]->playAnimation();
				mLongObjects[12]->getSprite()->setPosition((pushMapX + 3 + i * widthOnTile) * scaleX, (pushMapY - 45 + (j * heightOnTile) + pushGrassY / 2) * scaleY); //S�tter positionen enligt grid
				window.draw(*mLongObjects[12]->getSprite());
			}
			else if (mGrid[j][i] == 1.2f) {
				mLongObjects[2]->getSprite()->setPosition((pushMapX + i * widthOnTile) * scaleX, (pushMapY + (j * heightOnTile) + pushFenceY) * scaleY); //S�tter positionen enligt grid
				window.draw(mLongObjects[2]->getDrawSprite());
			}
			else if (mGrid[j][i] == 5.0f) { //Spelare Gr�s, temp innan animation
				mPlayer->playPlayer();
				if (!mMeepMoving) {
					mPlayer->getSpriteSheet()->setPosition(((pushMapX + i * widthOnTile) + pushMeepX) * scaleX, (pushMapY + (j * heightOnTile) + pushMeepY) * scaleY);
				}
				mPlayer->scale(window);
				window.draw(*mPlayer->getSpriteSheet());

				//anime.playTest();
				//anime.getSpriteSheet()->setPosition((pushMapX + i * widthOnTile) + pushMeepX, pushMapY + (j * heightOnTile) + pushMeepY);
				//window.draw(*anime.getSpriteSheet());
				//mPlayer->getSprite()->setPosition((pushMapX + i * widthOnTile), pushMapY + (j * heightOnTile) - 75);
					//window.draw(mPlayer->getDrawSprite());
					//mPlayer->setX(i);
					//mPlayer->setY(j);
			}
			else if (mGrid[j][i] == 5.1f) { //Spelare Klippt Gr�s, temp innan animation
				mPlayer->playPlayer();
				if (!mMeepMoving) {
					mPlayer->getSpriteSheet()->setPosition(((pushMapX + i * widthOnTile) + pushMeepX) * scaleX, (pushMapY + (j * heightOnTile) + pushMeepY) * scaleY);
				}
				mPlayer->scale(window);
				window.draw(*mPlayer->getSpriteSheet());
				/*anime.playTest();
				anime.getSpriteSheet()->setPosition((pushMapX + i * widthOnTile) + pushMeepX, pushMapY + (j * heightOnTile) + pushMeepY);
				window.draw(*anime.getSpriteSheet());*/
					/*mPlayer->getSprite()->setPosition((pushMapX + i * widthOnTile), pushMapY + (j * heightOnTile) - 75);
					window.draw(mPlayer->getDrawSprite());*/
				//mPlayer->setLast(2.1f);
				//mPlayer->setX(i);
				//mPlayer->setY(j);

			}
			else if (mGrid[j][i] == 5.2f) { //Spelare maskros, temp innan animation
				mPlayer->playPlayer();
				if (!mMeepMoving) {
					mPlayer->getSpriteSheet()->setPosition(((pushMapX + i * widthOnTile) + pushMeepX) * scaleX, (pushMapY + (j * heightOnTile) + pushMeepY) * scaleY);
				}
				mPlayer->scale(window);
				window.draw(*mPlayer->getSpriteSheet());
				/*anime.playTest();
				anime.getSpriteSheet()->setPosition((pushMapX + i * widthOnTile) + pushMeepX, pushMapY + (j * heightOnTile) + pushMeepY);
				window.draw(*anime.getSpriteSheet());*/
				/*mPlayer->getSprite()->setPosition((pushMapX + i * widthOnTile), pushMapY + (j * heightOnTile) - 75);
					window.draw(mPlayer->getDrawSprite());*/
				//mPlayer->setLast(2.2f);
				//mPlayer->setX(i);
				//mPlayer->setY(j);
			}
			else if (mGrid[j][i] == 5.3f) { //Spelare klippt maskros, temp innan animation
				mPlayer->playPlayer();
				if (!mMeepMoving) {
					mPlayer->getSpriteSheet()->setPosition(((pushMapX + i * widthOnTile) + pushMeepX) * scaleX, (pushMapY + (j * heightOnTile) + pushMeepY) * scaleY);
				}
				mPlayer->scale(window);
				window.draw(*mPlayer->getSpriteSheet());
				/*anime.playTest();
				anime.getSpriteSheet()->setPosition((pushMapX + i * widthOnTile) + pushMeepX, pushMapY + (j * heightOnTile) + pushMeepY);
				window.draw(*anime.getSpriteSheet());*/
				/*mPlayer->getSprite()->setPosition((pushMapX + i * widthOnTile), pushMapY + (j * heightOnTile) - 75);
					window.draw(mPlayer->getDrawSprite());*/
				//mPlayer->setLast(2.3f);
				//mPlayer->setX(i);
				//mPlayer->setY(j);
			}
			else if (mGrid[j][i] == 5.4f) { //Spelare grusv�g, temp innan animation
				mPlayer->playPlayer();
				if (!mMeepMoving) {
					mPlayer->getSpriteSheet()->setPosition(((pushMapX + i * widthOnTile) + pushMeepX) * scaleX, (pushMapY + (j * heightOnTile) + pushMeepY) * scaleY);
				}
				mPlayer->scale(window);
				window.draw(*mPlayer->getSpriteSheet());
				/*anime.playTest();
				anime.getSpriteSheet()->setPosition((pushMapX + i * widthOnTile) + pushMeepX, pushMapY + (j * heightOnTile) + pushMeepY);
				window.draw(*anime.getSpriteSheet());*/
				//mPlayer->setLast(2.4f);
				//mPlayer->setX(i);
				//mPlayer->setY(j);
				/*mPlayer->getSprite()->setPosition((pushMapX + i * widthOnTile), pushMapY + (j * heightOnTile) - 75);
					window.draw(mPlayer->getDrawSprite());*/
			}
			else if (mGrid[j][i] == 6.0f) { //Rand Npc Gr�s, temp innan animation
				coords c = { i, j };
				if (mNpcs[c] != 0) {
					mNpcs[c]->scale(window);
					mNpcs[c]->playAnimation();
					if (!mNpcsMoving) {
						mNpcs[c]->getSpriteSheet()->setPosition(((pushMapX + i * widthOnTile) + pushNpcX) * scaleX, (pushMapY + (j * heightOnTile) + pushNpcY) * scaleY); //S�tter positionen enligt grid
					}
					window.draw(*mNpcs[c]->getSpriteSheet());
				}
			}
			else if (mGrid[j][i] == 6.1f) { //Rand Npc Klippt Gr�s, temp innan animation
				coords c = { i, j };
				if (mNpcs[c] != 0) {
					mNpcs[c]->scale(window);
					mNpcs[c]->playAnimation();
					if (!mNpcsMoving) {
						mNpcs[c]->getSpriteSheet()->setPosition(((pushMapX + i * widthOnTile) + pushNpcX) * scaleX, (pushMapY + (j * heightOnTile) + pushNpcY) * scaleY); //S�tter positionen enligt grid
					}
					window.draw(*mNpcs[c]->getSpriteSheet());
				}
			}
			else if (mGrid[j][i] == 6.2f) { //Rand Npc maskros, temp innan animation
				coords c = { i, j };
				if (mNpcs[c] != 0) {
					mNpcs[c]->scale(window);
					mNpcs[c]->playAnimation();
					if (!mNpcsMoving) {
						mNpcs[c]->getSpriteSheet()->setPosition(((pushMapX + i * widthOnTile) + pushNpcX) * scaleX, (pushMapY + (j * heightOnTile) + pushNpcY) * scaleY); //S�tter positionen enligt grid
					}
					window.draw(*mNpcs[c]->getSpriteSheet());
				}
				mNpcs[c]->setLast(2.2f);
			}
			else if (mGrid[j][i] == 6.3f) { //Rand Npc Klippt maskros, temp innan animation
				coords c = { i, j };
				if (mNpcs[c] != 0) {
					mNpcs[c]->scale(window);
					mNpcs[c]->playAnimation();
					if (!mNpcsMoving) {
						mNpcs[c]->getSpriteSheet()->setPosition(((pushMapX + i * widthOnTile) + pushNpcX) * scaleX, (pushMapY + (j * heightOnTile) + pushNpcY) * scaleY); //S�tter positionen enligt grid
					}
					window.draw(*mNpcs[c]->getSpriteSheet());
				}
			}
			else if (mGrid[j][i] == 6.4f) { //Rand Npc grusv�g, temp innan animation
				coords c = { i, j };
				if (mNpcs[c] != 0) {
					mNpcs[c]->scale(window);
					mNpcs[c]->playAnimation();
					if (!mNpcsMoving) {
						mNpcs[c]->getSpriteSheet()->setPosition(((pushMapX + i * widthOnTile) + pushNpcX) * scaleX, (pushMapY + (j * heightOnTile) + pushNpcY) * scaleY); //S�tter positionen enligt grid
					}
					window.draw(*mNpcs[c]->getSpriteSheet());
				}
				mNpcs[c]->setLast(2.4f);
			}
			else if (mGrid[j][i] == 7.0f) { //Patrull Npc Gr�s, temp innan animation
				coords c = { i, j };
				if (mNpcs[c] != 0) {
					mNpcs[c]->scale(window);
					mNpcs[c]->playAnimation();
					if (!mNpcsMoving) {
						mNpcs[c]->getSpriteSheet()->setPosition(((pushMapX + i * widthOnTile) + pushNpcX) * scaleX, (pushMapY + (j * heightOnTile) + pushNpcY) * scaleY); //S�tter positionen enligt grid
					}
					window.draw(*mNpcs[c]->getSpriteSheet());
				}
			}
			else if (mGrid[j][i] == 7.1f) { //Patrull Npc Klippt Gr�s, temp innan animation
				coords c = { i, j };
				if (mNpcs[c] != 0) {
					mNpcs[c]->scale(window);
					mNpcs[c]->playAnimation();
					if (!mNpcsMoving) {
						mNpcs[c]->getSpriteSheet()->setPosition(((pushMapX + i * widthOnTile) + pushNpcX) * scaleX, (pushMapY + (j * heightOnTile) + pushNpcY) * scaleY); //S�tter positionen enligt grid
					}
					window.draw(*mNpcs[c]->getSpriteSheet());
				}
			}
			else if (mGrid[j][i] == 7.2f) { //Patrull Npc maskros, temp innan animation
				coords c = { i, j };
				if (mNpcs[c] != 0) {
					mNpcs[c]->scale(window);
					mNpcs[c]->playAnimation();
					if (!mNpcsMoving) {
						mNpcs[c]->getSpriteSheet()->setPosition(((pushMapX + i * widthOnTile) + pushNpcX) * scaleX, (pushMapY + (j * heightOnTile) + pushNpcY) * scaleY); //S�tter positionen enligt grid
					}
					window.draw(*mNpcs[c]->getSpriteSheet());
				}
				mNpcs[c]->setLast(2.2f);
			}
			else if (mGrid[j][i] == 7.3f) { //Patrull Npc Klippt maskros, temp innan animation
				coords c = { i, j };
				if (mNpcs[c] != 0) {
					mNpcs[c]->scale(window);
					mNpcs[c]->playAnimation();
					if (!mNpcsMoving) {
						mNpcs[c]->getSpriteSheet()->setPosition(((pushMapX + i * widthOnTile) + pushNpcX) * scaleX, (pushMapY + (j * heightOnTile) + pushNpcY) * scaleY); //S�tter positionen enligt grid
					}
					window.draw(*mNpcs[c]->getSpriteSheet());
				}
			}
			else if (mGrid[j][i] == 7.4f) { //Patrull Npc grusv�g, temp innan animation
				coords c = { i, j };
				if (mNpcs[c] != 0) {
					mNpcs[c]->scale(window);
					mNpcs[c]->playAnimation();
					if (!mNpcsMoving) {
						mNpcs[c]->getSpriteSheet()->setPosition(((pushMapX + i * widthOnTile) + pushNpcX) * scaleX, (pushMapY + (j * heightOnTile) + pushNpcY) * scaleY); //S�tter positionen enligt grid
					}
					window.draw(*mNpcs[c]->getSpriteSheet());
				}
				mNpcs[c]->setLast(2.4f);
			}
		}
	}
}

void Map1::beginTurn(int dir) {
	if (!mOngoingTurn)
	{
		mPlayer->changeAnimation(dir);
		mTurnClock.restart();
		mPlayerMoveTime.restart();
		mCurrentMove.clear();
		mCurrentMove = mPlayer->move(dir);
		mPlaceInMove = 0;
		mNpcNo = 0;
		mOngoingTurn = true;
		mPlayer->setWalking(true);
		mMeepMoving = true;
		mNpcsMoving = false;
		mNpcVector.clear();
		//Cleanup note: Not sure if mNpcCoords actually ever does anything or if it just sits there. 
		//I do recall needing it for testing at one point, not sure if it became obsolete.
		mNpcCoords.clear();
		for (int j = 0; j < mHeight; j++) {
			for (int i = 0; i < mWidth; i++) {
				if (mGrid[j][i] >= 6.0f && mGrid[j][i] < 8.0f) {
					coords at = { i, j };
					mNpcVector.push_back(mNpcs[at]);
				}
			}
		}
	}
}

void Map1::update(SoundManager &sound, sf::RenderWindow &window) {
	float scaleX = (float)window.getSize().x / 1920;
	float scaleY = (float)window.getSize().y / 1080;
	if (mPlaceInMove == mCurrentMove.size()) {
		if (mMeepMoving) {
			mPlayer->setWalking(false);
			mMeepMoving = false;
			mPlaceInMove = 0;
			mNpcsMoving = true;
			mCurrentMove.clear();
		}
		/*else if (mNpcsMoving) {
			if (mNpcNo < mNpcVector.size() - 1) {
				//mNpcVector[mNpcNo]->setWalking(false);
				mNpcNo++;
				mCurrentMove.clear();
				mPlaceInMove = 0;
			}
			else {
				mNpcsMoving = false;
			}
		}*/
	}

	if (mNpcVector.empty()) {
		mNpcsMoving = false;
	}

	/*if (mNpcsMoving) {
		float tempPosX = (pushMapX + (mNpcVector[mNpcNo]->getX() * widthOnTile) + pushNpcX) * scaleX;
		float tempPosY = (pushMapY + (mNpcVector[mNpcNo]->getY() * heightOnTile) + pushNpcY) * scaleY;
		if (mCurrentMove.size()>mPlaceInMove){
			switch (mCurrentMove[mPlaceInMove]) {
			case 8:
				mNpcVector[mNpcNo]->getSpriteSheet()->setPosition(tempPosX + 0,
					tempPosY - (mNpcMoveTimer.getElapsedTime().asSeconds() / mNpcMoveTime) * heightOnTile);
				break;
			case 9:
				mNpcVector[mNpcNo]->getSpriteSheet()->setPosition(tempPosX + (mNpcMoveTimer.getElapsedTime().asSeconds() / mNpcMoveTime * widthOnTile),
					tempPosY - (mNpcMoveTimer.getElapsedTime().asSeconds() / mNpcMoveTime) * heightOnTile);
				break;
			case 6:
				mNpcVector[mNpcNo]->getSpriteSheet()->setPosition(tempPosX + (mNpcMoveTimer.getElapsedTime().asSeconds() / mNpcMoveTime * widthOnTile),
					tempPosY + 0);
				break;
			case 3:
				mNpcVector[mNpcNo]->getSpriteSheet()->setPosition(tempPosX + (mNpcMoveTimer.getElapsedTime().asSeconds() / mNpcMoveTime * widthOnTile),
					tempPosY + (mNpcMoveTimer.getElapsedTime().asSeconds() / mNpcMoveTime) * heightOnTile);
				break;
			case 2:
				mNpcVector[mNpcNo]->getSpriteSheet()->setPosition(tempPosX + 0,
					tempPosY + (mNpcMoveTimer.getElapsedTime().asSeconds() / mNpcMoveTime) * heightOnTile);
				break;
			case 1:
				mNpcVector[mNpcNo]->getSpriteSheet()->setPosition(tempPosX - (mNpcMoveTimer.getElapsedTime().asSeconds() / mNpcMoveTime * widthOnTile),
					tempPosY + (mNpcMoveTimer.getElapsedTime().asSeconds() / mNpcMoveTime) * heightOnTile);
				break;
			case 4:
				mNpcVector[mNpcNo]->getSpriteSheet()->setPosition(tempPosX - (mNpcMoveTimer.getElapsedTime().asSeconds() / mNpcMoveTime * widthOnTile),
					tempPosY + 0);
				break;
			case 7:
				mNpcVector[mNpcNo]->getSpriteSheet()->setPosition(tempPosX - (mNpcMoveTimer.getElapsedTime().asSeconds() / mNpcMoveTime * widthOnTile),
					tempPosY - (mNpcMoveTimer.getElapsedTime().asSeconds() / mNpcMoveTime) * heightOnTile);
				break;
			}
		}
	}*/


	if (!mMeepMoving && mNpcsMoving) {
		/*if (mNpcNo < mNpcVector.size()) {
			mNpcVector[mNpcNo]->setWalking(true);

			if (mCurrentMove.empty()) {
				mCurrentMove = mNpcVector[mNpcNo]->move();
				mPlaceInMove = 0;
				mNpcMoveTime = 0.1f/mCurrentMove.size();
				mNpcMoveTimer.restart();
			}

			if (mPlaceInMove < mCurrentMove.size() && mNpcMoveTimer.getElapsedTime().asSeconds()>=mNpcMoveTime) {
				mNpcMoveTimer.restart();
				//0 means end of movement. Needed for patrols. 
				//Breakmove means that the entire movement for this character
				//is over for the turn
				if (mCurrentMove.at(mPlaceInMove) == 0) {
					mBreakMove = true;
					mNpcVector[mNpcNo]->setWalking(false);
					//mBreakMove = false;
					//break;
					//mNpcs[i]->swapDoneMoving();
				}

				//the movement functions returns a bool. True if they moved, 
				//false in case of collision

				if (!mBreakMove) {

					bool moved = moveNpc(mCurrentMove.at(mPlaceInMove), mNpcNo, sound);
					//if the NPC collided: do the following
					if (!moved) {

						//cout << "failed with move " << npcMove.at(j) << ", place " << j << endl;
						//get a new series of moves to attempt
						intVector tryMove;
						tryMove = mNpcVector[mNpcNo]->collide(mCurrentMove, mPlaceInMove);
						//try out the new list of steps
						for (intVector::size_type k = 0; k < tryMove.size(); k++) {
							//again, break if 0, breakMove is made true so that
							//the entire turn will end for the current character
							//if there is no movement after collision
							if (tryMove.at(k) == 0) {
								mBreakMove = true;
								mNpcVector[mNpcNo]->setWalking(false);
								break;
							}
							//check every move. If one of them works, return to standard
							//movement pattern
							bool retryMoved = moveNpc(tryMove.at(k), mNpcNo, sound);
							if (retryMoved) {
								mNpcVector[mNpcNo]->getSpriteSheet()->setPosition(((pushMapX + mNpcVector[mNpcNo]->getX() * widthOnTile) + pushNpcX) * scaleX, (pushMapY + (mNpcVector[mNpcNo]->getY() * heightOnTile) + pushNpcY) * scaleY);
								break;
							}
							else {
								mNpcVector[mNpcNo]->getSpriteSheet()->setPosition(((pushMapX + mNpcVector[mNpcNo]->getX() * widthOnTile) + pushNpcX) * scaleX, (pushMapY + (mNpcVector[mNpcNo]->getY() * heightOnTile) + pushNpcY) * scaleY);
							}
						}
					}
					else {
						mNpcVector[mNpcNo]->getSpriteSheet()->setPosition(((pushMapX + mNpcVector[mNpcNo]->getX() * widthOnTile) + pushNpcX) * scaleX, (pushMapY + (mNpcVector[mNpcNo]->getY() * heightOnTile) + pushNpcY) * scaleY);
					}
				}
				else {
					mCurrentMove.clear();
				}
				mPlaceInMove++;
			}
		}*/

		//Following code block is mostly copypasted from takeTurn
		for (NpcVector::size_type i = 0; i < mNpcVector.size(); i++) {
			//get their movement vector
			intVector npcMove = mNpcVector[i]->move();
			bool breakMove = false;
			//For every int in the vector, do the following
			for (intVector::size_type j = 0; j < npcMove.size(); j++) {
				//0 means end of movement. Needed for patrols. 
				//Breakmove means that the entire movement for this character
				//is over for the turn
				if (npcMove.at(j) == 0 || breakMove) {
					breakMove = false;
					//mNpcs[i]->swapDoneMoving();
					break;
				}
				//the movement functions returns a bool. True if they moved, 
				//false in case of collision
				bool moved = moveNpc(npcMove.at(j), i, sound);
				//if the NPC collided: do the following
				if (!moved) {

					//cout << "failed with move " << npcMove.at(j) << ", place " << j << endl;
					//get a new series of moves to attempt
					intVector tryMove;
					tryMove = mNpcVector[i]->collide(npcMove, j);
					//try out the new list of steps
					for (intVector::size_type k = 0; k < tryMove.size(); k++) {
						//again, break if 0, breakMove is made true so that
						//the entire turn will end for the current character
						//if there is no movement after collision
						if (tryMove.at(k) == 0) {
							breakMove = true;
							break;
						}
						//check every move. If one of them works, return to standard
						//movement pattern
						bool retryMoved = moveNpc(tryMove.at(k), i, sound);
						if (retryMoved) {
							break;
						}
					}

					break;
				}
				else {
					//cout << "Moved " << npcMove.at(j) << endl;
				}
			}
		}
	}

	mNpcsMoving = false;

	/*for (NpcVector::size_type i = 0; i < mNpcVector.size(); i++) {
		mNpcVector[i]->setWalking(false);
	}*/

	if (mMeepMoving) {
		//(mPlayerMoveTime.getElapsedTime().asSeconds()/mPlayer->getMoveTime())
		//mPlayer->getSpriteSheet()->move(((mPlayerMoveTime.getElapsedTime().asSeconds()/mPlayer->getMoveTime()) * widthOnTile), ((mPlayerMoveTime.getElapsedTime().asSeconds() / mPlayer->getMoveTime()) * heightOnTile));

		float tempPosX = (pushMapX + (mPlayer->getX() * widthOnTile) + pushMeepX) * scaleX;
		float tempPosY = (pushMapY + (mPlayer->getY() * heightOnTile) + pushMeepY) * scaleY;

		switch (mCurrentMove[mPlaceInMove]) {
		case 8:
			mPlayer->getSpriteSheet()->setPosition(tempPosX + 0*scaleX,
				tempPosY - (mPlayerMoveTime.getElapsedTime().asSeconds() / mPlayer->getMoveTime()) * heightOnTile*scaleY);

			//mPlayer->getSpriteSheet()->move(0,
			//	-((mPlayerMoveTime.getElapsedTime().asSeconds() / mPlayer->getMoveTime()) * heightOnTile));
			break;
		case 9:
			mPlayer->getSpriteSheet()->setPosition(tempPosX + (mPlayerMoveTime.getElapsedTime().asSeconds() / mPlayer->getMoveTime() * widthOnTile)*scaleX,
				tempPosY - (mPlayerMoveTime.getElapsedTime().asSeconds() / mPlayer->getMoveTime()) * heightOnTile*scaleY);

			//mPlayer->getSpriteSheet()->move(((mPlayerMoveTime.getElapsedTime().asSeconds()/mPlayer->getMoveTime()) * widthOnTile),
			//	-((mPlayerMoveTime.getElapsedTime().asSeconds() / mPlayer->getMoveTime()) * heightOnTile));
			break;
		case 6:
			mPlayer->getSpriteSheet()->setPosition(tempPosX + (mPlayerMoveTime.getElapsedTime().asSeconds() / mPlayer->getMoveTime() * widthOnTile)*scaleX,
				tempPosY + 0 * scaleY);

			//mPlayer->getSpriteSheet()->move(((mPlayerMoveTime.getElapsedTime().asSeconds() / mPlayer->getMoveTime()) * widthOnTile),
			//	0);	
			break;
		case 3:
			mPlayer->getSpriteSheet()->setPosition(tempPosX + (mPlayerMoveTime.getElapsedTime().asSeconds() / mPlayer->getMoveTime() * widthOnTile)*scaleX,
				tempPosY + (mPlayerMoveTime.getElapsedTime().asSeconds() / mPlayer->getMoveTime()) * heightOnTile*scaleY);

			//mPlayer->getSpriteSheet()->move(((mPlayerMoveTime.getElapsedTime().asSeconds() / mPlayer->getMoveTime()) * widthOnTile),
			//	((mPlayerMoveTime.getElapsedTime().asSeconds() / mPlayer->getMoveTime()) * heightOnTile));
			break;
		case 2:
			mPlayer->getSpriteSheet()->setPosition(tempPosX + 0 * scaleX,
				tempPosY + (mPlayerMoveTime.getElapsedTime().asSeconds() / mPlayer->getMoveTime()) * heightOnTile*scaleY);

			//mPlayer->getSpriteSheet()->move(0,
			//	((mPlayerMoveTime.getElapsedTime().asSeconds() / mPlayer->getMoveTime()) * heightOnTile));
			break;
		case 1:
			mPlayer->getSpriteSheet()->setPosition(tempPosX - (mPlayerMoveTime.getElapsedTime().asSeconds() / mPlayer->getMoveTime() * widthOnTile)*scaleX,
				tempPosY + (mPlayerMoveTime.getElapsedTime().asSeconds() / mPlayer->getMoveTime()) * heightOnTile*scaleY);

			//mPlayer->getSpriteSheet()->move(-((mPlayerMoveTime.getElapsedTime().asSeconds() / mPlayer->getMoveTime()) * widthOnTile),
			//	((mPlayerMoveTime.getElapsedTime().asSeconds() / mPlayer->getMoveTime()) * heightOnTile));
			break;
		case 4:
			mPlayer->getSpriteSheet()->setPosition(tempPosX - (mPlayerMoveTime.getElapsedTime().asSeconds() / mPlayer->getMoveTime() * widthOnTile)*scaleX,
				tempPosY + 0 * scaleY);

			//mPlayer->getSpriteSheet()->move(-((mPlayerMoveTime.getElapsedTime().asSeconds() / mPlayer->getMoveTime()) * widthOnTile),
			//	0 );
			break;
		case 7:
			mPlayer->getSpriteSheet()->setPosition(tempPosX - (mPlayerMoveTime.getElapsedTime().asSeconds() / mPlayer->getMoveTime() * widthOnTile)*scaleX,
				tempPosY - (mPlayerMoveTime.getElapsedTime().asSeconds() / mPlayer->getMoveTime()) * heightOnTile*scaleY);

			//mPlayer->getSpriteSheet()->move(-((mPlayerMoveTime.getElapsedTime().asSeconds() / mPlayer->getMoveTime()) * widthOnTile),
			//	-((mPlayerMoveTime.getElapsedTime().asSeconds() / mPlayer->getMoveTime()) * heightOnTile));
			break;
		}
		//Asd
	}

	if (mMeepMoving && mPlayerMoveTime.getElapsedTime().asSeconds() >= mPlayer->getMoveTime()) {
		mPlayerMoveTime.restart();
		bool moved = movePlayer(mCurrentMove.at(mPlaceInMove), sound, window);
		if (!moved) {
			mPlayer->collide(mCurrentMove, mPlaceInMove);
			mPlayer->getSpriteSheet()->setPosition(((pushMapX + mPlayer->getX() * widthOnTile) + pushMeepX) * scaleX, (pushMapY + (mPlayer->getY() * heightOnTile) + pushMeepY) * scaleY);
			mPlayer->setWalking(false);
			mMeepMoving = false;
			mCurrentMove.clear();
			mNpcsMoving = true;
		}
		else {
			mPlayer->getSpriteSheet()->setPosition(((pushMapX + mPlayer->getX() * widthOnTile) + pushMeepX) * scaleX, (pushMapY + (mPlayer->getY() * heightOnTile) + pushMeepY) * scaleY);
		}
		mPlaceInMove++;
	}

	if (!mMeepMoving && !mNpcsMoving && mOngoingTurn) {
		mTurnCount++;
		std::cout << "That was turn " << mTurnCount << "." << endl;
		if (mTurnCount >= 50) {
			std::cout << "GAME OVER" << endl;
		}
		std::cout << endl;
		mOngoingTurn = false;
	}

	if (mTurnClock.getElapsedTime().asSeconds() >= 20.0 && mOngoingTurn) {
		mTurnCount++;
		std::cout << "That was turn " << mTurnCount << "." << endl;
		if (mTurnCount >= 50) {
			std::cout << "GAME OVER" << endl;
		}
		std::cout << endl;
		mOngoingTurn = false;
	}

}

/*This code looks a ton better with helper functions movePlayer(int dir)
and moveNpc(int dir, int atPos) for each individual step.*/
void Map1::takeTurn(int dir, SoundManager &sound, sf::RenderWindow &window) {

	//sound.playSound(10.4f);
	/*get the intVector that lists all of the individual 1-tile moves*/
	intVector meepMove = mPlayer->move(dir);
	/*go through the vector and move 1 step int*/
	for (intVector::size_type i = 0; i < meepMove.size(); i++) {
		bool moved = movePlayer(meepMove.at(i), sound, window);
		if (!moved) {
			mPlayer->collide(meepMove, i);
			break;
		}
	}

	//Add all the npcs on the map to a vector for ease of looping
	mNpcVector.clear();
	mNpcCoords.clear();
	for (int j = 0; j < mHeight; j++) {
		for (int i = 0; i < mWidth; i++) {
			if (mGrid[j][i] >= 6.0f && mGrid[j][i] < 8.0f) {
				coords at = { i, j };
				mNpcVector.push_back(mNpcs[at]);
			}
		}
	}
	//cout << "Size of vector " << mNpcVector.size() << endl;
	/*Do this for every NPC in the vector*/
	for (NpcVector::size_type i = 0; i < mNpcVector.size(); i++) {
		//get their movement vector
		intVector npcMove = mNpcVector[i]->move();
		bool breakMove = false;
		//For every int in the vector, do the following
		for (intVector::size_type j = 0; j < npcMove.size(); j++) {
			//0 means end of movement. Needed for patrols. 
			//Breakmove means that the entire movement for this character
			//is over for the turn
			if (npcMove.at(j) == 0 || breakMove) {
				breakMove = false;
				//mNpcs[i]->swapDoneMoving();
				break;
			}
			//the movement functions returns a bool. True if they moved, 
			//false in case of collision
			bool moved = moveNpc(npcMove.at(j), i, sound);
			//if the NPC collided: do the following
			if (!moved) {
				
				//cout << "failed with move " << npcMove.at(j) << ", place " << j << endl;
				//get a new series of moves to attempt
				intVector tryMove;
				tryMove = mNpcVector[i]->collide(npcMove, j);
				//try out the new list of steps
				for (intVector::size_type k = 0; k < tryMove.size(); k++) {
					//again, break if 0, breakMove is made true so that
					//the entire turn will end for the current character
					//if there is no movement after collision
					if (tryMove.at(k) == 0) {
						breakMove = true;
						break;
					}
					//check every move. If one of them works, return to standard
					//movement pattern
					bool retryMoved = moveNpc(tryMove.at(k), i, sound);
					if (retryMoved) {
						break;
					}
				}

				break;
			}
			else {
				//cout << "Moved " << npcMove.at(j) << endl;
			}
		}
	}

/*	for (NpcVector::size_type i = 0; i < mNpcVector.size(); i++) {
		coords c = { mNpcVector[i]->getX(), mNpcVector[i]->getY() };
		mNpcs[c] = mNpcVector[i];
		mGrid[mNpcVector[i]->getX()][mNpcVector[i]->getY()] = mNpcVector[i]->getType();
		//mNpcs.erase(at);
	}*/
	mTurnCount++;
	std::cout << "That was turn " << mTurnCount << "." << endl;
	if (mTurnCount >= 50) {
		std::cout << "GAME OVER" << endl;
	}
	std::cout << endl;
}

bool Map1::movePlayer(int dir, SoundManager &sound, sf::RenderWindow &window) {
		/*need temporary values to alter to avoid certain issues*/
		int tempX = mPlayer->getX();
		int tempY = mPlayer->getY();
		//float tempPosX = 0, tempPosY = 0;
		/*move according to the int*/
	switch (dir) {
		case 8:
			tempY--;
			//tempPosY += -52;
			break;
		case 9:
			tempY--;
			tempX++;
			//tempPosY += -52;
			//tempPosX += 64;
			break;
		case 6:
			tempX++;
			//tempPosX += 64;
			break;
		case 3:
			tempX++;
			tempY++;
			//tempPosY += 52;
			//tempPosX += 64;
			break;
		case 2:
			tempY++;
			//tempPosY += 52;
			break;
		case 1:
			tempY++;
			tempX--;
			//tempPosY += 52;
			//tempPosX += -64;
			break;
		case 4:
			tempX--;
			//tempPosX += -64;
			break;
		case 7:
			tempX--;
			tempY--;
			//tempPosY += -52;
			//tempPosX += -64;
			break;
		}
		/*Make sure we don't give meep a faulty position*/
		/*if (tempX >= mPlayer->getPosX()){
			tempX = mPlayer->getPosX - 1;
		}
		else if (tempX < 0){
			tempX = 0;
		}
		if (tempY >= mPlayer->getPosY()){
			tempY = mPlayer->getPosY() - 1;
		}
		else if (tempY < 0){
			tempY = 0;
		}*/

		/*move meep to new place in the array and return the original value
		to the last position*/
		//std::cout << "Meep trying to move to: " << tempX << ", " << tempY << " which has value " << mGrid[tempY][tempX] << endl;
	if (mGrid[tempY][tempX] >= 2.0f && mGrid[tempY][tempX] <= 2.4f) {
		mGrid[mPlayer->getY()][mPlayer->getX()] = mPlayer->getLast();
		if (mGrid[tempY][tempX] == 2.0f && mPlayer->getFunctioning()) {
			cutGrass++;
			mPlayer->setLast(2.1f);
		}
		else if (mGrid[tempY][tempX] == 2.2f && mPlayer->getFunctioning()) {
			cutDandelions++;
			mPlayer->setLast(2.3f);
		}

		else {
			mPlayer->setLast(mGrid[tempY][tempX]);
		}
		mGrid[tempY][tempX] = mPlayer->getType();
			//mPlayer->updPos(tempPosX, tempPosY);

			mPlayer->setX(tempX);
			mPlayer->setY(tempY);

			//Kan inte st�nga av gr�sklippning p� trasig klippare f�rr�n vi har ordentlig Render
			if (!mPlayer->getMowerEquipped()) {
				cutVector cut = mPlayer->getCuts();
				cutVector toCut;
				//Beautiful, I know.
			for (cutVector::size_type i = 0; i < cut.size(); i++) {
				if (mGrid[cut.at(i)[1]][cut.at(i)[0]] == 9.0f) {
						cutHedges++;
						mGrid[cut.at(i)[1]][cut.at(i)[0]] = 9.1f;
						}
					}
				}
			if (totalAmountOfGrass > 0) {
				std::cout << fixed << setprecision(0) << endl << "Meep has mowed: " << cutGrass << " grasstiles out of: " << totalAmountOfGrass << " total. % cut: " << (cutGrass / totalAmountOfGrass) * 100 << "." << endl;
			}
			if (totalAmountOfDandelions > 0) {
				std::cout << fixed << setprecision(0) << "Meep has mowed: " << cutDandelions << " dandelions out of: " << totalAmountOfDandelions << " total. % cut: " << (cutDandelions / totalAmountOfDandelions) * 100 << "." << endl;
			}
			if (totalAmountOfHedges > 0) {
				std::cout << fixed << setprecision(0) << "Meep has mowed: " << cutHedges << " hedges out of: " << totalAmountOfHedges << " total. % cut: " << (cutHedges / totalAmountOfHedges) * 100 << "." << endl;
			}
			//std::cout << "Meep moved to: " << tempX << ", " << tempY << " which now has value " << mGrid[tempY][tempX] << endl;
		return true;
		}
		else {
			//cout << endl << (int)floor(mGrid[tempY][tempX])-1 << endl;
			//sound.setSound(7);
			
			sound.playSound(20);
			cout << endl << (int)mGrid[tempY][tempX];

			int tempI;

			if (mGrid[tempY][tempX] == 0.6f) {
				tempI = 10;
			}
			else {
				tempI = (int)mGrid[tempY][tempX];
			}
			
			switch (tempI) {

			case 0: { //Fence
				sound.playSound(23);
				break;
			}

			case 1: { //Fence
				sound.playSound(23);
					break;
				}
			case 3: { //Stone
				sound.playSound(26);
				break;
			}
			case 4: { //Tr�
				sound.playSound(24);
				break;
			}
			case 6: { //Cat
				sound.playSound(21);
				break;
			}
			case 7: { //Munk
				int i = rand() % 4;


				sound.setParamValue(27, "Monks", i);
				sound.playSound(27);
				break;
			}
			case 9: { //H�ck
				sound.playSound(28);
				break;
			}
			case 10: { //Font�n
				sound.playSound(29);
				break;
			}
			}
			
			screenshake(window);
/*			if (mGrid[tempY][tempX] == 6){
				//Krock med Katt
				sound.playSound(0.1f);
			}
			else if (mGrid[tempY][tempX] == 7){
				//Krock med Vakt
				sound.playSound(0.1f);
			}
			else if (mGrid[tempY][tempX] == 1){
				//Krock med Staket
				sound.playSound(0);
			}
			else if (mGrid[tempY][tempX] == 3){
				//Krock med Sten
				sound.playSound(0
			}
			else if (mGrid[tempY][tempX] == 4){
				//Krock med Tr�d
				sound.playSound(0);
			}
			else if (mGrid[tempY][tempX] == 9){
				//Krock med H�ck
				sound.setSound(0);
				sound.playSound();
			}*/
		return false;
	}
}
/*string Map1::getGrass() {
	stringstream o;
	o << "Cut grass: " << (cutGrass / totalAmountOfGrass) * 100;
	return o.str();
}*/
bool Map1::moveNpc(int dir, int atPos, SoundManager &sound) {
	int tempX = mNpcVector.at(atPos)->getX();
	int tempY = mNpcVector.at(atPos)->getY();
	//float tempPosX = 0;
	//float tempPosY = 0;
	switch (dir) {
	case 8:
		tempY--;
		//tempPosY += -52;
		break;
	case 9:
		tempY--;
		tempX++;
		//tempPosY += -52;
		//tempPosX += 64;
		break;
	case 6:

		tempX++;
		//tempPosX += 64;
		break;
	case 3:
		tempX++;
		tempY++;
		//tempPosY += 52;
		//tempPosX += 64;
		break;
	case 5:
		tempX += 0;
		tempY += 0;
		break;
	case 2:
		tempY++;
		//tempPosY += 52;
		break;
	case 1:
		tempY++;
		tempX--;
		//tempPosY += 52;
		//tempPosX += -64;
		break;
	case 4:
		tempX--;
		//tempPosX += -64;
		break;
	case 7:
		tempX--;
		tempY--;
		//tempPosY += -52;
		//tempPosX += -64;
		break;
	}

	//cout << "Cat trying to move to: " << tempX << ", " << tempY << " which has value " << mGrid[tempY][tempX] << endl;
	if (mGrid[tempY][tempX] >= 2.0f && mGrid[tempY][tempX] < 3.0f) {
		
		mNextX = tempX;
		mNextY = tempY;

		mGrid[mNpcVector.at(atPos)->getY()][mNpcVector.at(atPos)->getX()] = mNpcVector.at(atPos)->getLast();
		coords tempCoords = { mNpcVector.at(atPos)->getX(), mNpcVector.at(atPos)->getY() };
		mNpcs.erase(tempCoords);
		mNpcVector.at(atPos)->setLast(mGrid[tempY][tempX]);
		tempCoords = { tempX, tempY };
		mNpcs[tempCoords] = mNpcVector[atPos];
		mGrid[tempY][tempX] = mNpcVector.at(atPos)->getType();
	
		//getX()/getY() will show old position, tempX/tempY will show new position

		mNpcVector.at(atPos)->setX(tempX);
		mNpcVector.at(atPos)->setY(tempY);

		//cout << "Cat moved to: " << tempX << ", " << tempY << " which now has value " << mGrid[tempY][tempX] << endl;
		return true;
	}
	else {
		if (mNpcVector.at(atPos)->getCollide()){
			//sound.playSound(mGrid[tempY][tempX]);
		}
/*		//Recognizes what it collides with. Sorta.
		if (mGrid[tempY][tempX] == 5 && mNpcs.at(atPos)->getCollide()){
			//Krock med Meep
			sound.playSound(0.1f);
			int dmg = 1;
			mPlayer->collideWith(dmg);
		}
		else if (mGrid[tempY][tempX] == 6 && mNpcs.at(atPos)->getCollide()){
			//Krock med Katt
			sound.playSound(0.1f);
		}
		else if (mGrid[tempY][tempX] == 7 && mNpcs.at(atPos)->getCollide()){
			//Krock med Vakt
			sound.playSound(0.1f);
		}
		else if (mGrid[tempY][tempX] == 1 && mNpcs.at(atPos)->getCollide()){
			//Krock med Staket
			sound.playSound(0.0);
		}
		else if (mGrid[tempY][tempX] == 3 && mNpcs.at(atPos)->getCollide()){
			//Krock med Sten
			sound.playSound(0.0);
		}
		else if (mGrid[tempY][tempX] == 4 && mNpcs.at(atPos)->getCollide()){
			//Krock med Tr�d
			sound.playSound(0.0);
		}
		else if (mGrid[tempY][tempX] == 9 && mNpcs.at(atPos)->getCollide()){
			//Krock med H�ck
			sound.setSound(0);
			sound.playSound();
		}*/

		//cout << "Cat tried: " << tempX << ", " << tempY << " which has value " << mGrid[tempY][tempX] << endl;
		return false;
	}
}
void Map1::screenshake(sf::RenderWindow &window) {
	int tempX, tempY;
	clock.restart();
	bool switchIf = false;
	bool temp;

	tempX = window.getPosition().x;
	tempY = window.getPosition().y;



	float tid = 0.02f;

	for (int i = 0; i < 5; i++) {


		int randomValueX = thor::random(-50, 50);
		int randomValueY = thor::random(-50, 50);

		switchIf = !switchIf;
		temp = false;
		if (switchIf) {
			while (!temp) {
				cout << clock.getElapsedTime().asSeconds() << endl;
				if (clock.getElapsedTime().asSeconds() >= tid) {
					temp = true;
					window.setPosition(sf::Vector2i(tempX + randomValueX, tempY + randomValueY));
					clock.restart();	
				}
			}
		}
		if (!switchIf) {
			while (!temp) {
				cout << clock.getElapsedTime().asSeconds() << endl;
				if (clock.getElapsedTime().asSeconds() >= tid) {
					temp = true;
					window.setPosition(sf::Vector2i(tempX - randomValueX, tempY - randomValueY));
					clock.restart();
				}
			}
		}
	}



	window.setPosition(sf::Vector2i(tempX, tempY));
}
void Map1::getMapInfo(){
	string saveFilePath = "Maps/"+mSavefile;
	ifstream file(saveFilePath);
	file >> mWidth >> mHeight >> pushMapX >> pushMapY >> mBronzeGrass >> mSilverGrass >> mGoldGrass >> mBronzeHedge  >> mSilverHedge  >> mGoldHedge >> mBronzeDandelion >> mSilverDandelion >> mGoldDandelion >> specialFeature >> meepSpawnDirection;
}

//Funktion f�r att returnera objekten
vector <StaticObjects*> Map1::getObjects() {
	return mObjects;
}

Player* Map1::getPlayer() {
	return mPlayer;
}

float** Map1::getGrid() {
	return mGrid;
}

Maps::NpcMap Map1::getNpcs() {
	return mNpcs;
}

vector<StaticObjects*> Map1::getLongObjects() {
	return mLongObjects;
}

int Map1::checkState() {
	return mState;
}
int Map1::getTurnCount() {
	return mTurnCount;
}
int Map1::getMaxTurns() {
	return mWinRounds;
}
int Map1::getGrass() {
	if (totalAmountOfGrass > 0) {
		return (int)((cutGrass / totalAmountOfGrass) * 100);
	}
	else {
		return 9999;
	}
}
int Map1::getHedges() {
	if (totalAmountOfHedges > 0) {
		return (int)((cutHedges / totalAmountOfHedges) * 100);
	}
	else {
		return 9999;
	}
}
int Map1::getDandelions() {
	if (totalAmountOfDandelions > 0) {
		return (int)((cutDandelions / totalAmountOfDandelions) * 100);
	}
	else {
		return 9999;
	}
}
vector<int>* Map1::getGoals() {
	delete mGetGoals;
	mGetGoals = new vector<int>;
	
	mGetGoals->push_back(mBronzeGrass);
	mGetGoals->push_back(mSilverGrass);
	mGetGoals->push_back(mGoldGrass);
	mGetGoals->push_back(mBronzeHedge);
	mGetGoals->push_back(mSilverHedge);
	mGetGoals->push_back(mGoldHedge);
	mGetGoals->push_back(mBronzeDandelion);
	mGetGoals->push_back(mSilverDandelion);
	mGetGoals->push_back(mGoldDandelion);
	return mGetGoals;
}
int Map1::getTurnsLeft() {
	return mWinRounds - mTurnCount;
}
int Map1::getMeepSpawnDirection() {
	return meepSpawnDirection;
}