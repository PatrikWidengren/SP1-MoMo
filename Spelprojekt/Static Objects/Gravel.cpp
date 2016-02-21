#include "Gravel.h"

using namespace std;

static const string filename_Gravel = "Resource Files/Sprites/gravel.png";
sf::Texture textureGravel;

Gravel::Gravel(int arrayX, int arrayY, float posX, float posY) {
	mArrayX = arrayX;
	mArrayY = arrayY;
	mPosX = posX;
	mPosY = posY;
	mSprite.setPosition(mPosX, mPosY);
}
Gravel::~Gravel() {

}
void Gravel::render() {
	mSprite.setTexture(textureGravel);
}
float Gravel::getPosX() {
	return mPosX;
}
float Gravel::getPosY() {
	return mPosY;
}
int Gravel::getArrayX() {
	return mArrayX;
}
int Gravel::getArrayY() {
	return mArrayY;
}
sf::Sprite* Gravel::getSprite() {
	return &mSprite;
}
sf::Sprite Gravel::getDrawSprite() {
	return mSprite;
}
void Gravel::setCut() {
}
bool Gravel::getCut() {
	return isCut;
}
void Gravel::initialize() {
	textureGravel.loadFromFile(filename_Gravel);
}
void Gravel::finalize() {
	textureGravel.~Texture();
}