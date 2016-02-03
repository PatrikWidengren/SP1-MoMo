#ifndef INCLUDED_STATICOBJECTS
#define INCLUDED_STATICOBJECTS
#include <SFML\Graphics.hpp>

//Basklass f�r alla statiska objekt (+ ev. r�rliga)
class StaticObjects{
public:
	StaticObjects();
	virtual ~StaticObjects();
	virtual void render() = 0;
	virtual float getX() = 0;
	virtual float getY() = 0;
	virtual sf::Sprite getSprite() = 0;


};


#endif