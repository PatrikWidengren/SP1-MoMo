#ifndef SOUNDMENU
#define SOUNDMENU

#include "menu.h"
#include "..\..\Managers\SoundManager.h"
#include "..\..\Managers\MusicManager.h"

class SoundMenu : public Menu
{
public:
	SoundMenu(float width, float height);
	~SoundMenu();

	// Load a backgrounds to show for the menu
	sf::Texture* highlighttextBg01 = new sf::Texture; //the highlightTexture for displaying.
	sf::Texture* textBg01 = new sf::Texture; //hold the texture

	sf::Texture* textBack = new sf::Texture;

	sf::Texture* textHighlightBack = new sf::Texture;

	sf::Sprite* spriteBack = new sf::Sprite;

	sf::Sprite* bg01 = new sf::Sprite; //Drawable sprite wich gets a texture later. Bg stands for background
	sf::Sprite* highlightSprite01 = new sf::Sprite; //when you hover, or select. the alternative brightens upp.

	virtual int checkState();
	virtual void updateSoundMenu(sf::RenderWindow &window, sf::Vector2i &mouse, SoundManager &sound);
	virtual void displayMenu01(sf::RenderWindow &window);
	virtual void moveUp();
	virtual void moveDown();
	virtual void scale(sf::RenderWindow &window);
	sf::Vector2i mMouse;

	int checkOptionState();

protected:
	static int const mNumberOfSelections = 3;

private:
	sf::IntRect *mRects[mNumberOfSelections];
	int mOptionMenuState;
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