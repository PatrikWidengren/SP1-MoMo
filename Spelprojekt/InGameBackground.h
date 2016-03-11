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
	std::string writeTurns(int turns);
	std::string writeProgress(int cutgrass, int cuthedges, int cutdandelions, std::vector<int>* goals);
	int getTurns();
	void write(int turncount, int cutgrass, int cuthedges, int cutdandelions, std::vector<int>* goals);
private:
	//int mIntTurns;
	sf::Font font;
	sf::Texture* texture01_backgroundTop = new sf::Texture();
	sf::Texture* texture01_backgroundBottom = new sf::Texture();
	sf::Texture* texture02_backgroundTop = new sf::Texture();
	sf::Texture* texture02_backgroundBottom = new sf::Texture();
	sf::Texture* texture03_backgroundTop = new sf::Texture();
	sf::Texture* texture03_backgroundBottom = new sf::Texture();
	sf::Texture* texture04_backgroundTop = new sf::Texture();
	sf::Texture* texture04_backgroundBottom = new sf::Texture();
	sf::Texture* texture05_backgroundTop = new sf::Texture();
	sf::Texture* texture05_backgroundBottom = new sf::Texture();
	sf::Texture* texture_inGameHud = new sf::Texture();
	sf::Sprite* backgroundTop = new sf::Sprite();
	sf::Sprite* backgroundBottom = new sf::Sprite();
	sf::Sprite* inGameHud = new sf::Sprite();
	std::string mMapName;
	sf::Text* mTurns = new sf::Text; //(writeTurns(int turns), font, 20);
	sf::Text* mProgress = new sf::Text;
	std::vector<int>* mGoals;
};


#endif 
