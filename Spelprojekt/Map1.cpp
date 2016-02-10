#include "Map1.h"
#include <iostream>

using namespace std;

static float widthOnTile = 64.0f;
static float heigthOnTile = 52.0f;
static int widthTile = 64;
static int heigthTile = 52;

Map1::Map1(string savefile){
	mSavefile = savefile;
	getArraySize();
	Stone::initialize();
	Grass::initialize();
	Fence::initialize();
	Tree::initialize();
	Player::initialize();
	CharRand::initialize();
	CharPatrol::initialize();
}
Map1::~Map1(){
	Stone::finalize();
	Grass::finalize();
	Fence::finalize();
	Tree::finalize();
	Player::finalize();
	CharRand::finalize();
	CharPatrol::finalize();
}
void Map1::render(){
	for (ObjectsVector::size_type i = 0; i < mObjects.size(); i++){
		//mObjects[i]->getSprite();
		mObjects[i]->render();
	}
	for (NpcVector::size_type i = 0; i < mNpcs.size(); i++){
		mNpcs[i]->render();
	}
	mPlayer->render();
	for (ObjectsVector::size_type i = 0; i < mLongObjects.size(); i++){
		mLongObjects[i]->render();
	}
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
	file >> tempValue >> tempValue;
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

	/*
	//*************************************************************************************************************************************************
	//*************************************************************************************************************************************************
	//*************************************************************************************************************************************************
	//*************************************************************************************************************************************************

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

	//*************************************************************************************************************************************************
	//*************************************************************************************************************************************************
	//*************************************************************************************************************************************************
	//*************************************************************************************************************************************************

	*/

	mGrid = createGrid(mWidth, mHeigth);
	for (int i = 0; i < mWidth; i++){
		for (int j = 0; j < mHeigth; j++){
			if (mGrid[j][i] == 1){
				mObjects.push_back(new Grass(i, j, (i * widthOnTile), (j * heigthOnTile)));

				mObjects.push_back(new Fence(i, j, (i * widthOnTile), (j * heigthOnTile), 1));
			}
			if (mGrid[j][i] == 2){
				totalAmountOfGrass++;
				mObjects.push_back(new Grass(i, j, (i * widthOnTile), (j * heigthOnTile)));
			}
			if (mGrid[j][i] == 3){
				mObjects.push_back(new Stone(i, j, (i * widthOnTile), (j * heigthOnTile)));
			}
			if (mGrid[j][i] == 4){
				mObjects.push_back(new Grass(i, j, (i * widthOnTile), (j * heigthOnTile)));
				mLongObjects.push_back(new Tree(i, j, (i * widthOnTile) - 31, (j * heigthOnTile) - 200));
			}
			if (mGrid[j][i] == 5){
				mObjects.push_back(new Grass(i, j, (i * widthOnTile), (j * heigthOnTile)));
				mPlayer = new Player(i, j, new LawnMower(), (i * widthOnTile), (j * heigthOnTile));
			}
			if (mGrid[j][i] == 6){
				totalAmountOfGrass++;
				mObjects.push_back(new Grass(i, j, (i * widthOnTile), (j * heigthOnTile)));
				mNpcs.push_back(new CharRand(i, j, (i * widthOnTile), (j * heigthOnTile), 1, true));
			}	
			if (mGrid[j][i] == 7){
				totalAmountOfGrass++;
				mObjects.push_back(new Grass(i, j, (i * widthOnTile), (j * heigthOnTile)));
				//mNpcs.push_back(new CharPatrol(i, j, (i * widthOnTile), (j * heigthOnTile), &patrolPath));
			}
		}
	}
}

/*This code looks a ton better with helper functions movePlayer(int dir)
and moveNpc(int dir, int atPos) for each individual step.*/
void Map1::takeTurn(int dir){
	/*get the intVector that lists all of the individual 1-tile moves*/
	intVector meepMove = mPlayer->move(dir);
	/*go through the vector and move 1 step int*/
	for (intVector::size_type i = 0; i < meepMove.size(); i++){
		bool moved=movePlayer(meepMove.at(i));
		if (!moved){
			mPlayer->collide(meepMove, i);
			break;
		}
	}
	/*Do this for every NPC in the vector*/
	for (NpcVector::size_type i = 0; i < mNpcs.size(); i++){
		/*get their movement vector*/
		intVector npcMove = mNpcs.at(i)->move();
		bool breakMove = false;
		/*For every int in the vector, do the following*/
		for (intVector::size_type j = 0; j < npcMove.size(); j++){
			/*0 means end of movement. Needed for patrols. 
			Breakmove means that the entire movement for this character
			is over for the turn*/
			if (npcMove.at(j) == 0 || breakMove){
				breakMove = false;
				break;
			}
			/*the movemen functions returns a bool. True if they moved, 
			false in case of collision*/
			bool moved = moveNpc(npcMove.at(j), i);
			/*if the NPC collided: do the following*/
			if (!moved){
				/*get a new series of moves to attempt*/
				intVector tryMove;
				tryMove = mNpcs.at(i)->collide(npcMove, j);
				/*try out the new list of steps*/
				for (intVector::size_type k = 0; k < tryMove.size(); k++){
					/*again, break if 0, breakMove is made true so that
					the entire turn will end for the current character
					if there is no movement after collision*/
					if (tryMove.at(k) == 0){
						breakMove = true;
						break;
					}
					/*check every move. If one of them works, return to standard
					movement pattern*/
					bool retryMoved = moveNpc(tryMove.at(k), i);
					if (retryMoved){
						break;
					}
				}

				break;
			}
		}
	}
	mTurnCount++;
	cout << "That was turn " << mTurnCount << "." << endl;
	if (mTurnCount >= 50){
		cout << "GAME OVER" << endl;
	}
}

