#ifndef INCLUDED_STONE
#define INCLUDED_STONE

#include "StaticObjects.h"

//Underklass till "StaticObjects"
class Stone : public StaticObjects{
public:
	Stone(float x, float y);
	virtual ~Stone();
	virtual void render();
	virtual float getX();
	virtual float getY();
	virtual sf::Sprite getSprite();
	static void initialize();
	static void finalize();
private:
	float mX, mY;
	sf::Sprite mSprite;
};

#endif