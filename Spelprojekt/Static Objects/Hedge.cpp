#include "Hedge.h"

using namespace std;

static const string filename = "Resource Files/Sprites/hedge.png";
static const string filename2 = "Resource Files/Sprites/cuthedge.png";
sf::Texture textureHedge;
sf::Texture textureCutHedge;
sf::Image imageHedge;
sf::Image imageCutHedge;


Hedge::Hedge(int arrayX, int arrayY, float posX, float posY){
	mArrayX = arrayX;
	mArrayY = arrayY;
	mPosX = posX;
	mPosY = posY;
	mSprite.setPosition(mPosX, mPosY);
}
Hedge::~Hedge(){

}
void Hedge::render(){
	if (!isCut){
		mSprite.setTexture(textureHedge);
	}
	else{
		mSprite.setTexture(textureCutHedge);
	}
}
float Hedge::getPosX(){
	return mPosX;
}
float Hedge::getPosY(){
	return mPosY;
}
int Hedge::getArrayX(){
	return mArrayX;
}
int Hedge::getArrayY(){
	return mArrayY;
}
sf::Sprite* Hedge::getSprite(){
	return &mSprite;
}
sf::Sprite Hedge::getDrawSprite(){
	return mSprite;
}
void Hedge::setCut(){
	isCut = true;
}
bool Hedge::getCut(){
	return isCut;
}
void Hedge::initialize(){
	imageHedge.loadFromFile(filename);
	imageHedge.createMaskFromColor(sf::Color::White); 
	imageCutHedge.loadFromFile(filename2);
	imageCutHedge.createMaskFromColor(sf::Color::White);
	textureHedge.loadFromImage(imageHedge);
	textureCutHedge.loadFromImage(imageCutHedge);
}
void Hedge::finalize(){
	textureHedge.~Texture();
	textureCutHedge.~Texture();
	imageHedge.~Image();
	imageCutHedge.~Image();
}