#include "Fountain.h"

using namespace std;

static const string filename_Fountain = "Resource Files/SpriteSheets/Fontän_3x3_Spritesheet_Nearest.png";
sf::Texture textureFountain;

static const int spriteWidth = 192;
static const int spriteHeight = 192;

Fountain::Fountain(int arrayX, int arrayY, float posX, float posY) {
	mArrayX = arrayX;
	mArrayY = arrayY;
	mPosX = posX;
	mPosY = posY;
	mSprite.setPosition(mPosX, mPosY);

	mTextureSheet_fountain->loadFromFile(filename_Fountain);
	mFountainSheet->setTexture(*mTextureSheet_fountain);

	thor::FrameAnimation frame;
	for (int i = 0; i < 8; i++) {
		mRect = new sf::IntRect(sf::Vector2i(0 + spriteWidth * i, 0), sf::Vector2i(spriteWidth, spriteHeight));
		frame.addFrame(0.4f, *mRect);
	}
	fountainAnimator.addAnimation("animation", frame, sf::seconds(0.8f));
	fountainAnimator.playAnimation("animation", true);
}
Fountain::~Fountain() {

}
void Fountain::playAnimation() {
	fountainAnimator.update(clock.restart());
	fountainAnimator.animate(*mFountainSheet);
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
	return mFountainSheet;
}
sf::Sprite Fountain::getDrawSprite() {
	return *mFountainSheet;
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