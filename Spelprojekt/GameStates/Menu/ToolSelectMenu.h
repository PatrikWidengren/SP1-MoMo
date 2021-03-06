#ifndef INCLUDED_TOOLMENU
#define INCLUDED_TOOLMENU
#include "menu.h"

class ToolSelectMenu : public Menu
{
public:
	ToolSelectMenu(float width, float height);
	ToolSelectMenu();
	~ToolSelectMenu();
	// Load a backgrounds to show for the menu
	sf::Texture* highlighttextBg01 = new sf::Texture(); //the highlightTexture for displaying.
	sf::Texture* textBg01 = new sf::Texture(); //hold the texture

	sf::Sprite* bg01 = new sf::Sprite(); //Drawable sprite wich gets a texture later. Bg stands for background
	sf::Sprite* highlightSprite01 = new sf::Sprite(); //when you hover, or select. the alternative brightens upp.

	virtual int checkState();
	virtual void updateToolSelectMenu(sf::RenderWindow &window, sf::Vector2i &mouse);
	virtual void displayMenu01(sf::RenderWindow &window);
	virtual void moveUp();
	virtual void moveDown();
	sf::Vector2i mMouse;
protected:
	static int const mNumberOfSelections = 3;

private:
	sf::IntRect *mRects[mNumberOfSelections];
	int mState;
	int mTimer;
	int selectedIndex;
	sf::Font font;
	sf::Text menu[mNumberOfSelections];
	virtual void setTextures(); //Set a texture to a sprite
	virtual void setFonts();
	//flaggor f�r keypress
	bool mReturn = false;
	bool mDown = false;
	bool mUp = false;
};

#endif


