#ifndef INCLUDED_FENCE
#define INCLUDED_FENCE

#include "StaticObjects.h"

//Underklass till "StaticObjects"
class Fence : public StaticObjects{
public:
	Fence(float x, float y, int whatFence);
	virtual ~Fence();
	virtual void render();
	virtual float getX();
	virtual float getY();
	virtual sf::Sprite getSprite();
	static void initialize();
	static void finalize();
private:
	int mWhatFence;
	float mX, mY;
	sf::Sprite mSprite;
};

#endif