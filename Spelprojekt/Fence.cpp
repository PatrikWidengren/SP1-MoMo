#include "Fence.h"

using namespace std;

static const string filename = "fence_01.png";
sf::Texture textureFence;
sf::Image imageFence;

Fence::Fence(float x, float y, int whatFence){
	mWhatFence = whatFence;
	mX = x;
	mY = y;
	mSprite.setPosition(mX, mY);
}
Fence::~Fence(){

}
void Fence::render(){
	mSprite.setTexture(textureFence);
}
float Fence::getX(){
	return mX;
}
float Fence::getY(){
	return mY;
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