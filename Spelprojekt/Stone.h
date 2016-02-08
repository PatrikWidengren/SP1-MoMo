#ifndef INCLUDED_STONE
#define INCLUDED_STONE

#include "StaticObjects.h"

//Underklass till "StaticObjects"
class Stone : public StaticObjects{
public:
	Stone(int arrayX, int arrayY, float posX, float posY);
	virtual ~Stone();
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
	float mPosX, mPosY;
	int mArrayX, mArrayY;
	sf::Sprite mSprite;
};

#endif