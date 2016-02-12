#include "Grass.h"

using namespace std;

static const string filename = "Resource Files/Sprites/grass.png";
static const string filename2 = "Resource Files/Sprites/cutgrass.png";
sf::Texture textureGrass;
sf::Texture textureCutGrass;

Grass::Grass(int arrayX, int arrayY, float posX, float posY){
	mArrayX = arrayX;
	mArrayY = arrayY;
	mPosX = posX;
	mPosY = posY;
	mSprite.setPosition(mPosX, mPosY);
}
Grass::~Grass(){

}
void Grass::render(){
	if (!isCut){
		mSprite.setTexture(textureGrass);
	}
	else{
		mSprite.setTexture(textureCutGrass);
	}
}
float Grass::getPosX(){
	return mPosX;
}
float Grass::getPosY(){
	return mPosY;
}
int Grass::getArrayX(){
	return mArrayX;
}
int Grass::getArrayY(){
	return mArrayY;
}
sf::Sprite Grass::getSprite(){
	return mSprite;
}
void Grass::setCut(){
	isCut = true;
}
bool Grass::getCut(){
	return isCut;
}
void Grass::initialize(){
	textureGrass.loadFromFile(filename);
	textureCutGrass.loadFromFile(filename2);
}
void Grass::finalize(){
	textureGrass.~Texture();
	textureCutGrass.~Texture();
}