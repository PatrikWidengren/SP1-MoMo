#include "LongspriteTest.h"

using namespace std;

static const string filename = "test.png";
sf::Texture textureTest;
sf::Image image;

Test::Test(float x, float y){
	mX = x;
	mY = y;
	spr.setPosition(mX, mY);
}
Test::~Test(){

}
void Test::render(){
	spr.setTexture(textureTest);
}
float Test::getX(){
	return mX;
}
float Test::getY(){
	return mY;
}
sf::Sprite Test::getSprite(){
	return spr;
}
bool Test::getWalkable(){
	return mWalk;
}
void Test::changeWalkable(){
	if (mWalk){
		mWalk = false;
	}
	else if (!mWalk){
		mWalk = true;
	}
}
void Test::initialize(){
	image.loadFromFile(filename);
	image.createMaskFromColor(sf::Color::White);
	textureTest.loadFromImage(image);
}
void Test::finalize(){
	textureTest.~Texture();
}