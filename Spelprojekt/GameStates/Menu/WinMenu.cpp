#include "WinMenu.h"

WinMenu::WinMenu(float width, float height)
{
	mTimer = 0;
	mState = 6;
	setFonts();
	setTextures();


	selectedIndex = 0;

	mRects[0] = new sf::IntRect(sf::Vector2i(500, 640), sf::Vector2i(550, 100));
	mRects[1] = new sf::IntRect(sf::Vector2i(500, 740), sf::Vector2i(550, 100));

}

WinMenu::~WinMenu()
{
	
	delete highlighttextBg01;
	delete textBg01;

	delete bg01;
	delete highlightSprite01;
}

void WinMenu::updateWinMenu(sf::RenderWindow &window, sf::Vector2i &mouse)
{
	//These are unused as of now, but may become important once a win menu is in place
	/*if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mClick) {
		mClick = true;
	}*/
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick) {
		mClick = false;
	}

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mClick) {
		mClick = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !mDown)
	{
		mDown = true;
		WinMenu::moveDown();
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && mDown)
	{
		mDown = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !mUp)
	{
		mUp = true;
		WinMenu::moveUp();
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
			reset = true;
			mState = 7;
		}
		if (selectedIndex == 1) {
			window.close();
		}
	}
}

void WinMenu::displayMenu01(sf::RenderWindow &window)
{

	blackness.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
	pressEnter.setPosition(sf::Vector2f((window.getSize().x/2) - (pressEnter.getGlobalBounds().width/2), (window.getSize().y/2) - (pressEnter.getGlobalBounds().height)/2));
	blackness.setFillColor(sf::Color(0, 0, 0, 150));
	//pressEnter.setColor(sf::Color(0, 0, 0, 0));
	window.draw(blackness);
	window.draw(pressEnter);
	//window.draw(*bg01);

}

void WinMenu::setTextures()
{
	
	if (!textBg01->loadFromFile("Resource Files/Backgrounds/Background_Title.png")) //try to load the texture. if its wrong, give error
	textBg01->loadFromFile("error.jpg");

	pressEnter.setString("Press Enter to continue");

	bg01->setTexture(*textBg01);
}

void WinMenu::setFonts()

{
	if (!font.loadFromFile("Resource Files/Fonts/arial.ttf"))
	{
		//handle error
	}
	pressEnter.setFont(font);
}

void WinMenu::moveUp()
{

}

void WinMenu::moveDown()
{

}

int WinMenu::checkState() {
	return mState;
}

void WinMenu::scale(sf::RenderWindow &window) {

	mState = 6;

	bg01->setScale((float)window.getSize().x / 1920, (float)window.getSize().y / 1080);

	mRects[0] = new sf::IntRect(sf::Vector2i(500 * bg01->getScale().x, 640 * bg01->getScale().y), sf::Vector2i(550 * bg01->getScale().x, 100 * bg01->getScale().y));
	mRects[1] = new sf::IntRect(sf::Vector2i(500 * bg01->getScale().x, 740 * bg01->getScale().y), sf::Vector2i(550 * bg01->getScale().x, 100 * bg01->getScale().y));

}
