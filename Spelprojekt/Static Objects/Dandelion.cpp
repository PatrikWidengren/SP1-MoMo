#include "Dandelion.h"

using namespace std;

static const string filename_Dandelion_Uncut = "Resource Files/Sprites/dandelion.png";
static const string filename_Dandelion_Cut = "Resource Files/Sprites/Grass01_Cut.png";
sf::Texture textureDandelion;
sf::Texture textureCutDandelion;

Dandelion::Dandelion(int arrayX, int arrayY, float posX, float posY) {
	mArrayX = arrayX;
	mArrayY = arrayY;
	mPosX = posX;
	mPosY = posY;
	mSprite.setPosition(mPosX, mPosY);
}
Dandelion::~Dandelion() {

}
void Dandelion::render() {
	if (!isCut) {
		mSprite.setTexture(textureDandelion);
	}
	else {
		mSprite.setTexture(textureCutDandelion);
	}
}
float Dandelion::getPosX() {
	return mPosX;
}
float Dandelion::getPosY() {
	return mPosY;
}
int Dandelion::getArrayX() {
	return mArrayX;
}
int Dandelion::getArrayY() {
	return mArrayY;
}
sf::Sprite* Dandelion::getSprite() {
	return &mSprite;
}
sf::Sprite Dandelion::getDrawSprite() {
	return mSprite;
}
void Dandelion::setCut() {
	isCut = true;
}
bool Dandelion::getCut() {
	return isCut;
}
void Dandelion::initialize() {
	textureDandelion.loadFromFile(filename_Dandelion_Uncut);
	textureCutDandelion.loadFromFile(filename_Dandelion_Cut);
}
void Dandelion::finalize() {
	textureDandelion.~Texture();
	textureCutDandelion.~Texture();
}