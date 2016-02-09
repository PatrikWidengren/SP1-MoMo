#include "Fence.h"

using namespace std;

static const string filename = "fence_01.png";
sf::Texture textureFence;
sf::Image imageFence;

Fence::Fence(int arrayX, int arrayY, float posX, float posY, int whatFence){
	mWhatFence = whatFence;
	mArrayX = arrayX;
	mArrayY = arrayY;
	mPosX = posX;
	mPosY = posY;
	mSprite.setPosition(mPosX, mPosY);
}
Fence::~Fence(){

}
void Fence::render(){
	mSprite.setTexture(textureFence);
}
float Fence::getPosX(){
	return mPosX;
}
float Fence::getPosY(){
	return mPosY;
}
int Fence::getArrayX(){
	return mArrayX;
}
int Fence::getArrayY(){
	return mArrayY;
}
void Fence::setCut(){
}
bool Fence::getCut(){
	return false;
}
sf::Sprite Fence::getSprite(){
	return mSprite;
}
void Fence::initialize(){
	imageFence.loadFromFile(filename);
	imageFence.createMaskFromColor(sf::Color::White);
	textureFence.loadFromImage(imageFence);
}
void Fence::finalize(){
	textureFence.~Texture();
}