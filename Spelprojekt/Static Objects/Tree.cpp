#include "Tree.h"

using namespace std;

static const string filename = "Resource Files/Sprites/Tree.png";
sf::Texture textureTree;
sf::Image image;

Tree::Tree(int arrayX, int arrayY, float posX, float posY){
	mArrayX = arrayX;
	mArrayY = arrayY;
	mPosX = posX;
	mPosY = posY;
	spr.setPosition(mPosX, mPosY);
}
Tree::~Tree(){

}
void Tree::render(){
	spr.setTexture(textureTree);
}
float Tree::getPosX(){
	return mPosX;
}
float Tree::getPosY(){
	return mPosY;
}
int Tree::getArrayX(){
	return mArrayX;
}
int Tree::getArrayY(){
	return mArrayY;
}
void Tree::setCut(){
}
bool Tree::getCut(){
	return false;
}
sf::Sprite Tree::getSprite(){
	return spr;
}
bool Tree::getWalkable(){
	return mWalk;
}
void Tree::changeWalkable(){
	if (mWalk){
		mWalk = false;
	}
	else if (!mWalk){
		mWalk = true;
	}
}
void Tree::initialize(){
	image.loadFromFile(filename);
	image.createMaskFromColor(sf::Color::White);
	textureTree.loadFromImage(image);
}
void Tree::finalize(){
	textureTree.~Texture();
}