#include "Grass.h"

using namespace std;

static const string filename = "grass.png";
sf::Texture textureGrass;

Grass::Grass(float x, float y){
	mX = x;
	mY = y;
	mSprite.setPosition(mX, mY);
}
Grass::~Grass(){

}
void Grass::render(){
	mSprite.setTexture(textureGrass);
}
float Grass::getX(){
	return mX;
}
float Grass::getY(){
	return mY;
}
sf::Sprite Grass::getSprite(){
	return mSprite;
}
void Grass::initialize(){
	textureGrass.loadFromFile(filename);
}
void Grass::finalize(){
	textureGrass.~Texture();
}