#include "CharPatrol.h"

using namespace std;

sf::Texture textureGuard;
sf::Image imageGuard;
static const string filename = "deputy.png";

CharPatrol::CharPatrol(int arrX, int arrY, float posX, float posY, int *moves[50][10]): 
	retryPath{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	mArrayX(arrX),
	mArrayY(arrY),
	mPosX(posX),
	mPosY(posY)
	{
	mCharSprite.setPosition(posX, posY);
	mTurnNo = -1;
	for (int i = 0; i < 50; i++){
		for (int j = 0; j < 10; j++){
			path[i][j] = moves[i][j];
		}
	}
}

CharPatrol::~CharPatrol(){
	delete path;
}

float CharPatrol::getPosX(){
	return mPosX;
}

float CharPatrol::getPosY(){
	return mPosY;
}

intVector CharPatrol::move(){
	intVector curMove;
	if (retryPath[0] <= 0){
		mTurnNo++;
		for (int i = 0; i < 10; i++){
			if (*path[mTurnNo][i] <= 0){
				break;
			}
			else {
				curMove.push_back(*path[mTurnNo][i]);
			}
		}
	}
	else {
		for (int i = 0; i < 10; i++){
			if (retryPath[i] <= 0){
				break;
			}
			else{ 
				curMove.push_back(retryPath[i]);
			}
		}
		for (int i = 0; i < 10; i++){
			retryPath[i] = 0;
		}
	}
	return curMove;
}

intVector CharPatrol::collide(intVector moves, int atPos){
	int j = 0;
	for (intVector::size_type i = atPos; i < moves.size(); i++){
		retryPath[j] = moves.at(i);
	}
	intVector col;
	col.push_back(0);
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
}

float CharPatrol::getLast(){
	return mLast;
}

float CharPatrol::getType(){
	return mType;
}

void CharPatrol::updPos(float x, float y){
	mPosX += x;
	mPosY += y;
	mCharSprite.setPosition(mPosX, mPosY);
}

void CharPatrol::render(){
	mCharSprite.setTexture(textureGuard);
}

sf::Sprite CharPatrol::getSprite(){
	return mCharSprite;
}

void CharPatrol::initialize(){
	imageGuard.loadFromFile(filename);
	imageGuard.createMaskFromColor(sf::Color::White);
	textureGuard.loadFromImage(imageGuard);
}

void CharPatrol::finalize(){
	textureGuard.~Texture();
}