#include "Fountain.h"

using namespace std;

static const string filename_Fountain = "Resource Files/Sprites/Fountain_3x3(1).png";
sf::Texture textureFountain;

Fountain::Fountain(int arrayX, int arrayY, float posX, float posY) {
	mArrayX = arrayX;
	mArrayY = arrayY;
	mPosX = posX;
	mPosY = posY;
	mSprite.setPosition(mPosX, mPosY);
}
Fountain::~Fountain() {

}
void Fountain::render() {
	mSprite.setTexture(textureFountain);
}
float Fountain::getPosX() {
	return mPosX;
}
float Fountain::getPosY() {
	return mPosY;
}
int Fountain::getArrayX() {
	return mArrayX;
}
int Fountain::getArrayY() {
	return mArrayY;
}
sf::Sprite* Fountain::getSprite() {
	return &mSprite;
}
sf::Sprite Fountain::getDrawSprite() {
	return mSprite;
}
void Fountain::setCut() {
}
bool Fountain::getCut() {
	return isCut;
}
void Fountain::initialize() {
	textureFountain.loadFromFile(filename_Fountain);
}
void Fountain::finalize() {
	textureFountain.~Texture();
}