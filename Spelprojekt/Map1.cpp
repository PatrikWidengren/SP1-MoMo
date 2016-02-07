#include "Map1.h"
#include <iostream>

using namespace std;

static float widthOnTile = 64.0f;
static float heigthOnTile = 52.0f;
static int widthTile = 64;
static int heigthTile = 52;

Map1::Map1(string savefile){
	mSavefile = savefile;
	Stone::initialize();
	Grass::initialize();
	Fence::initialize();
	Player::initialize();
	CharRand::initialize();
}
Map1::~Map1(){
	Stone::finalize();
	Grass::finalize();
	Fence::finalize();
	Player::finalize();
	CharRand::finalize();
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
//Loopar igenom array och spawnar alla objekt
void Map1::spawnObjects(){
	mGrid = createGrid(mWidth, mHeigth);
	for (int i = 0; i < mWidth; i++){
		for (int j = 0; j < mHeigth; j++){
			if (mGrid[j][i] == 1){
				mObjects.push_back(new Grass((i * widthOnTile), (j * heigthOnTile)));

				mObjects.push_back(new Fence((i * widthOnTile), (j * heigthOnTile), 1));
			}
			if (mGrid[j][i] == 2){
				mObjects.push_back(new Grass((i * widthOnTile), (j * heigthOnTile)));
			}
			if (mGrid[j][i] == 5){
				mObjects.push_back(new Grass((i * widthOnTile), (j * heigthOnTile)));
				mPlayer = new Player(i, j, new LawnMower(), (i * widthOnTile), (j * heigthOnTile));
				//mObjects.push_back(new Player((i * widthOnTile), (j * heigthOnTile), 1));
			}
			if (mGrid[j][i] == 6){
				mObjects.push_back(new Grass((i * widthOnTile), (j * heigthOnTile)));
				mNpcs.push_back(new CharRand(i, j, (i * widthOnTile), (j * heigthOnTile), 1, true));
			}
		}
	}
}
void Map1::takeTurn(int dir){
	/*get the intVector that lists all of the individual 1-tile moves*/
	intVector meepMove = mPlayer->move(dir);
	/*go through the vector and move 1 step int*/
	for (intVector::size_type i = 0; i < meepMove.size(); i++){
		/*need temporary values to alter to avoid certain issues*/
		int tempX = mPlayer->getX();
		int tempY = mPlayer->getY();
		float tempPosX = 0, tempPosY = 0;
		/*move according to the int*/
		switch (meepMove.at(i)){
		case 8:
			tempY--;
			tempPosY+=-52;
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
			cout << "Meep moved to: " << tempX << ", " << tempY << " which now has value " << mGrid[tempY][tempX] << endl;
		}
		else {
			mPlayer->collide(meepMove, i);
			cout << "Meep tried: " << tempX << ", " << tempY << " which has value " << mGrid[tempY][tempX] << endl;
			break;
		}

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