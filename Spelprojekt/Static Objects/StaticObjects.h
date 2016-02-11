#ifndef INCLUDED_STATICOBJECTS
#define INCLUDED_STATICOBJECTS
#include <SFML\Graphics.hpp>

//Basklass för alla statiska objekt (+ ev. rörliga)
class StaticObjects{
public:
	StaticObjects();
	virtual ~StaticObjects();
	virtual void render() = 0;
	//Returnerar position i pixlar
	virtual float getPosX() = 0;
	virtual float getPosY() = 0;
	//Returnerar positionen i arrayen
	virtual int getArrayX() = 0;
	virtual int getArrayY() = 0;
	//Ändrar variabel "isCut" till true, används enbart i klassen Grass
	virtual void setCut() = 0;
	//Returnerar true/false beroende på om gräset är klippt eller inte
	virtual bool getCut() = 0;
	virtual sf::Sprite getSprite() = 0;


};


#endif