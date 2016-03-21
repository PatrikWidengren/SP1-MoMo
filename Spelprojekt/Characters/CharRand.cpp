#include "CharRand.h"
#include <cstdlib>

using namespace std;

sf::Texture textureCat;
sf::Image imageCat;
static const string filename = "Resource Files/Sprites/cat.png";
static const string cat_idle = "Resource Files/SpriteSheets/Cat_Black_Idle.png";
static const string cat_walk = "Resource Files/SpriteSheets/Cat_Black_Walk.png";
static const int spriteWidth = 64;
static const int spriteHeight = 64;

CharRand::CharRand(int arrX, int arrY, int moveLength, bool lockDir) :
	mArrayX(arrX),
	mArrayY(arrY),
	mLastX(arrX),
	mLastY(arrY),
	mStartPos{ arrX, arrY },
	mSpeed(moveLength),
	mDirLock(lockDir),
	mBaseType(6.0f),
	mOrigLast(2.0f){
	/*I am as of now unsure how to handle values like 
	4.1, 4.2, etc for other random NPCs. Will update code as it becomes 
	relevant*/
	mType = 6.0f;
	//dåligt tilfällig lösning. Fixa snart.
	mLast = 2.0f;


	mTextureSheet_catIdle->loadFromFile(cat_idle);
	mCatIdleSheet->setTexture(*mTextureSheet_catIdle);
	mTextureSheet_catWalk->loadFromFile(cat_walk);
	mCatWalkSheet->setTexture(*mTextureSheet_catWalk);

	for (int j = 0; j < 8; j++) {
		thor::FrameAnimation frame;
		for (int i = 0; i < 8; i++) {
			mRect = new sf::IntRect(sf::Vector2i(0 + spriteWidth * i, spriteHeight * j), sf::Vector2i(spriteWidth, spriteHeight));
			frame.addFrame(0.4f, *mRect);
		}
		std::ostringstream tempName;
		tempName << "idle" << j + 1;
		catAnimator->addAnimation(tempName.str(), frame, sf::seconds(1.1f));
	}

	for (int j = 0; j < 8; j++) {
		thor::FrameAnimation frame;
		for (int i = 0; i < 8; i++) {
			mRect = new sf::IntRect(sf::Vector2i(0 + spriteWidth * i, spriteHeight * j), sf::Vector2i(spriteWidth, spriteHeight));
			frame.addFrame(0.4f, *mRect);
		}
		std::ostringstream tempName;
		tempName << "walk" << j + 1;
		catAnimator->addAnimation(tempName.str(), frame, sf::seconds(1.1f));
	}
	if (walking) {
		catAnimator->playAnimation("walk7", true);
	}
	else {
		catAnimator->playAnimation("idle7", true);
	}
}

CharRand::~CharRand()
{
	delete mTextureSheet_catIdle;
	delete mTextureSheet_catWalk;

	delete mCatIdleSheet;
	delete mCatWalkSheet;

}
void CharRand::changeAnimation(int nr) {
	if (!walking) {
		if (nr == 1) {
			catAnimator->playAnimation("idle3", true);
		}
		if (nr == 2) {
			catAnimator->playAnimation("idle1", true);
		}
		if (nr == 3) {
			catAnimator->playAnimation("idle7", true);
		}
		if (nr == 4) {
			catAnimator->playAnimation("idle3", true);
		}
		if (nr == 6) {
			catAnimator->playAnimation("idle7", true);
		}
		if (nr == 7) {
			catAnimator->playAnimation("idle3", true);
		}
		if (nr == 8) {
			catAnimator->playAnimation("idle5", true);
		}
		if (nr == 9) {
			catAnimator->playAnimation("idle7", true);
		}
	}
	else {
		if (nr == 1) {
			catAnimator->playAnimation("walk2", true);
		}
		if (nr == 2) {
			catAnimator->playAnimation("walk1", true);
		}
		if (nr == 3) {
			catAnimator->playAnimation("walk8", true);
		}
		if (nr == 4) {
			catAnimator->playAnimation("walk3", true);
		}
		if (nr == 6) {
			catAnimator->playAnimation("walk7", true);
		}
		if (nr == 7) {
			catAnimator->playAnimation("walk4", true);
		}
		if (nr == 8) {
			catAnimator->playAnimation("walk5", true);
		}
		if (nr == 9) {
			catAnimator->playAnimation("walk6", true);
		}
	}
}
void CharRand::playAnimation() {
	catAnimator->update(clock.restart());
	if (!walking) {
		catAnimator->animate(*mCatIdleSheet);
	}
	if (walking) {
		catAnimator->animate(*mCatWalkSheet);
	}
}
void CharRand::reset() {
	mArrayX = mStartPos[0];
	mArrayY = mStartPos[1];
	mLast = mOrigLast;
}

intVector CharRand::move(){
	intVector movement;
	if (mDirLock){
		int dir = rand()%9+1;
		for (int i = 0; i < mSpeed; i++){
			changeAnimation(dir);
			movement.push_back(dir);
		}
	}
	else {
		for (int i = 0; i < mSpeed; i++){
			int dir = rand() % 9 + 1;
			if (i == mSpeed-1)
				changeAnimation(dir);
			movement.push_back(dir);
		}
	}
	mMoveTime = 1.0f / movement.size();
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
		if (m>9){
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

int CharRand::getLastX() {
	return mLastX;
}

int CharRand::getLastY() {
	return mLastY;
}

void CharRand::setX(int x){
	mLastX = mArrayX;
	mArrayX = x;
}

void CharRand::setY(int y){
	mLastY = mArrayY;
	mArrayY = y;
}

void CharRand::setLast(float l){
	mLast = l;
	mType = mBaseType + (mLast - 2);
}

float CharRand::getLast(){
	return mLast;
}

float CharRand::getType(){
	return mType;
}

bool CharRand::getCollide(){
	return false;
}
sf::Sprite* CharRand::getSpriteSheet(){
	if (!walking) {
		return mCatIdleSheet;
	}
	if (walking) {
		return mCatWalkSheet;
	}
}
void CharRand::initialize(){
}

void CharRand::finalize(){
	textureCat.~Texture();
	imageCat.~Image();
}
void CharRand::scale(sf::RenderWindow &window) {
	float scaleX = (float)window.getSize().x / 1920;
	float scaleY = (float)window.getSize().y / 1080;

	mCatIdleSheet->setScale(sf::Vector2f(scaleX, scaleY));
	mCatWalkSheet->setScale(sf::Vector2f(scaleX, scaleY));
}
float CharRand::getMoveTime() {
	return mMoveTime;
}

void CharRand::setWalking(bool walk) {
	walking = walk;
}

bool CharRand::getWalking() {
	return walking;
}
