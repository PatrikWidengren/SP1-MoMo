#include "Player.h"
#include <iostream>

using namespace std;

static int spriteWidth = 256;
static int spriteHeight = 256;
static const string filename = "Resource Files/Sprites/meep02.png";
static const string meep_idle1 = "Resource Files/SpriteSheets/Meep_Idle_Pushmower1.png";
static const string meep_walk1 = "Resource Files/SpriteSheets/Meep_Walk_Pushmower1.png";
static const string meep_idle2 = "Resource Files/SpriteSheets/Meep_Idle_Pushmower2.png";
static const string meep_walk2 = "Resource Files/SpriteSheets/Meep_Walk_Pushmower2.png";
static const string meep_idle3 = "Resource Files/SpriteSheets/Meep_Idle_Pushmower3.png";
static const string meep_walk3 = "Resource Files/SpriteSheets/Meep_Walk_Pushmower3.png";
static const string meep_idle4 = "Resource Files/SpriteSheets/Meep_Idle_Mower1.png";
static const string meep_walk4 = "Resource Files/SpriteSheets/Meep_Walk_Mower1.png"; 
static const string meep_idle5 = "Resource Files/SpriteSheets/Meep_Idle_Mower2.png";
static const string meep_walk5 = "Resource Files/SpriteSheets/Meep_Walk_Mower2.png";
static const string meep_idle_cutter = "Resource Files/SpriteSheets/Meep_Idle_Hedgecutter.png";
static const string meep_walk_cutter = "Resource Files/SpriteSheets/Meep_Walk_Hedgecutter.png";





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

	mTextureIdleSheet1->loadFromFile(meep_idle1);
	mTextureIdleSheet2->loadFromFile(meep_idle2);
	mTextureIdleSheet3->loadFromFile(meep_idle3);
	mTextureIdleSheet4->loadFromFile(meep_idle4);
	mTextureIdleSheet5->loadFromFile(meep_idle5);
	mTextureIdleSheetCutter1->loadFromFile(meep_idle_cutter);
	
	mSpriteIdleSheet->setTexture(*mTextureIdleSheet1);
	mdopies = 100;

	for (int j = 0; j < 8; j++) {
		thor::FrameAnimation frame;
		for (int i = 0; i < 7; i++) {
			mRect = new sf::IntRect(sf::Vector2i(0 + spriteWidth * i, spriteHeight * j), sf::Vector2i(spriteWidth, spriteHeight));
			frame.addFrame(0.4f, *mRect);
		}
		std::ostringstream tempName;
		tempName << "idle" << j + 1;
		animatorMeep->addAnimation(tempName.str(), frame, sf::seconds(0.8f));
	}

	mTextureWalkSheet1->loadFromFile(meep_walk1);
	mTextureWalkSheet2->loadFromFile(meep_walk2);
	mTextureWalkSheet3->loadFromFile(meep_walk3);
	mTextureWalkSheet4->loadFromFile(meep_walk4);
	mTextureWalkSheet5->loadFromFile(meep_walk5);
	mTextureWalkSheetCutter1->loadFromFile(meep_walk_cutter);

	mSpriteWalkSheet->setTexture(*mTextureWalkSheet1);

	for (int j = 0; j < 8; j++) {
		thor::FrameAnimation frame;
		for (int i = 0; i < 8; i++) {
			mRect = new sf::IntRect(sf::Vector2i(0 + spriteWidth * i, spriteHeight * j), sf::Vector2i(spriteWidth, spriteHeight));
			frame.addFrame(0.4f, *mRect);
		}
		std::ostringstream tempName;
		tempName << "walk" << j + 1;
		animatorMeep->addAnimation(tempName.str(), frame, sf::seconds(0.8f));
	}

	animatorMeep->playAnimation("idle3", true);
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

	delete mTextureIdleSheet1;
	delete mTextureWalkSheet1;
	delete mTextureIdleSheet2;
	delete mTextureWalkSheet2;
	delete mTextureIdleSheet3;
	delete mTextureWalkSheet3;
	delete mTextureIdleSheet4;
	delete mTextureWalkSheet4;
	delete mTextureIdleSheet5;
	delete mTextureWalkSheet5;
	delete mTextureIdleSheetCutter1;
	delete mTextureWalkSheetCutter1;

	delete mSpriteIdleSheet;
	delete mSpriteWalkSheet;
}

intVector Player::move(int dir){
	intVector movement = mLawnMower->getMove(dir);
	mMoveTime = 0.8f / movement.size();
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
	if (mMowerEquipped) {
		cout << "Lawnmower" << endl;
		switch (intMower)
		{
		case 0: {
			mSpriteWalkSheet->setTexture(*mTextureWalkSheet1);
			mSpriteIdleSheet->setTexture(*mTextureIdleSheet1);
			break;
		}
		case 1: {
			mSpriteWalkSheet->setTexture(*mTextureWalkSheet2);
			mSpriteIdleSheet->setTexture(*mTextureIdleSheet2);
			break;
		}
		case 2: {
			mSpriteWalkSheet->setTexture(*mTextureWalkSheet3);
			mSpriteIdleSheet->setTexture(*mTextureIdleSheet3);
			break;
		}
		case 3: {
			mSpriteWalkSheet->setTexture(*mTextureWalkSheet4);
			mSpriteIdleSheet->setTexture(*mTextureIdleSheet4);
			break;
		}
		case 4: {
			mSpriteWalkSheet->setTexture(*mTextureWalkSheet5);
			mSpriteIdleSheet->setTexture(*mTextureIdleSheet5);
			break;
		}
		}
	}
	else {
		mSpriteWalkSheet->setTexture(*mTextureWalkSheetCutter1);
		mSpriteIdleSheet->setTexture(*mTextureIdleSheetCutter1);
		cout << "Hedge cutter" << endl;
	}
}

