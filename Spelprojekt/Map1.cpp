#include "Map1.h"
#include <iostream>
#include <math.h>

using namespace std;

static float widthOnTile = 64.0f;
static float heigthOnTile = 52.0f;
static int widthTile = 64;
static int heigthTile = 52;
static int pushGrassX = -32;
static int pushGrassY = -76;
static int pushFenceY = -76;

Map1::Map1(string savefile){
	mSavefile = savefile;
	getMapInfo();
	Stone::initialize();
	Grass::initialize();
	Fence::initialize();
	Tree::initialize();
	Hedge::initialize();
	Player::initialize();
	CharRand::initialize();
	CharPatrol::initialize();
}
Map1::~Map1(){
	Stone::finalize();
	Grass::finalize();
	Fence::finalize();
	Tree::finalize();
	Hedge::finalize();
	Player::finalize();
	CharRand::finalize();
	CharPatrol::finalize();
}

void Map1::resetGrid(){
	mGrid = createGrid(mWidth, mHeigth);
}

//Skapar array
float** Map1::createGrid(int width, int heigth){
	/*float grid[15][20] =
	{ { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 },
	{   1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 },
	{   1.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 },
	{   1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 },
	{   1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 },
	{   1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 },
	{   1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 },
	{   1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 },
	{   1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 },
	{   1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 },
	{   1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 },
	{   1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 },
	{   1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 },
	{   1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 },
	{   1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 } };
	*/

	float tempValue;
	ifstream file(mSavefile);
	file >> tempValue >> tempValue >> tempValue >> tempValue >> tempValue >> tempValue >> tempValue >> tempValue;

	float** array2d = 0;
	array2d = new float*[heigth];
	for (int i = 0; i < heigth; i++){
		array2d[i] = new float[width];
		for (int j = 0; j < width; j++){
			file >> tempValue;
			array2d[i][j] = tempValue;
		}
	}


	/*float** array2d = 0;
	array2d = new float*[15];
	for (int i = 0; i < 15; i++){
		array2d[i] = new float[20];
		for (int j = 0; j < 20; j++){
			array2d[i][j] = grid[i][j];
		}
	}*/

	return array2d;
}


/**************************************[EXAMPLE CODE FOR INSTANTIATING A PATROLLING ENEMY]***************************************************/
/*********************************************************************************************************************************************
//50x10 array med varje värde 0
int patrolPath[50][10] = {};
//skapar temporärt en array med bara de steg och turer som inte är noll.
int tempPath[4][4]{
	{ 6, 6, 6, 0 },
	{ 2, 2, 2, 2 },
	{ 4, 4, 4, 0 },
	{ 8, 8, 8, 8 }
};

//Flytta över alla siffror från temporära arrayen till den som ska skickas med i konstruktorn
for (int i = 0; i < sizeof(tempPath); i++){
	for (int j = 0; j < sizeof(tempPath[i]); j++){
		int k = tempPath[i][j];
		patrolPath[i][j] = k;
	}
}

//CharPatrol(int arrX, int arrY, float posX, float posY, int *moves[50][10])
int arraySpotX = 0;
int arraySpotY = 0;
float coordinateX = 0.0f;
float coordinateY = 0.0f;
//Kom ihåg att skicka adresssen till patrolPath då det sparas som en arraypekare
CharPatrol *example = new CharPatrol(arraySpotX, arraySpotY, coordinateX, coordinateY, &patrolPath);


**********************************************************************************************************************************************/

