#ifndef INCLUDED_FENCE
#define INCLUDED_FENCE

#include "StaticObjects.h"

//Underklass till "StaticObjects"
class Fence : public StaticObjects{
public:
	Fence(int arrayX, int arrayY, float posX, float posY, int whatFence);
	virtual ~Fence();
	virtual void render();
	virtual float getPosX();
	virtual float getPosY();
	virtual int getArrayX();
	virtual int getArrayY();
	virtual sf::Sprite* getSprite();
	virtual sf::Sprite getDrawSprite();
	virtual void setCut();
	virtual bool getCut();
	virtual void playAnimation();

	static void initialize();
	static void finalize();
private:
	int mWhatFence;
	float mPosX, mPosY;
	int mArrayX, mArrayY;
	sf::Sprite mSprite;
};

#endif