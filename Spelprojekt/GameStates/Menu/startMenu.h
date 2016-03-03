#ifndef STARTMENU
#define STARTMENU

#include "menu.h"

class startMenu : public Menu
{
public:
	startMenu(float width, float height);
	startMenu();
	~startMenu();
	bool reset = false;

	// Load a backgrounds to show for the menu
	sf::Texture highlighttextBg01; //the highlightTexture for displaying.
	sf::Texture textBg01; //hold the texture

	sf::Texture textContinue;
	sf::Texture textNewgame;
	sf::Texture textOption;
	sf::Texture textCredits;
	sf::Texture textExit;

	sf::Texture textHighlightContinue;
	sf::Texture textHighlightNewgame;
	sf::Texture textHighlightOption;
	sf::Texture textHighlightCredits;
	sf::Texture textHighlightExit;

	sf::Sprite spriteContinue;
	sf::Sprite spriteNewgame;
	sf::Sprite spriteOption;
	sf::Sprite spriteCredits;
	sf::Sprite spriteExit;


	sf::Sprite bg01; //Drawable sprite wich gets a texture later. Bg stands for background
	sf::Sprite highlightSprite01; //when you hover, or select. the alternative brightens upp.

	virtual int checkState();
	virtual void updateStartMenu(sf::RenderWindow &window, sf::Vector2i &mouse);
	virtual void displayMenu01(sf::RenderWindow &window);
	virtual void moveUp();
	virtual void moveDown();
	virtual void scale(sf::RenderWindow &window);
protected:
	static int const mNumberOfSelections = 5;

private:
	sf::IntRect *mRects[mNumberOfSelections];
	sf::Vector2i mMouse;
	int mState;
	int mTimer;
	int selectedIndex;
	sf::Font font;
	sf::Text menu[mNumberOfSelections];

	virtual void setTextures(); //Set a texture to a sprite
	virtual void setFonts();
	//flaggor för keypress
	bool mReturn = false;
	bool mDown = false;
	bool mUp = false;
};


#endif