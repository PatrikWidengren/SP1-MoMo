#ifndef INGAMEMENU
#define INGAMEMENU

#include "menu.h"

class inGameMenu :
	public Menu
{
public:
	inGameMenu(float width, float height);
	~inGameMenu();

	// Load a backgrounds to show for the menu
	sf::Texture* highlighttextBg01 = new sf::Texture(); //the highlightTexture for displaying.
	sf::Texture* textBg01 = new sf::Texture(); //hold the texture

	sf::Texture* textResume = new sf::Texture();
	sf::Texture* textOption = new sf::Texture();
	sf::Texture* textQuit = new sf::Texture();

	sf::Texture* textHighlightResume = new sf::Texture();
	sf::Texture* textHighlightOption = new sf::Texture();
	sf::Texture* textHighlightQuit = new sf::Texture();

	sf::Sprite* spriteResume = new sf::Sprite();
	sf::Sprite* spriteOption = new sf::Sprite();
	sf::Sprite* spriteQuit = new sf::Sprite();

	sf::Sprite* bg01 = new sf::Sprite(); //Drawable sprite wich gets a texture later. Bg stands for background
	sf::Sprite* highlightSprite01 = new sf::Sprite(); //when you hover, or select. the alternative brightens upp.

	virtual int checkState();
	virtual void updateInGameMenu(sf::RenderWindow &window, sf::Vector2i &mouse, SoundManager &sound);
	virtual void displayMenu01(sf::RenderWindow &window);
	virtual void moveUp();
	virtual void moveDown();
	virtual void scale(sf::RenderWindow &window);
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
	//flaggor för keypress
	bool mReturn = false;
	bool mDown = false;
	bool mUp = false;
};

#endif