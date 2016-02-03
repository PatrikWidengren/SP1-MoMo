#ifndef INCLUDED_TEST
#define INCLUDED_TEST

#include "StaticObjects.h"

//Underklass till "StaticObjects"
class Test : public StaticObjects{
public:
	Test(float x, float y);
	virtual ~Test();
	virtual void render();
	virtual float getX();
	virtual float getY();
	virtual sf::Sprite getSprite();
	virtual bool getWalkable();
	virtual void changeWalkable();
	static void initialize();
	static void finalize();
private:
	float mX, mY;
	bool mWalk = true;
	sf::Sprite mSprite;
	sf::Sprite spr;
};

#endif