string Player::getMower(){
	return mLawnMower->getStats();
}

string Player::getShears(){
	return mHedgeTool->getStats();
}

void Player::setMower(Mower *m, int i){
	mLawnMower = m;
	intMower = i;
	switch (intMower)
	{
	case 0: {
		mSpriteWalkSheet->setTexture(*mTextureWalkSheet1);
		mSpriteIdleSheet->setTexture(*mTextureIdleSheet1);
		break;
	}
	case 1: {
		mSpriteWalkSheet->setTexture(*mTextureWalkSheet2);
		mSpriteIdleSheet->setTexture(*mTextureIdleSheet2);
		break;
	}
	case 2: {
		mSpriteWalkSheet->setTexture(*mTextureWalkSheet3);
		mSpriteIdleSheet->setTexture(*mTextureIdleSheet3);
		break;
	}
	case 3: {
		mSpriteWalkSheet->setTexture(*mTextureWalkSheet4);
		mSpriteIdleSheet->setTexture(*mTextureIdleSheet4);
		break;
	}
	case 4: {
		mSpriteWalkSheet->setTexture(*mTextureWalkSheet5);
		mSpriteIdleSheet->setTexture(*mTextureIdleSheet5);
		break;
	}
	}
}

void Player::setHedgeTool(Shears *s, int i){
	mHedgeTool = s;
	intCutter = i;
}

cutVector Player::getCuts(){
	return mHedgeTool->getCuts(mArrayX, mArrayY);
	//return mHedgeTool->getCuts(0, 0);
}

void Player::setLast(float l){
	mLast = l;
	mType = mBaseType + (mLast - 2);
}

void Player::changeAnimation(int nr) {
	/*stringstream blubb;
	if (walking) {
		blubb << "walk" << nr;
		animatorMeep->playAnimation(blubb.str(), true);
	}
	else {
		blubb << "idle" << nr;
		animatorMeep->playAnimation(blubb.str(), true);
	}*/
	if (!walking) {
		if (nr == 1) {
			animatorMeep->playAnimation("idle2", true);
		}
		if (nr == 2) {
			animatorMeep->playAnimation("idle1", true);
		}
		if (nr == 3) {
			animatorMeep->playAnimation("idle8", true);
		}
		if (nr == 4) {
			animatorMeep->playAnimation("idle3", true);
		}
		if (nr == 6) {
			animatorMeep->playAnimation("idle7", true);
		}
		if (nr == 7) {
			animatorMeep->playAnimation("idle4", true);
		}
		if (nr == 8) {
			animatorMeep->playAnimation("idle5", true);
		}
		if (nr == 9) {
			animatorMeep->playAnimation("idle6", true);
		}
	}
	else {
		if (nr == 1) {
			animatorMeep->playAnimation("walk2", true);
		}
		if (nr == 2) {
			animatorMeep->playAnimation("walk1", true);
		}
		if (nr == 3) {
			animatorMeep->playAnimation("walk8", true);
		}
		if (nr == 4) {
			animatorMeep->playAnimation("walk3", true);
		}
		if (nr == 6) {
			animatorMeep->playAnimation("walk7", true);
		}
		if (nr == 7) {
			animatorMeep->playAnimation("walk4", true);
		}
		if (nr == 8) {
			animatorMeep->playAnimation("walk5", true);
		}
		if (nr == 9) {
			animatorMeep->playAnimation("walk6", true);
		}
	}
}

void Player::playPlayer() {
	animatorMeep->update(clock.restart());
	if (walking) {
		animatorMeep->animate(*mSpriteWalkSheet);
	}
	else {
		animatorMeep->animate(*mSpriteIdleSheet);
	}
}

void Player::setWalking(bool walk) {
	walking = walk;
}

bool Player::getWalking() {
	return walking;
}

float Player::getMoveTime() {
	return mMoveTime;
}

sf::Sprite* Player::getSpriteSheet() {
	if (walking) {
		return mSpriteWalkSheet;
	}
	else {
		return mSpriteIdleSheet;
	}
}
void Player::scale(sf::RenderWindow &window) {
	float scaleX = (float)window.getSize().x / 1920;
	float scaleY = (float)window.getSize().y / 1080;

	mSpriteIdleSheet->setScale(sf::Vector2f(scaleX, scaleY));
	mSpriteWalkSheet->setScale(sf::Vector2f(scaleX, scaleY));
}
Mower* Player::mower() {
	return mLawnMower;
}