//Loopar igenom array och spawnar alla objekt
//Variabeln totalAmoutOfGrass håller koll på hur många gräs som skall kunna klippas
void Map1::spawnObjects(){

	
	//*************************************************************************************************************************************************
	//*************************************************************************************************************************************************
	//*************************************************************************************************************************************************
	//*************************************************************************************************************************************************

	//50x10 array med varje värde 0
	int **patrolPath = 0;
	patrolPath = new int*[50];
	for (int i = 0; i < 50; i++){
		patrolPath[i] = new int[10];
		for (int j = 0; j < 10; j++){
			patrolPath[i][j] = 0;
		}
	}
	//skapar temporärt en array med bara de steg och turer som inte är noll.
	int tempPath[5][4]{
			{ 4, 0, 0, 0 },
			{ 2, 2, 0, 0 },
			{ 6, 6, 6, 6 },
			{ 8, 8, 0, 0 },
			{ 4, 4, 4, 0 }
	};

	//Flytta över alla siffror från temporära arrayen till den som ska skickas med i konstruktorn
	for (int i = 0; i < 5; i++){
		for (int j = 0; j < 4; j++){
			patrolPath[i][j] = tempPath[i][j];
		}
	}

	//*************************************************************************************************************************************************
	//*************************************************************************************************************************************************
	//*************************************************************************************************************************************************
	//*************************************************************************************************************************************************
	mPlayer = new Player(new LawnMower(), new HedgeCutter(2, 1));
	mObjects.push_back(new Grass(0, 0, (widthOnTile), (heigthOnTile)));
	mObjects.push_back(new Grass(0, 0, (widthOnTile), (heigthOnTile)));
	mObjects[1]->setCut();
	mObjects.push_back(new Stone(0, 0, (widthOnTile), (heigthOnTile)));
	mLongObjects.push_back(new Tree(0, 0, (widthOnTile)-31, (heigthOnTile)-200)); //Träd: plats 0
	mLongObjects.push_back(new Fence(0, 0, (widthOnTile), (heigthOnTile)+pushFenceY, 1));
	mLongObjects.push_back(new Fence(0, 0, (widthOnTile), (heigthOnTile)+pushFenceY, 2));
	mLongObjects.push_back(new Fence(0, 0, (widthOnTile), (heigthOnTile)+pushFenceY, 3));
	mLongObjects.push_back(new Fence(0, 0, (widthOnTile), (heigthOnTile)+pushFenceY, 4));
	mLongObjects.push_back(new Fence(0, 0, (widthOnTile), (heigthOnTile)+pushFenceY, 5));
	mLongObjects.push_back(new Fence(0, 0, (widthOnTile), (heigthOnTile)+pushFenceY, 6));
	mLongObjects.push_back(new Fence(0, 0, (widthOnTile), (heigthOnTile)+pushFenceY, 7));
	mLongObjects.push_back(new Fence(0, 0, (widthOnTile), (heigthOnTile)+pushFenceY, 8));
	mLongObjects.push_back(new Fence(0, 0, (widthOnTile), (heigthOnTile)+pushFenceY, 9));
	mLongObjects.push_back(new Hedge(0, 0, (widthOnTile), (heigthOnTile)));
	mLongObjects.push_back(new Hedge(0, 0, (widthOnTile), (heigthOnTile)));
	mLongObjects[11]->setCut();
	mNpcs.push_back(new CharRand(0, 0, (widthOnTile), (heigthOnTile), 1, true));
	//mNpcs.push_back(new CharPatrol(0, 0, (widthOnTile), (heigthOnTile), patrolPath));

	for (ObjectsVector::size_type i = 0; i < mObjects.size(); i++){
		mObjects[i]->render();
	}

	for (NpcVector::size_type i = 0; i < mNpcs.size(); i++){
		mNpcs[i]->render();
	}

	for (ObjectsVector::size_type i = 0; i < mLongObjects.size(); i++){
		mLongObjects[i]->render();
	}
	//mPlayer->render();

	mGrid = createGrid(mWidth, mHeigth);
	
	for (int i = 0; i < mWidth; i++){
		for (int j = 0; j < mHeigth; j++){
			if (mGrid[j][i] == 2.0f){
				totalAmountOfGrass++;
			}
			if (mGrid[j][i] == 3.2f){
				totalAmountOfGrass++;
			}
			if (mGrid[j][i] == 3.4f){
				totalAmountOfGrass++;
			}
			if (mGrid[j][i] == 2.4f){
				totalAmountOfHedges++;
			}
		}
	}
	/*
	for (int i = 0; i < mWidth; i++){
		for (int j = 0; j < mHeigth; j++){
			if (mGrid[j][i] == 1){
				mObjects.push_back(new Grass(i, j, (i * widthOnTile) + pushGrassX, (j * heigthOnTile) + pushGrassY));

				mLongObjects.push_back(new Fence(i, j, (i * widthOnTile), (j * heigthOnTile) + pushFenceY, 1));
			}
			if (mGrid[j][i] == 1.1f){
				mObjects.push_back(new Grass(i, j, (i * widthOnTile) + pushGrassX, (j * heigthOnTile) + pushGrassY));

				mLongObjects.push_back(new Fence(i, j, (i * widthOnTile), (j * heigthOnTile) + pushFenceY, 1));
			}
			if (mGrid[j][i] == 1.2f){
				mObjects.push_back(new Grass(i, j, (i * widthOnTile) + pushGrassX, (j * heigthOnTile) + pushGrassY));

				mLongObjects.push_back(new Fence(i, j, (i * widthOnTile), (j * heigthOnTile) + pushFenceY, 2));
			}
			if (mGrid[j][i] == 1.3f){
				mObjects.push_back(new Grass(i, j, (i * widthOnTile) + pushGrassX, (j * heigthOnTile) + pushGrassY));

				mLongObjects.push_back(new Fence(i, j, (i * widthOnTile), (j * heigthOnTile) + pushFenceY, 3));
			}
			if (mGrid[j][i] == 1.4f){
				mObjects.push_back(new Grass(i, j, (i * widthOnTile) + pushGrassX, (j * heigthOnTile) + pushGrassY));

				mLongObjects.push_back(new Fence(i, j, (i * widthOnTile), (j * heigthOnTile) + pushFenceY, 4));
			}
			if (mGrid[j][i] == 1.5f){
				mObjects.push_back(new Grass(i, j, (i * widthOnTile) + pushGrassX, (j * heigthOnTile) + pushGrassY));

				mLongObjects.push_back(new Fence(i, j, (i * widthOnTile), (j * heigthOnTile) + pushFenceY, 5));
			}
			if (mGrid[j][i] == 1.6f){
				mObjects.push_back(new Grass(i, j, (i * widthOnTile) + pushGrassX, (j * heigthOnTile) + pushGrassY));

				mLongObjects.push_back(new Fence(i, j, (i * widthOnTile), (j * heigthOnTile) + pushFenceY, 6));
			}
			if (mGrid[j][i] == 1.7f){
				mObjects.push_back(new Grass(i, j, (i * widthOnTile) + pushGrassX, (j * heigthOnTile) + pushGrassY));

				mLongObjects.push_back(new Fence(i, j, (i * widthOnTile), (j * heigthOnTile) + pushFenceY, 7));
			}
			if (mGrid[j][i] == 1.8f){
				mObjects.push_back(new Grass(i, j, (i * widthOnTile) + pushGrassX, (j * heigthOnTile) + pushGrassY));

				mLongObjects.push_back(new Fence(i, j, (i * widthOnTile), (j * heigthOnTile) + pushFenceY, 8));
			}
			if (mGrid[j][i] == 1.9f){
				mObjects.push_back(new Grass(i, j, (i * widthOnTile) + pushGrassX, (j * heigthOnTile) + pushGrassY));
				mLongObjects.push_back(new Fence(i, j, (i * widthOnTile), (j * heigthOnTile) + pushFenceY, 9));
			}
			if (mGrid[j][i] == 2){
				totalAmountOfGrass++;
				mObjects.push_back(new Grass(i, j, (i * widthOnTile) + pushGrassX, (j * heigthOnTile) + pushGrassY));
			}
			if (mGrid[j][i] == 3){
				mObjects.push_back(new Stone(i, j, (i * widthOnTile), (j * heigthOnTile)));
			}
			if (mGrid[j][i] == 4){
				mObjects.push_back(new Grass(i, j, (i * widthOnTile) + pushGrassX, (j * heigthOnTile) + pushGrassY));
				mLongObjects.push_back(new Tree(i, j, (i * widthOnTile) - 31, (j * heigthOnTile) - 200));
			}
			if (mGrid[j][i] == 5){
				mObjects.push_back(new Grass(i, j, (i * widthOnTile) + pushGrassX, (j * heigthOnTile) + pushGrassY));
				mPlayer = new Player(i, j, new LawnMower(), new HedgeCutter(2, 1), (i * widthOnTile), (j * heigthOnTile));
			}
			if (mGrid[j][i] == 6){
				totalAmountOfGrass++;
				mObjects.push_back(new Grass(i, j, (i * widthOnTile) + pushGrassX, (j * heigthOnTile) + pushGrassY));
				mNpcs.push_back(new CharRand(i, j, (i * widthOnTile), (j * heigthOnTile), 1, true));
			}	
			if (mGrid[j][i] == 7){
				totalAmountOfGrass++;
				mObjects.push_back(new Grass(i, j, (i * widthOnTile) + pushGrassX, (j * heigthOnTile) + pushGrassY));
				mNpcs.push_back(new CharPatrol(i, j, (i * widthOnTile), (j * heigthOnTile), patrolPath));
			}
			if (mGrid[j][i] == 9){
				totalAmountOfHedges++;
				mObjects.push_back(new Grass(i, j, (i * widthOnTile) + pushGrassX, (j * heigthOnTile) + pushGrassY));
				mLongObjects.push_back(new Hedge(i, j, (i * widthOnTile), (j * heigthOnTile)));
			}
		}
	}*/
}

