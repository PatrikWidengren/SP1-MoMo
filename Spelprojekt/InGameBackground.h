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
	sf::Texture* texture_backgroundTop = new sf::Texture();
	sf::Texture* texture_backgroundBottom = new sf::Texture();
	sf::Texture* texture_inGameHud = new sf::Texture();
	sf::Sprite* backgroundTop = new sf::Sprite();
	sf::Sprite* backgroundBottom = new sf::Sprite();
	sf::Sprite* inGameHud = new sf::Sprite();
	std::string mMapName;
};


#endif 
