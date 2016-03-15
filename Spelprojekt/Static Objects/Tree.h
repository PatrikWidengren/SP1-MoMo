#ifndef INCLUDED_TREE
#define INCLUDED_TREE

#include "StaticObjects.h"

//Underklass till "StaticObjects"
class Tree : public StaticObjects{
public:
	Tree(int arrayX, int arrayY, float posX, float posY);
	virtual ~Tree();
	virtual void render();
	virtual float getPosX();
	virtual float getPosY();
	virtual int getArrayX();
	virtual int getArrayY();
	virtual sf::Sprite* getSprite();
	virtual sf::Sprite getDrawSprite();
	virtual bool getWalkable();
	virtual void changeWalkable();
	virtual void setCut();
	virtual bool getCut();
	virtual void playAnimation();

	static void initialize();
	static void finalize();
private:
	float mPosX, mPosY;
	int mArrayX, mArrayY;
	bool mWalk = true;
	sf::Sprite mSprite;
	sf::Sprite spr;
};

#endif