void Map1::render(sf::RenderWindow &window){

	for (int i = 0; i < mWidth; i++){
		for (int j = 0; j < mHeigth; j++){
				if (mGrid[j][i] == 1.1f){
					mObjects[0]->getSprite()->setPosition((i * widthOnTile) + pushGrassX, (j * heigthOnTile) + pushGrassY); //Sätter positionen enligt grid
					window.draw(mObjects[0]->getDrawSprite());
				}else
				if (mGrid[j][i] == 1.2f){
					mObjects[0]->getSprite()->setPosition((i * widthOnTile) + pushGrassX, (j * heigthOnTile) + pushGrassY); //Sätter positionen enligt grid
					window.draw(mObjects[0]->getDrawSprite());
				}else
				if (mGrid[j][i] == 1.3f){
					mObjects[0]->getSprite()->setPosition((i * widthOnTile) + pushGrassX, (j * heigthOnTile) + pushGrassY); //Sätter positionen enligt grid
					window.draw(mObjects[0]->getDrawSprite());
				}else
				if (mGrid[j][i] == 1.4f){
					mObjects[0]->getSprite()->setPosition((i * widthOnTile) + pushGrassX, (j * heigthOnTile) + pushGrassY); //Sätter positionen enligt grid
					window.draw(mObjects[0]->getDrawSprite());
				}else
				if (mGrid[j][i] == 1.5f){
					mObjects[0]->getSprite()->setPosition((i * widthOnTile) + pushGrassX, (j * heigthOnTile) + pushGrassY); //Sätter positionen enligt grid
					window.draw(mObjects[0]->getDrawSprite());
				}else
				if (mGrid[j][i] == 1.6f){
					mObjects[0]->getSprite()->setPosition((i * widthOnTile) + pushGrassX, (j * heigthOnTile) + pushGrassY); //Sätter positionen enligt grid
					window.draw(mObjects[0]->getDrawSprite());
				}else
				if (mGrid[j][i] == 1.7f){
					mObjects[0]->getSprite()->setPosition((i * widthOnTile) + pushGrassX, (j * heigthOnTile) + pushGrassY); //Sätter positionen enligt grid
					window.draw(mObjects[0]->getDrawSprite());
				}else
				if (mGrid[j][i] == 1.8f){
					mObjects[0]->getSprite()->setPosition((i * widthOnTile) + pushGrassX, (j * heigthOnTile) + pushGrassY); //Sätter positionen enligt grid
					window.draw(mObjects[0]->getDrawSprite());
				}else
				if (mGrid[j][i] == 1.9f){
					mObjects[0]->getSprite()->setPosition((i * widthOnTile) + pushGrassX, (j * heigthOnTile) + pushGrassY); //Sätter positionen enligt grid
					window.draw(mObjects[0]->getDrawSprite());
				}else
				if (mGrid[j][i] == 2.0f){ //Gräs
					mObjects[0]->getSprite()->setPosition((i * widthOnTile) + pushGrassX, (j * heigthOnTile) + pushGrassY); //Sätter positionen enligt grid
					window.draw(mObjects[0]->getDrawSprite());
				}else
				if (mGrid[j][i] == 2.1f){ //Klippt gräs
					mObjects[1]->getSprite()->setPosition((i * widthOnTile) + pushGrassX, (j * heigthOnTile) + pushGrassY); //Sätter positionen enligt grid
					window.draw(mObjects[1]->getDrawSprite());
				}else
				if (mGrid[j][i] == 3.0f){ //Sten
					mObjects[2]->getSprite()->setPosition((i * widthOnTile), (j * heigthOnTile)); //Sätter positionen enligt grid
					window.draw(mObjects[2]->getDrawSprite());
				}else
				if (mGrid[j][i] == 4.0f){ //Träd
					mObjects[0]->getSprite()->setPosition((i * widthOnTile) + pushGrassX, (j * heigthOnTile) + pushGrassY); //Sätter positionen enligt grid
					window.draw(mObjects[0]->getDrawSprite());
				}
				else
				if (mGrid[j][i] == 5.0f){ //Spelare Gräs, temp innan animation
					mObjects[0]->getSprite()->setPosition((i * widthOnTile) + pushGrassX, (j * heigthOnTile) + pushGrassY); //Sätter positionen enligt grid
					window.draw(mObjects[0]->getDrawSprite());
				}
				else
				if (mGrid[j][i] == 5.1f){ //Spelare klippt Gräs, temp innan animation
					mObjects[1]->getSprite()->setPosition((i * widthOnTile) + pushGrassX, (j * heigthOnTile) + pushGrassY); //Sätter positionen enligt grid
					window.draw(mObjects[1]->getDrawSprite());
				}
				else
				if (mGrid[j][i] == 6.0f){ //Rand Npc på Gräs, temp innan animation
					mObjects[0]->getSprite()->setPosition((i * widthOnTile) + pushGrassX, (j * heigthOnTile) + pushGrassY); //Sätter positionen enligt grid
					window.draw(mObjects[0]->getDrawSprite());
				}
				else
				if (mGrid[j][i] == 6.1f){ //Rand Npc på Klippt Gräs, temp innan animation
					mObjects[1]->getSprite()->setPosition((i * widthOnTile) + pushGrassX, (j * heigthOnTile) + pushGrassY); //Sätter positionen enligt grid
					window.draw(mObjects[1]->getDrawSprite());
				}
				else
				if (mGrid[j][i] == 7.0f){ //Patrull Npc på Gräs, temp innan animation
					mObjects[0]->getSprite()->setPosition((i * widthOnTile) + pushGrassX, (j * heigthOnTile) + pushGrassY); //Sätter positionen enligt grid
					window.draw(mObjects[0]->getDrawSprite());
				}
				else
				if (mGrid[j][i] == 7.1f){ //Patrull Npc på Klippt Gräs, temp innan animation
					mObjects[1]->getSprite()->setPosition((i * widthOnTile) + pushGrassX, (j * heigthOnTile) + pushGrassY); //Sätter positionen enligt grid
					window.draw(mObjects[1]->getDrawSprite());
				}
				else
				if (mGrid[j][i] == 9.0f){ //Häck
					mObjects[0]->getSprite()->setPosition((i * widthOnTile) + pushGrassX, (j * heigthOnTile) + pushGrassY); //Sätter positionen enligt grid
					window.draw(mObjects[0]->getDrawSprite());
				}
				else
				if (mGrid[j][i] == 9.1f){ //Klippt Häck
					mObjects[0]->getSprite()->setPosition((i * widthOnTile) + pushGrassX, (j * heigthOnTile) + pushGrassY); //Sätter positionen enligt grid
					window.draw(mObjects[0]->getDrawSprite());
				}

		}
	}
	for (int i = 0; i < mWidth; i++){
		for (int j = 0; j < mHeigth; j++){
				if (mGrid[j][i] == 5.0f){ //Spelare Gräs, temp innan animation
					mPlayer->getSprite()->setPosition((i * widthOnTile), (j * heigthOnTile));
					window.draw(mPlayer->getDrawSprite());
					mPlayer->setX(i);
					mPlayer->setY(j);
				}else
				if (mGrid[j][i] == 5.1f){ //Spelare Klippt Gräs, temp innan animation
					mPlayer->getSprite()->setPosition((i * widthOnTile), (j * heigthOnTile));
					window.draw(mPlayer->getDrawSprite());
				}else
				if (mGrid[j][i] == 6.0f){ //Rand Npc Gräs, temp innan animation
					mNpcs[0]->getSprite()->setPosition((i * widthOnTile), (j * heigthOnTile)); //Sätter positionen enligt grid
					window.draw(mNpcs[0]->getDrawSprite());
				}else
				if (mGrid[j][i] == 6.1f){ //Rand Npc Klippt Gräs, temp innan animation
					mNpcs[0]->getSprite()->setPosition((i * widthOnTile), (j * heigthOnTile)); //Sätter positionen enligt grid
					window.draw(mNpcs[0]->getDrawSprite());
				}else
				if (mGrid[j][i] == 7.0f){ //Patrull Npc Gräs, temp innan animation
					//mNpcs[1]->getSprite()->setPosition((i * widthOnTile), (j * heigthOnTile)); //Sätter positionen enligt grid
					//window.draw(mNpcs[1]->getDrawSprite());
				}else
				if (mGrid[j][i] == 7.1f){ //Patrull Npc Klippt Gräs, temp innan animation
					//mNpcs[1]->getSprite()->setPosition((i * widthOnTile), (j * heigthOnTile)); //Sätter positionen enligt grid
					//window.draw(mNpcs[1]->getDrawSprite());
				}
		}
	}
	for (int i = 0; i < mWidth; i++){
		for (int j = 0; j < mHeigth; j++){
				if (mGrid[j][i] == 4.0f){ //Träd
					mLongObjects[0]->getSprite()->setPosition((i * widthOnTile) - 31, (j * heigthOnTile) - 200); //Sätter positionen enligt grid
					window.draw(mLongObjects[0]->getDrawSprite());
				} 
				else
				if (mGrid[j][i] == 1.1f){
					mLongObjects[1]->getSprite()->setPosition((i * widthOnTile), (j * heigthOnTile) + pushFenceY); //Sätter positionen enligt grid
					window.draw(mLongObjects[1]->getDrawSprite());
				}else
				if (mGrid[j][i] == 1.2f){
					mLongObjects[2]->getSprite()->setPosition((i * widthOnTile), (j * heigthOnTile) + pushFenceY); //Sätter positionen enligt grid
					window.draw(mLongObjects[2]->getDrawSprite());
				}else
				if (mGrid[j][i] == 1.3f){
					mLongObjects[3]->getSprite()->setPosition((i * widthOnTile), (j * heigthOnTile) + pushFenceY); //Sätter positionen enligt grid
					window.draw(mLongObjects[3]->getDrawSprite());
				}else
				if (mGrid[j][i] == 1.4f){
					mLongObjects[4]->getSprite()->setPosition((i * widthOnTile), (j * heigthOnTile) + pushFenceY); //Sätter positionen enligt grid
					window.draw(mLongObjects[4]->getDrawSprite());
				}else
				if (mGrid[j][i] == 1.5f){
					mLongObjects[5]->getSprite()->setPosition((i * widthOnTile), (j * heigthOnTile) + pushFenceY); //Sätter positionen enligt grid
					window.draw(mLongObjects[5]->getDrawSprite());
				}else
				if (mGrid[j][i] == 1.6f){
					mLongObjects[6]->getSprite()->setPosition((i * widthOnTile), (j * heigthOnTile) + pushFenceY); //Sätter positionen enligt grid
					window.draw(mLongObjects[6]->getDrawSprite());
				}else
				if (mGrid[j][i] == 1.7f){
					mLongObjects[7]->getSprite()->setPosition((i * widthOnTile), (j * heigthOnTile) + pushFenceY); //Sätter positionen enligt grid
					window.draw(mLongObjects[7]->getDrawSprite());
				}else
				if (mGrid[j][i] == 1.8f){
					mLongObjects[8]->getSprite()->setPosition((i * widthOnTile), (j * heigthOnTile) + pushFenceY); //Sätter positionen enligt grid
					window.draw(mLongObjects[8]->getDrawSprite());
				}else
				if (mGrid[j][i] == 1.9f){
					mLongObjects[9]->getSprite()->setPosition((i * widthOnTile), (j * heigthOnTile) + pushFenceY); //Sätter positionen enligt grid
					window.draw(mLongObjects[9]->getDrawSprite());
				}else
				if (mGrid[j][i] == 9.0f){ //Häck
					mLongObjects[10]->getSprite()->setPosition((i * widthOnTile), (j * heigthOnTile)); //Sätter positionen enligt grid
					window.draw(mLongObjects[10]->getDrawSprite());
				}else
				if (mGrid[j][i] == 9.1f){ //Klippt Häck
					mLongObjects[11]->getSprite()->setPosition((i * widthOnTile), (j * heigthOnTile)); //Sätter positionen enligt grid
					window.draw(mLongObjects[11]->getDrawSprite());
				}
		}
	}
}

