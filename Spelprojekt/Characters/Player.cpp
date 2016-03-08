#include "Player.h"
#include <iostream>

using namespace std;

static int spriteWidth = 256;
static int spriteHeight = 256;
static const string filename = "Resource Files/Sprites/meep02.png";
static const string meep_idle = "Resource Files/SpriteSheets/Meep_Idle_Pushmower1.png";
static const string meep_walk = "Resource Files/SpriteSheets/Meep_Walk_Pushmower1.png";

Player::Player(Mower *m, Shears *c/*, float posX, float posY*/) :
	mLawnMower(m), mAntiLeakMower(m), mHedgeTool(c), 
	mAntiLeakHedgeTool(c), mBaseType(5.0f){
	walking = false;
	//mPosX = posX;
	//mPosY = posY
	//mPlayerSprite.setPosition(posX, posY);
	mType = 5.1f;
	//Temporär lösning. Bör fixas snarast
	mLast = 2.1f;
	//mPlayerSprite.setTexture(texturePlayer);
	mTextureSheet.loadFromFile(meep_idle);
	mSpriteIdleSheet.setTexture(mTextureSheet);

	for (int j = 0; j < 8; j++) {
		thor::FrameAnimation frame;
		for (int i = 0; i < 7; i++) {
			mRect = new sf::IntRect(sf::Vector2i(0 + spriteWidth * i, spriteHeight * j), sf::Vector2i(spriteWidth, spriteHeight));
			frame.addFrame(0.4f, *mRect);
		}
		std::ostringstream tempName;
		tempName << "idle" << j + 1;
		animatorMeep.addAnimation(tempName.str(), frame, sf::seconds(1.1f));
	}
	animatorMeep.playAnimation("idle3", true);

	mTextureSheet.loadFromFile(meep_walk);
	mSpriteWalkSheet.setTexture(mTextureSheet);

	for (int j = 0; j < 8; j++) {
		thor::FrameAnimation frame;
		for (int i = 0; i < 8; i++) {
			mRect = new sf::IntRect(sf::Vector2i(0 + spriteWidth * i, spriteHeight * j), sf::Vector2i(spriteWidth, spriteHeight));
			frame.addFrame(0.4f, *mRect);
		}
		std::ostringstream tempName;
		tempName << "walk" << j + 1;
		animatorMeep.addAnimation(tempName.str(), frame, sf::seconds(1.1f));
	}
}

/*void Player::updPos(float x, float y){
	mPosX += x;
	mPosY += y;
	mPlayerSprite.setPosition(mPosX, mPosY);
}*/

Player::~Player(){
	//delete mLawnMower;
	//delete mHedgeTool;
	delete mAntiLeakHedgeTool;
	delete mAntiLeakMower;
}
intVector Player::move(int dir){
	intVector movement = mLawnMower->getMove(dir);
	mMoveTime = 1.0 / movement.size();
	return movement;
}

void Player::collide(intVector moves, int atPos){
	int dmg = 0;
	for (intVector::size_type i = atPos; i < moves.size(); i++){
		dmg++;
	}
	mLawnMower->setToMin(dmg);
}

void Player::collideWith(int dmg){
	mLawnMower->setToMin(dmg);
}

/*float Player::getPosX(){
	return mPosX;
}
float Player::getPosY(){
	return mPosY;
}
void Player::render(){
	mPlayerSprite.setTexture(texturePlayer);
}*/
int Player::getX(){
	return mArrayX;
}

int Player::getY(){
	return mArrayY;
}

int Player::getLastX() {
	return mLastX;
}

int Player::getLastY() {
	return mLastY;
}

void Player::setX(int x){
	mLastX = mArrayX;
	mArrayX = x;
}

void Player::setY(int y){
	mLastY = mArrayY;
	mArrayY = y;
}

float Player::getType(){
	return mType;
}

float Player::getLast(){
	return mLast;
}

bool Player::getMowerEquipped(){
	return mMowerEquipped;
}

bool Player::getFunctioning(){
	if (mMowerEquipped){
		return mLawnMower->getFunctioning();
	}
	else return false;
}

void Player::swapEquipped(){
	cout << "Equipment changed from ";
	if (mMowerEquipped){
		cout << "Lawnmower" << endl;
	}
	else {
		cout << "Hedge cutter" << endl;
	}
	mMowerEquipped = !mMowerEquipped;
	cout << "Equipment changed to ";
	if (mMowerEquipped){
		cout << "Lawnmower" << endl;
	}
	else {
		cout << "Hedge cutter" << endl;
	}
}

string Player::getMower(){
	return mLawnMower->getStats();
}

string Player::getShears(){
	return mHedgeTool->getStats();
}

void Player::setMower(Mower *m){
	mLawnMower = m;
}

void Player::setHedgeTool(Shears *s){
	mHedgeTool = s;
}

cutVector Player::getCuts(){
	return mHedgeTool->getCuts(mArrayX, mArrayY);
	//return mHedgeTool->getCuts(0, 0);
}

void Player::setLast(float l){
	mLast = l;
	mType = mBaseType + (mLast - 2);
}
/*void Player::update(){

}*/
void Player::changeAnimation(std::string name) {
	animatorMeep.playAnimation(name, true);
}

void Player::playPlayer() {
	animatorMeep.update(clock.restart());
	if (walking) {
		animatorMeep.animate(mSpriteWalkSheet);
	}
	else {
		animatorMeep.animate(mSpriteIdleSheet);
	}
}

float Player::getMoveTime() {
	return mMoveTime;
}
sf::Sprite* Player::getSpriteSheet() {
	if (walking) {
		return &mSpriteWalkSheet;
	}
	else {
		return &mSpriteIdleSheet;
	}
}