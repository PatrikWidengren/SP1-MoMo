#ifndef INCLUDED_GRASS
#define INCLUDED_GRASS

#include "StaticObjects.h"

//Underklass till "StaticObjects"
class Grass : public StaticObjects{
public:
	Grass(float x, float y);
	virtual ~Grass();
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