#include "Stone.h"

using namespace std;

static const string filename = "stone.png";

sf::Texture textureStone;

Stone::Stone(float x, float y){
	mX = x;
	mY = y;

	mSprite.setPosition(mX, mY);	
}
Stone::~Stone(){

}
void Stone::render(){
	mSprite.setTexture(textureStone);
}
float Stone::getX(){
	return mX;
}
float Stone::getY(){
	return mY;
}
sf::Sprite Stone::getSprite(){
	return mSprite;
}
void Stone::initialize(){
	textureStone.loadFromFile(filename);
}
void Stone::finalize(){
	textureStone.~Texture();
}