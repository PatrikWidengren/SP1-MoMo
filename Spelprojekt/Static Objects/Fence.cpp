#include "Fence.h"

using namespace std;

static const string filename_fence_Top = "Resource Files/Sprites/Fence01_01.png";
static const string filename_fence_Bottom = "Resource Files/Sprites/Fence01_03.png";
static const string filename_fence_Right = "Resource Files/Sprites/Fence01_02.png";
static const string filename_fence_Left = "Resource Files/Sprites/Fence01_04.png";
static const string filename_fence_TopLeft = "Resource Files/Sprites/Fence01Corner_01.png";
static const string filename_fence_TopRight = "Resource Files/Sprites/Fence01Corner_02.png";
static const string filename_fence_BottomRight = "Resource Files/Sprites/Fence01Corner_03.png";
static const string filename_fence_BottomLeft = "Resource Files/Sprites/Fence01Corner_04.png";

sf::Texture textureFenceTop;
sf::Texture textureFenceBottom;
sf::Texture textureFenceRight;
sf::Texture textureFenceLeft;
sf::Texture textureFenceBottomLeft;
sf::Texture textureFenceBottomRight;
sf::Texture textureFenceTopRight;
sf::Texture textureFenceTopLeft;

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
	if (mWhatFence == 1){
		mSprite.setTexture(textureFenceTop);
	}
	if (mWhatFence == 2){
		mSprite.setTexture(textureFenceBottom);
	}
	if (mWhatFence == 3){
		mSprite.setTexture(textureFenceRight);
	}
	if (mWhatFence == 4){
		mSprite.setTexture(textureFenceLeft);
	}
	if (mWhatFence == 5){
		mSprite.setTexture(textureFenceBottomLeft);
	}
	if (mWhatFence == 6){
		mSprite.setTexture(textureFenceBottomRight);
	}
	if (mWhatFence == 7){
		mSprite.setTexture(textureFenceTopRight);
	}
	if (mWhatFence == 8){
		mSprite.setTexture(textureFenceTopLeft);
	}

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
	//imageFence.loadFromFile(filename);
	//imageFence.createMaskFromColor(sf::Color::White);

	textureFenceTop.loadFromFile(filename_fence_Bottom);
	textureFenceBottom.loadFromFile(filename_fence_Top);
	textureFenceRight.loadFromFile(filename_fence_Right);
	textureFenceLeft.loadFromFile(filename_fence_Left);
	textureFenceBottomLeft.loadFromFile(filename_fence_BottomLeft);
	textureFenceBottomRight.loadFromFile(filename_fence_BottomRight);
	textureFenceTopRight.loadFromFile(filename_fence_TopRight);
	textureFenceTopLeft.loadFromFile(filename_fence_TopLeft);

}
void Fence::finalize(){
	textureFenceTop.~Texture();
	textureFenceBottom.~Texture();
	textureFenceRight.~Texture();
	textureFenceLeft.~Texture();
	textureFenceBottomLeft.~Texture();
	textureFenceBottomRight.~Texture();
	textureFenceTopRight.~Texture();
	textureFenceTopLeft.~Texture();

	//imageFence.~Image();
}