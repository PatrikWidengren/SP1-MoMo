#ifndef INCLUDED_INGAMEBACKGROUND
#define INCLUDED_INGAMEBACKGROUND

#include <SFML\Graphics.hpp>
#include <sstream>
#include <iostream>

class InGameBackground {
public:
	InGameBackground();
	~InGameBackground();
	void drawBackgroundTop(sf::RenderWindow &window);
	void drawBackgroundBottom(sf::RenderWindow &window);
	void setTextures();
	void setMapname(std::string mapname);
private:
	sf::Texture texture_backgroundTop;
	sf::Texture texture_backgroundBottom;
	sf::Texture texture_inGameHud;
	sf::Sprite backgroundTop;
	sf::Sprite backgroundBottom;
	sf::Sprite inGameHud;
	std::string mMapName;
};


#endif 
