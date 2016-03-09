#include "CharPatrol.h"
#include <iostream>

using namespace std;

sf::Texture textureGuard;
sf::Image imageGuard;
static const string filename = "Resource Files/Sprites/deputy.png";
static const string dog_idle = "Resource Files/SpriteSheets/DOG_IDLE.png";
static const string dog_walk = "Resource Files/SpriteSheets/Dog_Walk.png";
static const int spriteWidth = 64;
static const int spriteHeight = 64;

CharPatrol::CharPatrol(int arrX, int arrY, int **moves/*, int turnCount, int moveCount*/): 
	
	mArrayX(arrX),
	mArrayY(arrY),
	mLastX(arrX),
	mLastY(arrY),
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

	path = moves;
	//I assume guard is 7
	mType = 7.0f;
	//temporary fix. update asap.
	mLast = 2.0f;

	mTextureSheet_dogIdle.loadFromFile(dog_idle);
	mDogIdleSheet.setTexture(mTextureSheet_dogIdle);

	mTextureSheet_dogWalk.loadFromFile(dog_walk);
	mDogWalkSheet.setTexture(mTextureSheet_dogWalk);

	for (int j = 0; j < 8; j++) {
		thor::FrameAnimation frame;
		for (int i = 0; i < 8; i++) {
			mRect = new sf::IntRect(sf::Vector2i(0 + spriteWidth * i, spriteHeight * j), sf::Vector2i(spriteWidth, spriteHeight));
			frame.addFrame(0.4f, *mRect);
		}
		std::ostringstream tempName;
		tempName << "animation" << j + 1;
		dogAnimator.addAnimation(tempName.str(), frame, sf::seconds(1.1f));
	}
	dogAnimator.playAnimation("animation7", true);
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

				changeAnimation(path[mTurnNo][i]);
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
	//return a 0 to break the movement for the turn
	col.push_back(0);
	mMoveTime = 1.0f / col.size();
	return col;
}

int CharPatrol::getX(){
	return mArrayX;
}

int CharPatrol::getY(){
	return mArrayY;
}

int CharPatrol::getLastX() {
	return mLastX;
}

int CharPatrol::getLastY() {
	return mLastY;
}

void CharPatrol::setX(int x){
	mLastX = mArrayX;
	mArrayX = x;
}

void CharPatrol::setY(int y){
	mLastY = mArrayY;
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
void CharPatrol::playAnimation() {
	dogAnimator.update(clock.restart());
	if (!walking) {
		dogAnimator.animate(mDogIdleSheet);
	}
	else {
		dogAnimator.animate(mDogWalkSheet);
	}
}
void CharPatrol::changeAnimation(int nr) {
	if (nr == 1) {
		dogAnimator.playAnimation("animation2", true);
	}
	if (nr == 2) {
		dogAnimator.playAnimation("animation1", true);
	}
	if (nr == 3) {
		dogAnimator.playAnimation("animation8", true);
	}
	if (nr == 4) {
		dogAnimator.playAnimation("animation3", true);
	}
	if (nr == 6) {
		dogAnimator.playAnimation("animation7", true);
	}
	if (nr == 7) {
		dogAnimator.playAnimation("animation4", true);
	}
	if (nr == 8) {
		dogAnimator.playAnimation("animation5", true);
	}
	if (nr == 9) {
		dogAnimator.playAnimation("animation6", true);
	}
}
sf::Sprite* CharPatrol::getSpriteSheet() {
	if (!walking) {
		return &mDogIdleSheet;
	}
	else {
		return &mDogWalkSheet;
	}
}

void CharPatrol::initialize(){
	//imageGuard.loadFromFile(filename);
	//imageGuard.createMaskFromColor(sf::Color::White);
	//textureGuard.loadFromImage(imageGuard);
}

void CharPatrol::finalize(){
	textureGuard.~Texture();
	imageGuard.~Image();
}

float CharPatrol::getMoveTime() {
	return mMoveTime;
}