/*This code looks a ton better with helper functions movePlayer(int dir)
and moveNpc(int dir, int atPos) for each individual step.*/
void Map1::takeTurn(int dir, SoundManager &sound){
	/*get the intVector that lists all of the individual 1-tile moves*/
	intVector meepMove = mPlayer->move(dir);
	/*go through the vector and move 1 step int*/
	for (intVector::size_type i = 0; i < meepMove.size(); i++){
		bool moved = movePlayer(meepMove.at(i), sound);
		if (!moved){
			mPlayer->collide(meepMove, i);
			break;
		}
	}
	/*Do this for every NPC in the vector*/
	/*for (NpcVector::size_type i = 0; i < mNpcs.size(); i++){
		//get their movement vector
		intVector npcMove = mNpcs.at(i)->move();
		bool breakMove = false;
		//For every int in the vector, do the following
		for (intVector::size_type j = 0; j < npcMove.size(); j++){
			//0 means end of movement. Needed for patrols. 
			//Breakmove means that the entire movement for this character
			//is over for the turn
			if (npcMove.at(j) == 0 || breakMove){
				breakMove = false;
				break;
			}
			//the movement functions returns a bool. True if they moved, 
			//false in case of collision
			bool moved = moveNpc(npcMove.at(j), i, sound);
			//if the NPC collided: do the following
			if (!moved){
				//cout << "failed with move " << npcMove.at(j) << ", place " << j << endl;
				//get a new series of moves to attempt
				intVector tryMove;
				tryMove = mNpcs.at(i)->collide(npcMove, j);
				//try out the new list of steps
				for (intVector::size_type k = 0; k < tryMove.size(); k++){
					//again, break if 0, breakMove is made true so that
					//the entire turn will end for the current character
					//if there is no movement after collision
					if (tryMove.at(k) == 0){
						breakMove = true;
						break;
					}
					//check every move. If one of them works, return to standard
					movement pattern
					bool retryMoved = moveNpc(tryMove.at(k), i, sound);
					if (retryMoved){
						break;
					}
				}

				break;
			}*/
			/*else {
				cout << "Moved " << npcMove.at(j) << endl;
			}*/
		//}
	//}
	mTurnCount++;
	std::cout << "That was turn " << mTurnCount << "." << endl;
	if (mTurnCount >= 50){
		std::cout << "GAME OVER" << endl;
	}
	std::cout << endl;
}

