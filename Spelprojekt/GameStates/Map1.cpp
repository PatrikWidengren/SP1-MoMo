#include "Map1.h"
#include <iostream>
#include <iomanip>


using namespace std;

static float widthOnTile = 64.0f;
static float heightOnTile = 52.0f;
static int widthTile = 64;
static int heightTile = 52;
static int pushGrassX = -32;
static int pushGrassY = -76;
static int pushFenceY = -76;
static int pushMeepX = -96;
static int pushMeepY = -116;

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
}
Map1::~Map1() {
	Stone::finalize();
	Grass::finalize();
	Fence::finalize();
	Tree::finalize();
	Hedge::finalize();
	Gravel::finalize();
	Dandelion::finalize();
	Player::finalize();
	CharRand::finalize();
	CharPatrol::finalize();
	Fountain::finalize();

	mNpcs.clear();
	/*while (!mNpcVector.empty()) {
		delete mNpcVector[0];
		mNpcVector.erase(mNpcVector.begin());
	}*/
}

void Map1::resetGrid(){
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
	mGrid = createGrid(mWidth, mHeight);
	turnsLeft = 50;
	cutGrass = 0;
	cutHedges = 0;
	cutDandelions = 0;
	mTurnCount = 0;
	mSkipLines = 0;
}

//Skapar array
float** Map1::createGrid(int width, int height) {
	float tempValue;
	string saveFilePath = "Maps/" + mSavefile;
	ifstream file(saveFilePath);
	file >> tempValue >> tempValue >> tempValue >> tempValue >> tempValue >> tempValue >> tempValue >> tempValue >> tempValue >> tempValue >> tempValue >> tempValue >> tempValue;

	float** array2d;
	if (width > height) {
		array2d = new float*[width];
		for (int i = 0; i < width; i++) {
			array2d[i] = new float[height];
			for (int j = 0; j < height; j++) {
				array2d[i][j] = 0;
			}
		}
	}
	//Skapar grid på annat sätt om height är större än width
	else {
		array2d = new float*[height];
		for (int i = 0; i < height; i++) {
			array2d[i] = new float[width];
			for (int j = 0; j < width; j++) {
				array2d[i][j] = 0;
			}
		}
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			file >> tempValue;
			array2d[i][j] = tempValue;
		}
	}
	return array2d;
}

