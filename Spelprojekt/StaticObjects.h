#ifndef INCLUDED_STATICOBJECTS
#define INCLUDED_STATICOBJECTS
#include <SFML\Graphics.hpp>

//Basklass f�r alla statiska objekt (+ ev. r�rliga)
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
	//�ndrar variabel "isCut" till true, anv�nds enbart i klassen Grass
	virtual void setCut() = 0;
	//Returnerar true/false beroende p� om gr�set �r klippt eller inte
	virtual bool getCut() = 0;
	virtual sf::Sprite getSprite() = 0;


};


#endif