bool Map1::movePlayer(int dir, SoundManager &sound){
		/*need temporary values to alter to avoid certain issues*/
		int tempX = mPlayer->getX();
		int tempY = mPlayer->getY();
		//float tempPosX = 0, tempPosY = 0;
		/*move according to the int*/
	switch (dir){
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
		std::cout << "Meep trying to move to: " << tempX << ", " << tempY << " which has value " << mGrid[tempY][tempX] << endl;
		if (mGrid[tempY][tempX] >= 2.0f && mGrid[tempY][tempX] < 2.2f){
			mGrid[mPlayer->getY()][mPlayer->getX()] = mPlayer->getLast();
			if (mGrid[tempY][tempX] == 2.0f){
				std::cout << "y grass no cut" << endl;
				mPlayer->setLast(2.1);
			}
			else{
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
				for (cutVector::size_type i = 0; i < cut.size(); i++){
					if (mGrid[cut.at(i)[1]][cut.at(i)[0]] == 9.0f){
						mGrid[cut.at(i)[1]][cut.at(i)[0]] = 9.1f;
					}
				}
			}
			std::cout << endl << "Meep has mowed: " << cutGrass << " grasstiles out of: " << totalAmountOfGrass << " total." << endl;
			std::cout << "Meep has mowed: " << cutHedges << " hedges out of: " << totalAmountOfHedges << " total." << endl;

			std::cout << "Meep moved to: " << tempX << ", " << tempY << " which now has value " << mGrid[tempY][tempX] << endl;
		return true;
		}
		else {
			//cout << endl << (int)floor(mGrid[tempY][tempX])-1 << endl;
			//sound.setSound(7);
			//sound.playSound((mGrid[tempY][tempX]));
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
				sound.playSound(0);
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

void Map1::deleteContent()
{
	while (!mObjects.empty()){
		delete mObjects[0];
		mObjects.erase(mObjects.begin());
	}
	while (!mNpcs.empty()){
		delete mNpcs[0];
		mNpcs.erase(mNpcs.begin());
	}
	while (!mLongObjects.empty()){
		delete mLongObjects[0];
		mLongObjects.erase(mLongObjects.begin());
	}

	delete mPlayer;
	totalAmountOfGrass = 0;
	totalAmountOfHedges = 0;
	turnsLeft = 50;
	cutGrass = 0;
	cutHedges = 0;
	mTurnCount = 0;
}

bool Map1::moveNpc(int dir, int atPos, SoundManager &sound){
	int tempX = mNpcs.at(atPos)->getX();
	int tempY = mNpcs.at(atPos)->getY();
	float tempPosX = 0;
	float tempPosY = 0;
	switch (dir){
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

	//cout << "Cat trying to move to: " << tempX << ", " << tempY << " which has value " << mGrid[tempY][tempX] << endl;
	if (mGrid[tempY][tempX] >= 2.2f && mGrid[tempY][tempX] < 2.2f){
		mGrid[mNpcs.at(atPos)->getY()][mNpcs.at(atPos)->getX()] = mNpcs.at(atPos)->getLast();
		mNpcs.at(atPos)->setLast(mGrid[tempY][tempX]);
		mGrid[tempY][tempX] = mNpcs.at(atPos)->getType();
		mNpcs.at(atPos)->updPos(tempPosX, tempPosY);

		mNpcs.at(atPos)->setX(tempX);
		mNpcs.at(atPos)->setY(tempY);
		//cout << "Cat moved to: " << tempX << ", " << tempY << " which now has value " << mGrid[tempY][tempX] << endl;
		return true;
	}
	else {
		if (mNpcs.at(atPos)->getCollide()){
			sound.playSound((int)floor(mGrid[tempY][tempX]) - 1);
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

void Map1::getMapInfo(){
	ifstream file(mSavefile);
	file >> mWidth >> mHeigth >> mBronzeGrass >> mBronzeHedge >> mSilverGrass >> mSilverHedge >> mGoldGrass >> mGoldHedge;
}

//Funktion för att returnera objekten
vector<StaticObjects*> Map1::getObjects(){
	return mObjects;
}
Player* Map1::getPlayer(){
	return mPlayer;
}

float** Map1::getGrid(){
	return mGrid;
}

vector<Character*> Map1::getNpcs(){
	return mNpcs;
}
vector<StaticObjects*> Map1::getLongObjects(){
	return mLongObjects;
}