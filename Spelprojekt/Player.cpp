#include "Player.h"

using namespace std;

sf::Texture texturePlayer;
sf::Image imagePlayer;
static const string filename = "meep.png";

Player::Player(int arrX, int arrY, Mower *m, float posX, float posY):
	mArrayX(arrX),
	mArrayY(arrY),
	lawnMower(m){	
	mPosX = posX;
	mPosY = posY;
	mPlayerSprite.setPosition(posX, posY);
	mType = 5.0f;
}

void Player::updPos(float x, float y){
	mPosX += x;
	mPosY += y;
	mPlayerSprite.setPosition(mPosX, mPosY);
}

Player::~Player(){
	delete lawnMower;
}
intVector Player::move(int dir){
	intVector movement = lawnMower->getMove(dir);
	return movement;
}

void Player::collide(intVector moves, int atPos){
	int dmg = 0;
	for (int i = atPos; i < moves.size(); i++){
		dmg++;
	}
	lawnMower->setToMin(dmg);
}

float Player::getPosX(){
	return mPosX;
}
float Player::getPosY(){
	return mPosY;
}
void Player::render(){
	mPlayerSprite.setTexture(texturePlayer);
}
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
sf::Sprite Player::getSprite(){
	return mPlayerSprite;
}


float Player::getType(){
	return mType;
}

float Player::getLast(){
	return mLast;
}

void Player::setLast(float l){
	mLast = l;
}
void Player::initialize(){
	imagePlayer.loadFromFile(filename);
	imagePlayer.createMaskFromColor(sf::Color::White);
	texturePlayer.loadFromImage(imagePlayer);
}
void Player::finalize(){
	texturePlayer.~Texture();
}
/*void Player::update(){

}*/