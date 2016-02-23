#include "Player.h"
#include <iostream>

using namespace std;

sf::Texture texturePlayer;
sf::Image imagePlayer;
static const string filename = "Resource Files/Sprites/meep02.png";

Player::Player(Mower *m, Shears *c/*, float posX, float posY*/) :
	mLawnMower(m),
	mAntiLeakMower(m),
	mHedgeTool(c),
	mAntiLeakHedgeTool(c),
	mBaseType(5.0f){
	//mPosX = posX;
	//mPosY = posY;
	//mPlayerSprite.setPosition(posX, posY);
	mType = 5.1f;
	//Temporär lösning. Bör fixas snarast
	mLast = 2.1f;
	mPlayerSprite.setTexture(texturePlayer);
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

void Player::setX(int x){
	mArrayX = x;
}

void Player::setY(int y){
	mArrayY = y;
}
sf::Sprite* Player::getSprite(){
	return &mPlayerSprite;
}

sf::Sprite Player::getDrawSprite(){
	return mPlayerSprite;
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
void Player::initialize(){
	imagePlayer.loadFromFile(filename);
	imagePlayer.createMaskFromColor(sf::Color::White);
	texturePlayer.loadFromImage(imagePlayer);
}
void Player::finalize(){
	texturePlayer.~Texture();
	imagePlayer.~Image();
}
/*void Player::update(){

}*/