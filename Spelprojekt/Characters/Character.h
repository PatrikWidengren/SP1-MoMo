#ifndef INCLUDED_NPCBASE
#define INCLUDED_NPCBASE
#include <vector>
#include <array>
#include "SFML\Graphics.hpp"
#include <Thor\Animations.hpp>
#include <sstream>

typedef std::array<int, 2> coords;

typedef std::vector<int> intVector;
class Character{
public:
	Character();
	virtual ~Character();
	virtual void reset()=0;
	virtual intVector move() = 0;
	virtual intVector collide(intVector moves, int atPos) = 0;
	virtual int getX() = 0;
	virtual int getY() = 0;
	virtual int getLastX() = 0;
	virtual int getLastY() = 0;

	virtual void setWalking(bool walk) = 0;
	virtual bool getWalking() = 0;

	virtual void setX(int x) = 0;
	virtual void setY(int Y) = 0;
	virtual void setLast(float l) = 0;
	virtual float getLast() = 0;
	virtual float getType() = 0;
	virtual void playAnimation() = 0;
	virtual void changeAnimation(int nr) = 0;
	virtual sf::Sprite* getSpriteSheet() = 0;
	virtual float getMoveTime() = 0;
	virtual void scale(sf::RenderWindow &window) = 0;


	//Treat this as running into and colliding with things?
	virtual bool getCollide() = 0;
};

#endif