#ifndef INCLUDED_HEDGE
#define INCLUDED_HEDGE

#include "StaticObjects.h"

//Underklass till "StaticObjects"
class Hedge : public StaticObjects{
public:
	Hedge(int arrayX, int arrayY, float posX, float posY);
	virtual ~Hedge();
	virtual void render();
	virtual float getPosX();
	virtual float getPosY();
	virtual int getArrayX();
	virtual int getArrayY();
	virtual sf::Sprite getSprite();
	virtual void setCut();
	virtual bool getCut();

	static void initialize();
	static void finalize();
private:
	bool isCut = false;
	float mPosX, mPosY;
	int mArrayX, mArrayY;
	sf::Sprite mSprite;
};

#endif