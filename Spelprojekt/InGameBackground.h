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
	std::string getMedal();
	std::string writeTurns(int turns);
	std::string writeProgress(int cutgrass, int cuthedges, int cutdandelions, std::vector<int>* goals);
	int getTurns();
	void write(int turncount, int cutgrass, int cuthedges, int cutdandelions, std::vector<int>* goals);
	void scale(sf::RenderWindow &window);
	void getInfo(int maxmomentum, int minmomentum, int currentmomentum, int fallvalue, int risevalue);
	void selectMomentumSprite();
	void selectLawnmowerSprite(int number);
	void selectHedgecutterSprite();
private:
	std::string mMedal;
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
	sf::Texture* texture_bronzeMedal = new sf::Texture();
	sf::Texture* texture_silverMedal = new sf::Texture();
	sf::Texture* texture_goldMedal = new sf::Texture();
	sf::Texture* texture_arrow = new sf::Texture();

	sf::Texture* texture_woodMedal = new sf::Texture();
	sf::Texture* texture_woodMomentum = new sf::Texture();
	sf::Texture* texture_woodMenu = new sf::Texture();
	sf::Texture* texture_woodLawnmower = new sf::Texture();
	sf::Texture* texture_woodHedgecutter = new sf::Texture();

	sf::Texture* texture_lawnmower01 = new sf::Texture();
	sf::Texture* texture_lawnmower02 = new sf::Texture();
	sf::Texture* texture_lawnmower03 = new sf::Texture();
	sf::Texture* texture_lawnmower04 = new sf::Texture();
	sf::Texture* texture_lawnmower05 = new sf::Texture();
	sf::Texture* texture_hedgecutter01 = new sf::Texture();
	sf::Texture* texture_momentumText = new sf::Texture();
	sf::Texture* texture_menuText = new sf::Texture();

	sf::Texture* texture_momentum2_01 = new sf::Texture();
	sf::Texture* texture_momentum2_02 = new sf::Texture();
	sf::Texture* texture_momentum3_01 = new sf::Texture();
	sf::Texture* texture_momentum3_02 = new sf::Texture();
	sf::Texture* texture_momentum3_03 = new sf::Texture();
	sf::Texture* texture_momentum4_01 = new sf::Texture();
	sf::Texture* texture_momentum4_02 = new sf::Texture();
	sf::Texture* texture_momentum4_03 = new sf::Texture();
	sf::Texture* texture_momentum4_04 = new sf::Texture();

	sf::Sprite* sprite_woodMedal = new sf::Sprite();
	sf::Sprite* sprite_woodLawnmower = new sf::Sprite();
	sf::Sprite* sprite_woodHedgecutter = new sf::Sprite();
	sf::Sprite* sprite_woodMenu = new sf::Sprite();
	sf::Sprite* sprite_woodMomentum = new sf::Sprite();
	sf::Sprite* sprite_hedgecutter = new sf::Sprite();
	sf::Sprite* sprite_lawnmower = new sf::Sprite();
	sf::Sprite* sprite_downArrow = new sf::Sprite();
	sf::Sprite* sprite_menuText = new sf::Sprite();

	sf::Sprite* sprite_momentumText = new sf::Sprite();
	sf::Sprite* sprite_momentum = new sf::Sprite();
	sf::Sprite* sprite_backgroundTop = new sf::Sprite();
	sf::Sprite* sprite_backgroundBottom = new sf::Sprite();
	sf::Sprite* sprite_inGameHud = new sf::Sprite();
	sf::Sprite* sprite_medal = new sf::Sprite();
	std::string mMapName;
	sf::Text* mTurns = new sf::Text; //(writeTurns(int turns), font, 20);
	sf::Text* mProgress = new sf::Text;

	sf::Image* imageArrow = new sf::Image;

	std::vector<int>* mGoals;

	int mMowerMaxMomentum;
	int mMowerMinMomentum;
	int mMowerFallValue;
	int mMowerRiseValue;
	int mMowerCurrentMomentum;
	int mCurrentLawnmower;
	int mCurrentHedgecutter;
};


#endif 
