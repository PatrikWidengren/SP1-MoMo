#include "Stone.h"

using namespace std;

static const string filename = "Resource Files/Sprites/TreeStump1.png";

sf::Texture textureStone;

Stone::Stone(int arrayX, int arrayY, float posX, float posY){
	mArrayX = arrayX;
	mArrayY = arrayY;
	mPosX = posX;
	mPosY = posY;

	mSprite.setPosition(mPosX, mPosY);
}
Stone::~Stone(){

}
void Stone::render(){
	mSprite.setTexture(textureStone);
}
float Stone::getPosX(){
	return mPosX;
}
float Stone::getPosY(){
	return mPosY;
}
int Stone::getArrayX(){
	return mArrayX;
}
int Stone::getArrayY(){
	return mArrayY;
}
void Stone::setCut(){
}
bool Stone::getCut(){
	return false;
}
sf::Sprite* Stone::getSprite(){
	return &mSprite;
}
sf::Sprite Stone::getDrawSprite(){
	return mSprite;
}
void Stone::initialize(){
	textureStone.loadFromFile(filename);
}
void Stone::finalize(){
	textureStone.~Texture();
}