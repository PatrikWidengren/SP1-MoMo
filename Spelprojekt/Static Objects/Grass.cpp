#include "Grass.h"

using namespace std;

static const string filename_Grass_Uncut = "Grass_Uncut";
static const string filename_Grass_Cut = "Grass_Cut";


Grass::Grass(int arrayX, int arrayY, float posX, float posY, TextureManager &holder) 
	: textureGrass(holder.getTexture(filename_Grass_Uncut)), textureCutGrass(holder.getTexture(filename_Grass_Cut)){
	mArrayX = arrayX;
	mArrayY = arrayY;
	mPosX = posX;
	mPosY = posY;

	mSprite->setPosition(mPosX, mPosY);
}
Grass::~Grass(){

}
void Grass::render(){
	if (!isCut){
		mSprite->setTexture(textureGrass);
	}
	else{
		mSprite->setTexture(textureCutGrass);
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
sf::Sprite* Grass::getSprite(){
	return mSprite;
}
sf::Sprite Grass::getDrawSprite(){
	return *mSprite;
}
void Grass::setCut(){
	isCut = true;
}
bool Grass::getCut(){
	return isCut;
}
void Grass::initialize(){
	/*textureGrass->loadFromFile(filename_Grass_Uncut);
	textureCutGrass->loadFromFile(filename_Grass_Cut);*/
}
void Grass::finalize(){
	/*textureGrass->~Texture();
	textureCutGrass->~Texture();*/
}