bool Map1::movePlayer(int dir){
		/*need temporary values to alter to avoid certain issues*/
		int tempX = mPlayer->getX();
		int tempY = mPlayer->getY();
		float tempPosX = 0, tempPosY = 0;
		/*move according to the int*/
	switch (dir){
		case 8:
			tempY--;
		tempPosY += -52;
			break;
		case 9:
			tempY--;
			tempX++;
			tempPosY += -52;
			tempPosX += 64;
			break;
		case 6:
			tempX++;
			tempPosX += 64;
			break;
		case 3:
			tempX++;
			tempY++;
			tempPosY += 52;
			tempPosX += 64;
			break;
		case 2:
			tempY++;
			tempPosY += 52;
			break;
		case 1:
			tempY++;
			tempX--;
			tempPosY += 52;
			tempPosX += -64;
			break;
		case 4:
			tempX--;
			tempPosX += -64;
			break;
		case 7:
			tempX--;
			tempY--;
			tempPosY += -52;
			tempPosX += -64;
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
		cout << "Meep trying to move to: " << tempX << ", " << tempY << " which has value " << mGrid[tempY][tempX] << endl;
		if (mGrid[tempY][tempX] >= 2.0f && mGrid[tempY][tempX] < 3.0f){
			//mPlayField.at(mEepY).at(mEepX) = mEep->getLast();
			mGrid[mPlayer->getY()][mPlayer->getX()] = mPlayer->getLast();
			//mEep->setLast(mPlayField.at(tempY).at(tempX));
			mPlayer->setLast(mGrid[tempY][tempX]);
			//mPlayField.at(tempY).at(tempX) = mEep->getType();
			mGrid[tempY][tempX] = mPlayer->getType();
			mPlayer->updPos(tempPosX, tempPosY);

			mPlayer->setX(tempX);
			mPlayer->setY(tempY);
			//mEepX = tempX;
			//mEepY = tempY;


			//Loopar igenom alla objekt och kollar funktionen "getCut" på det objektet som spelaren befinner sig på, den blir true när gräset är klippt.
			//Variabeln cutGrass plussas på varje gång ett gräs klipps
			for (ObjectsVector::size_type i = 0; i < mObjects.size(); i++){
				if (mObjects[i]->getArrayX() == tempX && mObjects[i]->getArrayY() == tempY){
					if (!mObjects[i]->getCut()){
						mObjects[i]->setCut();
						cutGrass++;
					}
				}
			}
			cout << endl << "Meep has mowed: " << cutGrass << " grasstiles out of: " << totalAmountOfGrass << " total." << endl;

			cout << "Meep moved to: " << tempX << ", " << tempY << " which now has value " << mGrid[tempY][tempX] << endl;
		return true;
		}
		else {
			cout << "Meep tried: " << tempX << ", " << tempY << " which has value " << mGrid[tempY][tempX] << endl;

		return false;
	}
}

bool Map1::moveNpc(int dir, int atPos){
	int tempX = mNpcs.at(atPos)->getX();
	int tempY = mNpcs.at(atPos)->getY();
	float tempPosX = 0;
	float tempPosY = 0;
	switch (dir){
	case 8:
		tempY--;
		tempPosY += -52;
		break;
	case 9:
		tempY--;
		tempX++;
		tempPosY += -52;
		tempPosX += 64;
		break;
	case 6:
		tempX++;
		tempPosX += 64;
		break;
	case 3:
		tempX++;
		tempY++;
		tempPosY += 52;
		tempPosX += 64;
		break;
	case 2:
		tempY++;
		tempPosY += 52;
		break;
	case 1:
		tempY++;
		tempX--;
		tempPosY += 52;
		tempPosX += -64;
		break;
	case 4:
		tempX--;
		tempPosX += -64;
		break;
	case 7:
		tempX--;
		tempY--;
		tempPosY += -52;
		tempPosX += -64;
			break;
		}

	cout << "Cat trying to move to: " << tempX << ", " << tempY << " which has value " << mGrid[tempY][tempX] << endl;
	if (mGrid[tempY][tempX] >= 2.0f && mGrid[tempY][tempX] < 3.0f){
		mGrid[mNpcs.at(atPos)->getY()][mNpcs.at(atPos)->getX()] = mNpcs.at(atPos)->getLast();
		mNpcs.at(atPos)->setLast(mGrid[tempY][tempX]);
		mGrid[tempY][tempX] = mNpcs.at(atPos)->getType();
		mNpcs.at(atPos)->updPos(tempPosX, tempPosY);

		mNpcs.at(atPos)->setX(tempX);
		mNpcs.at(atPos)->setY(tempY);
		cout << "Cat moved to: " << tempX << ", " << tempY << " which now has value " << mGrid[tempY][tempX] << endl;
		return true;
	}
	else {
		cout << "Cat tried: " << tempX << ", " << tempY << " which has value " << mGrid[tempY][tempX] << endl;
		return false;
	}

}

void Map1::getArraySize(){
	//ofstream file(mSavefile);
	ifstream file(mSavefile);
	//for (int i = 0; i < 2; i++){
		file >> mWidth >> mHeigth;
	//}
}

//Funktion för att returnera objekten
vector<StaticObjects*> Map1::getObjects(){
	return mObjects;
}
Player* Map1::getPlayer(){
	return mPlayer;
}
vector<Character*> Map1::getNpcs(){
	return mNpcs;
}
vector<StaticObjects*> Map1::getLongObjects(){
	return mLongObjects;
}