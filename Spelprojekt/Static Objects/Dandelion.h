#ifndef INCLUDED_DANDELION
#define INCLUDED_DANDELION

#include "StaticObjects.h"

//Underklass till "StaticObjects"
class Dandelion : public StaticObjects {
public:
	Dandelion(int arrayX, int arrayY, float posX, float posY);
	virtual ~Dandelion();
	virtual void render();
	virtual float getPosX();
	virtual float getPosY();
	virtual int getArrayX();
	virtual int getArrayY();
	virtual sf::Sprite* getSprite();
	virtual sf::Sprite getDrawSprite();
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