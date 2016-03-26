#ifndef INCLUDED_WORLDMAP
#define INCLUDED_WORLDMAP

#include "Menu/menu.h"
#include <sstream>

struct MapRegions 
{
	std::string RegionID;
	int levelCount = 0;
	bool unlock = false;
	sf::Text mapRegionText;
	int mCostRegion;

};


class WorldMap : public Menu
{
public:
	WorldMap(float width, float height);
	WorldMap();
	~WorldMap();
	bool reset = false;
	bool mRegionUnlock[4];
	MapRegions mMapRegions[4];
	// Load a backgrounds to show for the menu
	sf::Texture* highlightTexture01 = new sf::Texture(); //the highlightTexture for displaying.
	sf::Texture* texture01 = new sf::Texture(); //hold the texture
	sf::Texture* textGreenDot = new sf::Texture();
	sf::Texture* textureCheat = new sf::Texture();
	sf::Texture* textureExit = new sf::Texture();

	sf::Sprite* bg01 = new sf::Sprite(); //Drawable sprite wich gets a texture later. Bg stands for background
	sf::Sprite* highlightSprite01 = new sf::Sprite(); //when you hover, or select. the alternative brightens upp.

	sf::Sprite* spriteGreenDot01 = new sf::Sprite();
	sf::Sprite* spriteGreenDot02 = new sf::Sprite();
	sf::Sprite* spriteGreenDot03 = new sf::Sprite();
	sf::Sprite* spriteGreenDot04 = new sf::Sprite();

	sf::Sprite* cheat = new sf::Sprite();
	sf::Sprite* exit = new sf::Sprite();

	virtual int checkState();
	int getRegion();
	void resetRegion();
	int getDemDopies();
	void setDemDopies(int demDopies);
	void addDemDopies(int demDopies);
	virtual void updateWorldMap(sf::RenderWindow &window, sf::Vector2i &mouse);
	virtual void displayMenu01(sf::RenderWindow &window);
	virtual void moveUp();
	virtual void moveDown();
	virtual void scale(sf::RenderWindow &window);
	int mDemDupies;
	int g; int h; int j; int k;
	void fadeText(std::string id);
protected:
	static int const mNumberOfSelections = 7;

private:
	sf::IntRect *mRects[mNumberOfSelections];
	sf::Vector2i mMouse;
	int mState;
	int mRegion=0;
	int mTimer;
	int selectedIndex;
	sf::Font font;
	sf::Text mShowDemDupies;

	std::string WriteRegionCost(int cost);

	std::string WriteDopies(int d);
	virtual void setTextures(); //Set a texture to a sprite
	virtual void setFonts();
	//flaggor för keypress
	bool mReturn = false;
	bool mDown = false;
	bool mUp = false;
};


#endif