#include "CharRand.h"
#include <cstdlib>

using namespace std;

sf::Texture textureCat;
sf::Image imageCat;
static const string filename = "Resource Files/Sprites/cat.png";

CharRand::CharRand(int arrX, int arrY, float posX, float posY, int moveLength, bool lockDir) :
	mArrayX(arrX),
	mArrayY(arrY),
	mPosX(posX),
	mPosY(posY),
	mSpeed(moveLength),
	mDirLock(lockDir){
	mCharSprite.setPosition(posX, posY);
	/*I am as of now unsure how to handle values like 
	4.1, 4.2, etc for other random NPCs. Will update code as it becomes 
	relevant*/
	mType = 6.0f;
	//d�ligt tilf�llig l�sning. Fixa snart.
	mLast = 2;
}

CharRand::~CharRand(){
}

float CharRand::getPosX(){
	return mPosX;
}

float CharRand::getPosY(){
	return mPosY;
}

intVector CharRand::move(){
	intVector movement;
	if (mDirLock){
		int dir = rand()%9+1;
		for (int i = 0; i < mSpeed; i++){
			movement.push_back(dir);
		}
	}
	else {
		for (int i = 0; i < mSpeed; i++){
			movement.push_back(rand()%9+1);
		}
	}
	return movement;
}

/*This function is oddly constructed, though I didn't know a better way
to have it cycle through different moves without randomizing each move in
the map class. When NPC's collide the takeTurn function in Map will 
go into a loop and try to move them according to the intVector that was
returned. Once it has successfully taken a step, reaches the end of the
vector, or reaches a 0, it will stop trying and end the movement
for the turn for that NPC.*/
intVector CharRand::collide(intVector moves, int atPos){
	intVector movement;
	int m = moves.at(atPos);
	for (int i = 0; i < 7; i++){
		m++;
		if (m == 5){
			m++;
		}
		if (m>9
			){
			m = (m % 9);
		}
		movement.push_back(m);
	}
	return movement;
}

int CharRand::getX(){
	return mArrayX;
}

int CharRand::getY(){
	return mArrayY;
}

void CharRand::setX(int x){
	mArrayX = x;
}

void CharRand::setY(int y){
	mArrayY = y;
}

void CharRand::setLast(float l){
	mLast = l;
}

float CharRand::getLast(){
	return mLast;
}

float CharRand::getType(){
	return mType;
}

void CharRand::updPos(float x, float y){
	mPosX += x;
	mPosY += y;
	mCharSprite.setPosition(mPosX, mPosY);
}

void CharRand::render(){
	mCharSprite.setTexture(textureCat);
}

sf::Sprite CharRand::getSprite(){
	return mCharSprite;
}

void CharRand::initialize(){
	imageCat.loadFromFile(filename);
	imageCat.createMaskFromColor(sf::Color::White);
	textureCat.loadFromImage(imageCat);
}

void CharRand::finalize(){
	textureCat.~Texture();
}