//Loopar igenom array och spawnar alla objekt
//Variabeln totalAmoutOfGrass håller koll på hur många gräs som skall kunna klippas, samma med hedge & dandelions
//skipLines räknar varje värde som sparas från patrullens .txt fil, för att inte ladda samma värden för flera patruller
int** Map1::getPatrolPath(int &skipLines) {
	string patrolFilePath = "Maps/patrols/patrols_" + mSavefile;
	ifstream file(patrolFilePath);
	int tempValue;
	int patrolPathWidth;
	int patrolPathHeight;

	//Loop för att komma förbi tidigare patrull-paths
	for (int i = 0; i < skipLines; i++) {
		file >> tempValue;
	}

	file >> patrolPathWidth >> patrolPathHeight;
	skipLines += 2;

	//patrolPathWidth + 1, eftersom mapeditorn inte sparar en extra nollrad, dvs vi skapar en extra nollrad här
	//här sparas bara nollor i hela arrayen
	int** patrolPath;
	patrolPath = new int*[patrolPathWidth + 1];
	for (int i = 0; i < patrolPathWidth + 1; i++) {
		patrolPath[i] = new int[patrolPathHeight];
		for (int j = 0; j < patrolPathHeight; j++) {
			//file >> tempValue;
			patrolPath[i][j] = 0;
		}
	}

	//här sätts värdena till patrolPath från .txt fil
	for (int i = 0; i < patrolPathWidth; i++) {
		for (int j = 0; j < patrolPathHeight; j++) {
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
	mObjects.push_back(new Fountain(0, 0, widthOnTile, heightOnTile));

	mLongObjects.push_back(new Tree(0, 0, (widthOnTile)-31, (heightOnTile)-200)); //Träd: plats 0
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
	
	for (int j = 0; j < mHeight; j++) {
		for (int i = 0; i < mWidth; i++) {
			if (mGrid[j][i] == 2.0f) {
				totalAmountOfGrass++;
			}
			if (mGrid[j][i] == 2.2f) {
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
			if (mGrid[j][i] >= 6.0f && mGrid[j][i] < 7.0f) { //Rand Npc Gräs, temp innan animation
				coords c = { i, j };
				mNpcs[c] = new CharRand(i, j, 2, true);
			}
			else if (mGrid[j][i] >= 7.0f && mGrid[j][i] < 8.0f) {
				coords c = { i, j };
				mNpcs[c] = new CharPatrol(i, j, getPatrolPath(mSkipLines));
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

void Map1::render(sf::RenderWindow &window, AnimeManager &anime) {

	for (int j = 0; j < mHeight; j++) {
		for (int i = 0; i < mWidth; i++) {
			/*if (mGrid[j][i] == 0.1f) {
				mObjects[0]->getSprite()->setPosition((i * widthOnTile) + pushGrassX, (j * heightOnTile) + pushGrassY); //Sätter positionen enligt grid
				window.draw(mObjects[0]->getDrawSprite());
			}*/
			if (mGrid[j][i] == 1.1f) {
				mObjects[0]->getSprite()->setPosition((i * widthOnTile) + pushGrassX, (j * heightOnTile) + pushGrassY); //Sätter positionen enligt grid
				window.draw(mObjects[0]->getDrawSprite());
			}
			else if (mGrid[j][i] == 1.2f) {
				mObjects[0]->getSprite()->setPosition((i * widthOnTile) + pushGrassX, (j * heightOnTile) + pushGrassY); //Sätter positionen enligt grid
				window.draw(mObjects[0]->getDrawSprite());
			}
			else if (mGrid[j][i] == 1.3f) {
				mObjects[0]->getSprite()->setPosition((i * widthOnTile) + pushGrassX, (j * heightOnTile) + pushGrassY); //Sätter positionen enligt grid
				window.draw(mObjects[0]->getDrawSprite());
			}
			else if (mGrid[j][i] == 1.4f) {
				mObjects[0]->getSprite()->setPosition((i * widthOnTile) + pushGrassX, (j * heightOnTile) + pushGrassY); //Sätter positionen enligt grid
				window.draw(mObjects[0]->getDrawSprite());
			}
			else if (mGrid[j][i] == 1.5f) {
				mObjects[0]->getSprite()->setPosition((i * widthOnTile) + pushGrassX, (j * heightOnTile) + pushGrassY); //Sätter positionen enligt grid
				window.draw(mObjects[0]->getDrawSprite());
			}
			else if (mGrid[j][i] == 1.6f) {
				mObjects[0]->getSprite()->setPosition((i * widthOnTile) + pushGrassX, (j * heightOnTile) + pushGrassY); //Sätter positionen enligt grid
				window.draw(mObjects[0]->getDrawSprite());
			}
			else if (mGrid[j][i] == 1.7f) {
				mObjects[0]->getSprite()->setPosition((i * widthOnTile) + pushGrassX, (j * heightOnTile) + pushGrassY); //Sätter positionen enligt grid
				window.draw(mObjects[0]->getDrawSprite());
			}
			else if (mGrid[j][i] == 1.8f) {
				mObjects[0]->getSprite()->setPosition((i * widthOnTile) + pushGrassX, (j * heightOnTile) + pushGrassY); //Sätter positionen enligt grid
				window.draw(mObjects[0]->getDrawSprite());
			}
			else if (mGrid[j][i] == 1.9f) {
				mObjects[0]->getSprite()->setPosition((i * widthOnTile) + pushGrassX, (j * heightOnTile) + pushGrassY); //Sätter positionen enligt grid
				window.draw(mObjects[0]->getDrawSprite());
			}
			else if (mGrid[j][i] == 2.0f) { //Gräs
				mObjects[0]->getSprite()->setPosition((i * widthOnTile) + pushGrassX, (j * heightOnTile) + pushGrassY); //Sätter positionen enligt grid
				window.draw(mObjects[0]->getDrawSprite());
			}
			else if (mGrid[j][i] == 2.1f) { //Klippt gräs
				mObjects[1]->getSprite()->setPosition((i * widthOnTile) + pushGrassX, (j * heightOnTile) + pushGrassY); //Sätter positionen enligt grid
				window.draw(mObjects[1]->getDrawSprite());
			}
			else if (mGrid[j][i] == 2.2f) { //Maskros
				mObjects[3]->getSprite()->setPosition((i * widthOnTile) + pushGrassX, (j * heightOnTile) + pushGrassY); //Sätter positionen enligt grid
				window.draw(mObjects[3]->getDrawSprite());
			}
			else if (mGrid[j][i] == 2.3f) { //Klippt Maskros
				mObjects[4]->getSprite()->setPosition((i * widthOnTile) + pushGrassX, (j * heightOnTile) + pushGrassY); //Sätter positionen enligt grid
				window.draw(mObjects[4]->getDrawSprite());
			}
			else if (mGrid[j][i] == 2.4f) { //Grusväg
				mObjects[5]->getSprite()->setPosition((i * widthOnTile), (j * heightOnTile)); //Sätter positionen enligt grid
				window.draw(mObjects[5]->getDrawSprite());
			}
			else if (mGrid[j][i] == 3.0f) { //Sten
				mObjects[0]->getSprite()->setPosition((i * widthOnTile) + pushGrassX, (j * heightOnTile) + pushGrassY); //Sätter positionen enligt grid
				window.draw(mObjects[0]->getDrawSprite());
				mObjects[2]->getSprite()->setPosition((i * widthOnTile), (j * heightOnTile) - 15); //Sätter positionen enligt grid
				window.draw(mObjects[2]->getDrawSprite());
			}
			else if (mGrid[j][i] == 4.0f) { //Träd
				mObjects[0]->getSprite()->setPosition((i * widthOnTile) + pushGrassX, (j * heightOnTile) + pushGrassY); //Sätter positionen enligt grid
				window.draw(mObjects[0]->getDrawSprite());
			}
			else if (mGrid[j][i] == 5.0f) { //Spelare Gräs, temp innan animation
				mObjects[0]->getSprite()->setPosition((i * widthOnTile) + pushGrassX, (j * heightOnTile) + pushGrassY); //Sätter positionen enligt grid
				window.draw(mObjects[0]->getDrawSprite());
			}
			else if (mGrid[j][i] == 5.1f) { //Spelare klippt Gräs, temp innan animation
				mObjects[1]->getSprite()->setPosition((i * widthOnTile) + pushGrassX, (j * heightOnTile) + pushGrassY); //Sätter positionen enligt grid
				window.draw(mObjects[1]->getDrawSprite());
			}
			else if (mGrid[j][i] == 5.2f) { //Spelare maskros, temp innan animation
				mObjects[3]->getSprite()->setPosition((i * widthOnTile) + pushGrassX, (j * heightOnTile) + pushGrassY); //Sätter positionen enligt grid
				window.draw(mObjects[3]->getDrawSprite());
			}
			else if (mGrid[j][i] == 5.3f) { //Spelare klippt maskros, temp innan animation
				mObjects[4]->getSprite()->setPosition((i * widthOnTile) + pushGrassX, (j * heightOnTile) + pushGrassY); //Sätter positionen enligt grid
				window.draw(mObjects[4]->getDrawSprite());
			}
			else if (mGrid[j][i] == 5.4f) { //Spelare grusväg, temp innan animation
				mObjects[5]->getSprite()->setPosition((i * widthOnTile), (j * heightOnTile)); //Sätter positionen enligt grid
				window.draw(mObjects[5]->getDrawSprite());
			}
			else if (mGrid[j][i] == 6.0f) { //Rand Npc på Gräs, temp innan animation
				mObjects[0]->getSprite()->setPosition((i * widthOnTile) + pushGrassX, (j * heightOnTile) + pushGrassY); //Sätter positionen enligt grid
				window.draw(mObjects[0]->getDrawSprite());
			}
			else if (mGrid[j][i] == 6.1f) { //Rand Npc på Klippt Gräs, temp innan animation
				mObjects[1]->getSprite()->setPosition((i * widthOnTile) + pushGrassX, (j * heightOnTile) + pushGrassY); //Sätter positionen enligt grid
				window.draw(mObjects[1]->getDrawSprite());
			}
			else if (mGrid[j][i] == 6.2f) { //Rand Npc på maskros, temp innan animation
				mObjects[3]->getSprite()->setPosition((i * widthOnTile) + pushGrassX, (j * heightOnTile) + pushGrassY); //Sätter positionen enligt grid
				window.draw(mObjects[3]->getDrawSprite());
			}
			else if (mGrid[j][i] == 6.3f) { //Rand Npc på Klippt maskros, temp innan animation
				mObjects[4]->getSprite()->setPosition((i * widthOnTile) + pushGrassX, (j * heightOnTile) + pushGrassY); //Sätter positionen enligt grid
				window.draw(mObjects[4]->getDrawSprite());
			}
			else if (mGrid[j][i] == 6.4f) { //Rand Npc på grusväg, temp innan animation
				mObjects[5]->getSprite()->setPosition((i * widthOnTile), (j * heightOnTile)); //Sätter positionen enligt grid
				window.draw(mObjects[5]->getDrawSprite());
			}
			else if (mGrid[j][i] == 7.0f) { //Patrull Npc på Gräs, temp innan animation
				mObjects[0]->getSprite()->setPosition((i * widthOnTile) + pushGrassX, (j * heightOnTile) + pushGrassY); //Sätter positionen enligt grid
				window.draw(mObjects[0]->getDrawSprite());
			}
			else if (mGrid[j][i] == 7.1f) { //Patrull Npc på Klippt Gräs, temp innan animation
				mObjects[1]->getSprite()->setPosition((i * widthOnTile) + pushGrassX, (j * heightOnTile) + pushGrassY); //Sätter positionen enligt grid
				window.draw(mObjects[1]->getDrawSprite());
			}
			else if (mGrid[j][i] == 7.2f) { //Patrull Npc på maskros, temp innan animation
				mObjects[3]->getSprite()->setPosition((i * widthOnTile) + pushGrassX, (j * heightOnTile) + pushGrassY); //Sätter positionen enligt grid
				window.draw(mObjects[3]->getDrawSprite());
			}
			else if (mGrid[j][i] == 7.3f) { //Patrull Npc på Klippt maskros, temp innan animation
				mObjects[4]->getSprite()->setPosition((i * widthOnTile) + pushGrassX, (j * heightOnTile) + pushGrassY); //Sätter positionen enligt grid
				window.draw(mObjects[4]->getDrawSprite());
			}
			else if (mGrid[j][i] == 7.4f) { //Patrull Npc på grusväg, temp innan animation
				mObjects[5]->getSprite()->setPosition((i * widthOnTile), (j * heightOnTile)); //Sätter positionen enligt grid
				window.draw(mObjects[5]->getDrawSprite());
			}
			else if (mGrid[j][i] == 9.0f) { //Häck
				mObjects[0]->getSprite()->setPosition((i * widthOnTile) + pushGrassX, (j * heightOnTile) + pushGrassY); //Sätter positionen enligt grid
				window.draw(mObjects[0]->getDrawSprite());
			}
			else if (mGrid[j][i] == 9.1f) { //Klippt Häck
				mObjects[1]->getSprite()->setPosition((i * widthOnTile) + pushGrassX, (j * heightOnTile) + pushGrassY); //Sätter positionen enligt grid
				window.draw(mObjects[1]->getDrawSprite());
			}
			else if (mGrid[j][i] == 10.0f) { //Fontän
				mObjects[6]->getSprite()->setPosition((i * widthOnTile), (j * heightOnTile) + pushGrassY / 2); //Sätter positionen enligt grid
				window.draw(mObjects[6]->getDrawSprite());
			}
		}
	}

	for (int j = 0; j < mHeight; j++) {
		for (int i = 0; i < mWidth; i++) {
			if (mGrid[j][i] == 1.1f) {
				mLongObjects[1]->getSprite()->setPosition((i * widthOnTile), (j * heightOnTile) + pushFenceY); //Sätter positionen enligt grid
				window.draw(mLongObjects[1]->getDrawSprite());
			}
			else if (mGrid[j][i] == 1.3f) {
				mLongObjects[3]->getSprite()->setPosition((i * widthOnTile), (j * heightOnTile) + pushFenceY); //Sätter positionen enligt grid
				window.draw(mLongObjects[3]->getDrawSprite());
			}
			else if (mGrid[j][i] == 1.4f) {
				mLongObjects[4]->getSprite()->setPosition((i * widthOnTile), (j * heightOnTile) + pushFenceY); //Sätter positionen enligt grid
				window.draw(mLongObjects[4]->getDrawSprite());
			}
			else if (mGrid[j][i] == 1.5f) {
				mLongObjects[5]->getSprite()->setPosition((i * widthOnTile), (j * heightOnTile) + pushFenceY); //Sätter positionen enligt grid
				window.draw(mLongObjects[5]->getDrawSprite());
			}
			else if (mGrid[j][i] == 1.6f) {
				mLongObjects[6]->getSprite()->setPosition((i * widthOnTile), (j * heightOnTile) + pushFenceY); //Sätter positionen enligt grid
				window.draw(mLongObjects[6]->getDrawSprite());
			}
			else if (mGrid[j][i] == 1.7f) {
				mLongObjects[7]->getSprite()->setPosition((i * widthOnTile), (j * heightOnTile) + pushFenceY); //Sätter positionen enligt grid
				window.draw(mLongObjects[7]->getDrawSprite());
			}
			else if (mGrid[j][i] == 1.8f) {
				mLongObjects[8]->getSprite()->setPosition((i * widthOnTile), (j * heightOnTile) + pushFenceY); //Sätter positionen enligt grid
				window.draw(mLongObjects[8]->getDrawSprite());
			}
			else if (mGrid[j][i] == 1.9f) {
				mLongObjects[9]->getSprite()->setPosition((i * widthOnTile), (j * heightOnTile) + pushFenceY); //Sätter positionen enligt grid
				window.draw(mLongObjects[9]->getDrawSprite());
			}
			else if (mGrid[j][i] == 9.0f) { //Häck
				mLongObjects[10]->getSprite()->setPosition((i * widthOnTile) + pushGrassX, (j * heightOnTile) + pushGrassY - 12); //Sätter positionen enligt grid
				window.draw(mLongObjects[10]->getDrawSprite());
			}
			else if (mGrid[j][i] == 9.1f) { //Klippt Häck
				mLongObjects[11]->getSprite()->setPosition((i * widthOnTile) + pushGrassX, (j * heightOnTile) + pushGrassY - 22); //Sätter positionen enligt grid
				window.draw(mLongObjects[11]->getDrawSprite());
			}
		}
	}
	for (int j = 0; j < mHeight; j++) {
		for (int i = 0; i < mWidth; i++) {
			if (mGrid[j][i] == 4.0f) { //Träd
				mLongObjects[0]->getSprite()->setPosition((i * widthOnTile) - 31, (j * heightOnTile) - 200); //Sätter positionen enligt grid
				window.draw(mLongObjects[0]->getDrawSprite());
			}
			else if (mGrid[j][i] == 1.2f) {
				mLongObjects[2]->getSprite()->setPosition((i * widthOnTile), (j * heightOnTile) + pushFenceY); //Sätter positionen enligt grid
				window.draw(mLongObjects[2]->getDrawSprite());
			}
			else if (mGrid[j][i] == 5.0f) { //Spelare Gräs, temp innan animation
				anime.playTest();
				anime.getSpriteSheet()->setPosition((i * widthOnTile) + pushMeepX, (j * heightOnTile) + pushMeepY);
				window.draw(*anime.getSpriteSheet());
				//mPlayer->getSprite()->setPosition((i * widthOnTile), (j * heightOnTile) - 75);
					//window.draw(mPlayer->getDrawSprite());
					mPlayer->setX(i);
					mPlayer->setY(j);
			}
			else if (mGrid[j][i] == 5.1f) { //Spelare Klippt Gräs, temp innan animation
				anime.playTest();
				anime.getSpriteSheet()->setPosition((i * widthOnTile) + pushMeepX, (j * heightOnTile) + pushMeepY);
				window.draw(*anime.getSpriteSheet());
					/*mPlayer->getSprite()->setPosition((i * widthOnTile), (j * heightOnTile) - 75);
					window.draw(mPlayer->getDrawSprite());*/
				mPlayer->setLast(2.1f);
				mPlayer->setX(i);
				mPlayer->setY(j);
			}
			else if (mGrid[j][i] == 5.2f) { //Spelare maskros, temp innan animation
				anime.playTest();
				anime.getSpriteSheet()->setPosition((i * widthOnTile) + pushMeepX, (j * heightOnTile) + pushMeepY);
				window.draw(*anime.getSpriteSheet());
				/*mPlayer->getSprite()->setPosition((i * widthOnTile), (j * heightOnTile) - 75);
					window.draw(mPlayer->getDrawSprite());*/
				mPlayer->setLast(2.2f);
				mPlayer->setX(i);
				mPlayer->setY(j);
			}
			else if (mGrid[j][i] == 5.3f) { //Spelare klippt maskros, temp innan animation
				anime.playTest();
				anime.getSpriteSheet()->setPosition((i * widthOnTile) + pushMeepX, (j * heightOnTile) + pushMeepY);
				window.draw(*anime.getSpriteSheet());
				/*mPlayer->getSprite()->setPosition((i * widthOnTile), (j * heightOnTile) - 75);
					window.draw(mPlayer->getDrawSprite());*/
				mPlayer->setLast(2.3f);
				mPlayer->setX(i);
				mPlayer->setY(j);
			}
			else if (mGrid[j][i] == 5.4f) { //Spelare grusväg, temp innan animation
				anime.playTest();
				anime.getSpriteSheet()->setPosition((i * widthOnTile) + pushMeepX, (j * heightOnTile) + pushMeepY);
				window.draw(*anime.getSpriteSheet());
				mPlayer->setLast(2.4f);
				mPlayer->setX(i);
				mPlayer->setY(j);
				/*mPlayer->getSprite()->setPosition((i * widthOnTile), (j * heightOnTile) - 75);
					window.draw(mPlayer->getDrawSprite());*/
			}
			else if (mGrid[j][i] == 6.0f) { //Rand Npc Gräs, temp innan animation
				coords c = { i, j };
				if (mNpcs[c] != 0) {
					mNpcs[c]->playAnimation();
					mNpcs[c]->getSpriteSheet()->setPosition((i * widthOnTile), (j * heightOnTile)); //Sätter positionen enligt grid
					window.draw(*mNpcs[c]->getSpriteSheet());
				}
			}
			else if (mGrid[j][i] == 6.1f) { //Rand Npc Klippt Gräs, temp innan animation
				coords c = { i, j };
				if (mNpcs[c] != 0) {
					mNpcs[c]->playAnimation();
					mNpcs[c]->getSpriteSheet()->setPosition((i * widthOnTile), (j * heightOnTile)); //Sätter positionen enligt grid
					window.draw(*mNpcs[c]->getSpriteSheet());
				}
			}
			else if (mGrid[j][i] == 6.2f) { //Rand Npc maskros, temp innan animation
				coords c = { i, j };
				if (mNpcs[c] != 0) {
					mNpcs[c]->playAnimation();
					mNpcs[c]->getSpriteSheet()->setPosition((i * widthOnTile), (j * heightOnTile)); //Sätter positionen enligt grid
					window.draw(*mNpcs[c]->getSpriteSheet());
				}
				mNpcs[c]->setLast(2.2f);
			}
			else if (mGrid[j][i] == 6.3f) { //Rand Npc Klippt maskros, temp innan animation
				coords c = { i, j };
				if (mNpcs[c] != 0) {
					mNpcs[c]->playAnimation();
					mNpcs[c]->getSpriteSheet()->setPosition((i * widthOnTile), (j * heightOnTile)); //Sätter positionen enligt grid
					window.draw(*mNpcs[c]->getSpriteSheet());
				}
			}
			else if (mGrid[j][i] == 6.4f) { //Rand Npc grusväg, temp innan animation
				coords c = { i, j };
				if (mNpcs[c] != 0) {
					mNpcs[c]->playAnimation();
					mNpcs[c]->getSpriteSheet()->setPosition((i * widthOnTile), (j * heightOnTile)); //Sätter positionen enligt grid
					window.draw(*mNpcs[c]->getSpriteSheet());
				}
				mNpcs[c]->setLast(2.4f);
			}
			else if (mGrid[j][i] == 7.0f) { //Patrull Npc Gräs, temp innan animation
				coords c = { i, j };
				if (mNpcs[c] != 0) {
					mNpcs[c]->playAnimation();
					mNpcs[c]->getSpriteSheet()->setPosition((i * widthOnTile), (j * heightOnTile)); //Sätter positionen enligt grid
					window.draw(*mNpcs[c]->getSpriteSheet());
				}
			}
			else if (mGrid[j][i] == 7.1f) { //Patrull Npc Klippt Gräs, temp innan animation
				coords c = { i, j };
				if (mNpcs[c] != 0) {
					mNpcs[c]->playAnimation();
					mNpcs[c]->getSpriteSheet()->setPosition((i * widthOnTile), (j * heightOnTile)); //Sätter positionen enligt grid
					window.draw(*mNpcs[c]->getSpriteSheet());
				}
			}
			else if (mGrid[j][i] == 7.2f) { //Patrull Npc maskros, temp innan animation
				coords c = { i, j };
				if (mNpcs[c] != 0) {
					mNpcs[c]->playAnimation();
					mNpcs[c]->getSpriteSheet()->setPosition((i * widthOnTile), (j * heightOnTile)); //Sätter positionen enligt grid
					window.draw(*mNpcs[c]->getSpriteSheet());
				}
				mNpcs[c]->setLast(2.2f);
			}
			else if (mGrid[j][i] == 7.3f) { //Patrull Npc Klippt maskros, temp innan animation
				coords c = { i, j };
				if (mNpcs[c] != 0) {
					mNpcs[c]->playAnimation();
					mNpcs[c]->getSpriteSheet()->setPosition((i * widthOnTile), (j * heightOnTile)); //Sätter positionen enligt grid
					window.draw(*mNpcs[c]->getSpriteSheet());
				}
			}
			else if (mGrid[j][i] == 7.4f) { //Patrull Npc grusväg, temp innan animation
				coords c = { i, j };
				if (mNpcs[c] != 0) {
					mNpcs[c]->playAnimation();
					mNpcs[c]->getSpriteSheet()->setPosition((i * widthOnTile), (j * heightOnTile)); //Sätter positionen enligt grid
					window.draw(*mNpcs[c]->getSpriteSheet());
				}
				mNpcs[c]->setLast(2.4f);
			}
		}
	}
}

/*This code looks a ton better with helper functions movePlayer(int dir)
and moveNpc(int dir, int atPos) for each individual step.*/
void Map1::takeTurn(int dir, SoundManager &sound) {
	/*get the intVector that lists all of the individual 1-tile moves*/
	intVector meepMove = mPlayer->move(dir);
	/*go through the vector and move 1 step int*/
	for (intVector::size_type i = 0; i < meepMove.size(); i++) {
		bool moved = movePlayer(meepMove.at(i), sound);
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

bool Map1::movePlayer(int dir, SoundManager &sound) {
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

			//Kan inte stänga av gräsklippning på trasig klippare förrän vi har ordentlig Render
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
			sound.playSound((mGrid[tempY][tempX]));
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
				//Krock med Träd
				sound.playSound(0);
			}
			else if (mGrid[tempY][tempX] == 9){
				//Krock med Häck
				sound.setSound(0);
				sound.playSound();
			}*/
		return false;
	}
}

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
		/*if (mNpcs.at(atPos)->getCollide()){
			//sound.playSound((int)floor(mGrid[tempY][tempX]) - 1);
		}*/
		sound.playSound(mGrid[tempY][tempX]);
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
			//Krock med Träd
			sound.playSound(0.0);
		}
		else if (mGrid[tempY][tempX] == 9 && mNpcs.at(atPos)->getCollide()){
			//Krock med Häck
			sound.setSound(0);
			sound.playSound();
		}*/

		//cout << "Cat tried: " << tempX << ", " << tempY << " which has value " << mGrid[tempY][tempX] << endl;
		return false;
	}
}

void Map1::deleteContent()
{
	for (int j = 0; j < mHeight; j++) {
		for (int i = 0; i < mWidth; i++) {
			coords tempCoord = { i, j };
			if (!mNpcs[tempCoord] != 0) {
				delete mNpcs[tempCoord];
				mNpcs.erase(tempCoord);
			}
		}
	}
}

void Map1::getMapInfo(){
	string saveFilePath = "Maps/"+mSavefile;
	ifstream file(saveFilePath);
	file >> mWidth >> mHeight >> mBronzeGrass >> mSilverGrass >> mGoldGrass >> mBronzeHedge  >> mSilverHedge  >> mGoldHedge >> mBronzeDandelion >> mSilverDandelion >> mGoldDandelion >> specialFeature >> meepSpawnDirection;
}

//Funktion för att returnera objekten
vector<StaticObjects*> Map1::getObjects() {
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