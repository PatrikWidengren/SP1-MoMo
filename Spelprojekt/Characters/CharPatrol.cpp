#include "CharPatrol.h"
#include <iostream>

using namespace std;

sf::Texture textureGuard;
sf::Image imageGuard;
static const string filename = "Resource Files/Sprites/deputy.png";

CharPatrol::CharPatrol(int arrX, int arrY, int **moves/*, int turnCount, int moveCount*/): 
	
	mArrayX(arrX),
	mArrayY(arrY),
	mStartPos{ arrX, arrY },
	mBaseType(7.0f),
	mOrigLast(2.0f)
	{

	//Remove these when moveCount and turnCount is in constructor
	int moveCount = 10;
	int turnCount = 50;

	mMoveCount = moveCount;
	mTurnCount = turnCount;

	//initialize retryPath with all zeroes.
	retryPath = new int[10];
	for (int i = 0; i < moveCount; i++){
		retryPath[i] = 0;
	}
	mTurnNo = -1;
	//fill up path with the move array

	// Not needed
	/*path = new int*[mTurnCount];
	for (int i = 0; i < mTurnCount; i++) {
		path[i] = new int[mMoveCount];
		for (int j = 0; j < mMoveCount; j++) {
			path[i][j] = 0;
		}
	}

	for (int i = 0; i < mTurnCount; i++){
		for (int j = 0; j < mMoveCount; j++) {
			path[i][j] = moves[i][j];
		}
	}*/

	path = moves;
	//I assume guard is 7
	mType = 7.0f;
	//temporary fix. update asap.
	mLast = 2.0f;
	render();
}

CharPatrol::~CharPatrol(){
	delete[] path;
	delete[] retryPath;
}

void CharPatrol::reset() {
	mTurnNo = -1;
	mArrayX = mStartPos[0];
	mArrayY = mStartPos[1];
	mLast = mOrigLast;
}

intVector CharPatrol::move(){
	intVector curMove;
	//Step 1: Make sure no retries are waiting
	//int test = 0;
	if (retryPath[0] <= 0){
		//If no retry waiting, take the next turn's movement
		mTurnNo++;
		//If the first move this turn is 0, end of patrol is reached. Restart patrol from 0
		if (path[mTurnNo][0]==0){
			mTurnNo = 0;
		}
		for (int i = 0; i < mMoveCount; i++){
			//add all the steps. Cancel if a move has val 0
			if (path[mTurnNo][i] <= 0 || path[mTurnNo][0] == 5){
				break;
			}
			else {
				//test += path[mTurnNo][i];
				//test *= mMoveCount;
				curMove.push_back(path[mTurnNo][i]);
			}
		}
		//cout << "Trying path: " << test << endl;
	}
	//if a retry is wating...
	else {
		for (int i = 0; i < mMoveCount; i++){
			//add the entire retryPath to the current turn's move
			//end prematurely if the movement of a turn is 0;
			if (retryPath[i] <= 0){
				break;
			}
			else{ 
				//test += retryPath[i];
				//test *= mMoveCount;
				curMove.push_back(retryPath[i]);
			}
		}
		//clear the whole retryPath
		for (int i = 0; i < mMoveCount; i++){
			retryPath[i] = 0;
		}
		//cout << "Retrying path: " << test << endl;
	}
	//return the intVector of steps
	return curMove;
}

intVector CharPatrol::collide(intVector moves, int atPos){
	int j = 0;
	//int test = 0;
	for (intVector::size_type i = atPos; i < moves.size(); i++){
		//Fill up the retryPath array with all the remaining moves
		retryPath[j] = moves.at(i);
		//test += moves.at(i);
		//test *= mMoveCount;
		j++;
	}
	//cout << "Saving " << test << "for next turn" << endl;
	intVector col;
	col.push_back(0);
	//return a 0 to break the movement for the turn
	return col;
}



int CharPatrol::getX(){
	return mArrayX;
}

int CharPatrol::getY(){
	return mArrayY;
}

void CharPatrol::setX(int x){
	mArrayX = x;
}

void CharPatrol::setY(int y){
	mArrayY = y;
}

void CharPatrol::setLast(float l){
	mLast = l;
	mType = mBaseType + (mLast - 2);
}

float CharPatrol::getLast(){
	return mLast;
}

float CharPatrol::getType(){
	return mType;
}

bool CharPatrol::getCollide(){
	return true;
}

void CharPatrol::render(){
	mCharSprite.setTexture(textureGuard);
}

sf::Sprite* CharPatrol::getSprite(){
	return &mCharSprite;
}

sf::Sprite CharPatrol::getDrawSprite(){
	return mCharSprite;
}

void CharPatrol::initialize(){
	imageGuard.loadFromFile(filename);
	imageGuard.createMaskFromColor(sf::Color::White);
	textureGuard.loadFromImage(imageGuard);
}

void CharPatrol::finalize(){
	textureGuard.~Texture();
	imageGuard.~Image();
}