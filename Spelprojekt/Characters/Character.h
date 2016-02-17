#ifndef INCLUDED_NPCBASE
#define INCLUDED_NPCBASE
#include <vector>
#include "SFML\Graphics.hpp"

typedef std::vector<int> intVector;
class Character{
public:
	Character();
	virtual ~Character();
	virtual float getPosX() = 0;
	virtual float getPosY() = 0;
	virtual intVector move() = 0;
	virtual intVector collide(intVector moves, int atPos) = 0;
	virtual int getX() = 0;
	virtual int getY() = 0;
	virtual void setX(int x) = 0;
	virtual void setY(int Y) = 0;
	virtual void setLast(float l) = 0;
	virtual float getLast() = 0;
	virtual float getType() = 0;
	virtual void updPos(float x, float y) = 0;
	virtual void render() = 0;
	virtual sf::Sprite* getSprite() = 0;
	virtual sf::Sprite getDrawSprite() = 0;
	//Treat this as running into and colliding with things?
	virtual bool getCollide() = 0;
};

#endif