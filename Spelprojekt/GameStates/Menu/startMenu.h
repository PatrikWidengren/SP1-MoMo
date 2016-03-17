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
	sf::Texture* highlighttextBg01 = new sf::Texture(); //the highlightTexture for displaying.
	sf::Texture* textBg01 = new sf::Texture(); //hold the texture

	sf::Texture* textContinue = new sf::Texture();
	sf::Texture* textNewgame = new sf::Texture();
	sf::Texture* textOption = new sf::Texture();
	sf::Texture* textCredits = new sf::Texture();
	sf::Texture* textExit = new sf::Texture();

	sf::Texture* textHighlightContinue = new sf::Texture();
	sf::Texture* textHighlightNewgame = new sf::Texture();
	sf::Texture* textHighlightOption = new sf::Texture();
	sf::Texture* textHighlightCredits = new sf::Texture();
	sf::Texture* textHighlightExit = new sf::Texture();

	sf::Texture* textSpinbg = new sf::Texture();

	sf::Sprite* spriteContinue = new sf::Sprite();
	sf::Sprite* spriteNewgame = new sf::Sprite();
	sf::Sprite* spriteOption = new sf::Sprite();
	sf::Sprite* spriteCredits = new sf::Sprite();
	sf::Sprite* spriteExit = new sf::Sprite();

	sf::Sprite* spriteSpinbg = new sf::Sprite();


	sf::Sprite* bg01 = new sf::Sprite(); //Drawable sprite wich gets a texture later. Bg stands for background
	sf::Sprite* highlightSprite01 = new sf::Sprite(); //when you hover, or select. the alternative brightens upp.

	virtual int checkState();
	virtual void updateStartMenu(sf::RenderWindow &window, sf::Vector2i &mouse, SoundManager &sound);
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