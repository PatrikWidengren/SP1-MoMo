#include "KeyboardOptionMenu.h"

KeyboardOptionMenu::KeyboardOptionMenu(float width, float height)
{
	highlightSprite01.setPosition(10, 235);
	mTimer = 0;
	mState = 4;
	mOptionMenuState = 3;
	setFonts();
	setTextures();

	spriteBack.setPosition(1385, 515);

	selectedIndex = 0;

	mRects[0] = new sf::IntRect(sf::Vector2i(500, 640), sf::Vector2i(550, 100));
	mRects[1] = new sf::IntRect(sf::Vector2i(500, 740), sf::Vector2i(550, 100));
	mRects[2] = new sf::IntRect(sf::Vector2i(1385, 515), sf::Vector2i(113, 91));

}

KeyboardOptionMenu::~KeyboardOptionMenu()
{

}

void KeyboardOptionMenu::updateKeyboardOptionMenu(sf::RenderWindow &window, sf::Vector2i &mouse, SoundManager &sound)
{

	mMouse.x = mouse.x;
	mMouse.y = mouse.y;

	if (mRects[2]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
	{
		spriteBack.setTexture(textHighlightBack);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick)
		{
			mClick = false;
			//Back
			mOptionMenuState = 1;
			sound.playSound(10.1f);
		}
	}
	else
		spriteBack.setTexture(textBack);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !mDown)
	{
		mDown = true;
		KeyboardOptionMenu::moveDown();
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && mDown)
	{
		mDown = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !mUp)
	{
		mUp = true;
		KeyboardOptionMenu::moveUp();
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && mUp)
	{
		mUp = false;
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !mReturn)
	{
		mReturn = true;
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && mReturn)
	{
		mReturn = false;
		if (selectedIndex == 0) {
			mState = 4;
		}
		if (selectedIndex == 1) {
			mState = 4;
		}
		if (selectedIndex == 2) {
			mOptionMenuState = 1;
		}
	}

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mClick) {
		mClick = true;
	}

}

void KeyboardOptionMenu::displayMenu01(sf::RenderWindow &window)
{

	window.draw(mText01);
	window.draw(bg01);
	window.draw(spriteBack);

}

void KeyboardOptionMenu::setTextures()
{
	
	if (!textBg01.loadFromFile("resource Files/Backgrounds/Background_Options.png")) //try to load the texture. if its wrong, give error
		textBg01.loadFromFile("error.jpg");

	if (!textBack.loadFromFile("Resource Files/Menus/BackArrow.png"))
		textBack.loadFromFile("error.jpg");

	if (!textHighlightBack.loadFromFile("Resource Files/Menus/BackArrow_Highlight.png"))
		textHighlightBack.loadFromFile("error.jpg");


	spriteBack.setTexture(textBack);

	bg01.setTexture(textBg01);
	
}

void KeyboardOptionMenu::setFonts()

{
	if (!font.loadFromFile("Resource Files/Fonts/arial.ttf"))
	{
		//handle error
	}
}

void KeyboardOptionMenu::moveUp()
{

}

void KeyboardOptionMenu::moveDown()
{

}


int KeyboardOptionMenu::checkState() {
	return mState;
}

int KeyboardOptionMenu::checkOptionState() {
	return mOptionMenuState;
}

void KeyboardOptionMenu::scale(sf::RenderWindow &window) {

	mState = 4;
	mOptionMenuState = 3;

	bg01.setScale((float)window.getSize().x / 1920, (float)window.getSize().y / 1080);

	spriteBack.setScale((float)window.getSize().x / 1920, (float)window.getSize().y / 1080);

	mRects[0] = new sf::IntRect(sf::Vector2i(500 * bg01.getScale().x, 640 * bg01.getScale().y), sf::Vector2i(550 * bg01.getScale().x, 100 * bg01.getScale().y));
	mRects[1] = new sf::IntRect(sf::Vector2i(500 * bg01.getScale().x, 740 * bg01.getScale().y), sf::Vector2i(550 * bg01.getScale().x, 100 * bg01.getScale().y));
	mRects[2] = new sf::IntRect(sf::Vector2i(1385 * bg01.getScale().x, 515 * bg01.getScale().y), sf::Vector2i(113 * bg01.getScale().x, 91 * bg01.getScale().y));

	spriteBack.setPosition(1385 * bg01.getScale().x, 515 * bg01.getScale().y);

}
