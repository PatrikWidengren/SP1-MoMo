#include "ToolSelectMenu.h"

ToolSelectMenu::ToolSelectMenu(float width, float height)
{
	highlightSprite01->setPosition(10, 235);
	mTimer = 0;
	mState = 0;
	setFonts();
	setTextures();

	selectedIndex = 0;

	mRects[0] = new sf::IntRect(sf::Vector2i(500, 640), sf::Vector2i(550, 100));
	mRects[1] = new sf::IntRect(sf::Vector2i(500, 740), sf::Vector2i(550, 100));
	mRects[2] = new sf::IntRect(sf::Vector2i(1750, 35), sf::Vector2i(115, 95));

}

ToolSelectMenu::~ToolSelectMenu()
{
	delete highlighttextBg01;
	delete textBg01;

	delete bg01;
	delete highlightSprite01;
}

void ToolSelectMenu::updateToolSelectMenu(sf::RenderWindow &window, sf::Vector2i &mouse)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !mDown)
	{
		mDown = true;
		moveDown();
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && mDown)
	{
		mDown = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !mUp)
	{
		mUp = true;
		moveUp();
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
			mState = 8;
		}
		if (selectedIndex == 1) {
			mState = 9;
		}
		if (selectedIndex == 2) {
			mState = 1;
		}
	}
}

void ToolSelectMenu::displayMenu01(sf::RenderWindow &window)
{

	for (int i = 0; i < mNumberOfSelections; i++)
	{
		window.draw(menu[i]);
	}

	window.draw(*bg01);
	//std::cout << mMouse.x << ": 1 :" << mMouse.y << std::endl;
	//std::cout << highlightSprite01->getPosition().x << ": ToolSelectMenu :" << highlightSprite01->getPosition().y << std::endl;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mMouse.x > 10 && mMouse.x < 200 && mMouse.y > 235 && mMouse.y < 365) // left click if its on the option
	{
		window.close();
	}
	if (mMouse.x > highlightSprite01->getPosition().x * highlightSprite01->getScale().x && mMouse.x < highlightSprite01->getPosition().y - 35 && mMouse.y > highlightSprite01->getPosition().y && mMouse.y < highlightSprite01->getPosition().y + 30)
	{
		highlightSprite01->setPosition(10, 235);
		window.draw(*highlightSprite01);
	}
}

void ToolSelectMenu::setTextures()
{
	/*
	if (!textBg01.loadFromFile("testmenu.png")) //try to load the texture. if its wrong, give error
	textBg01.loadFromFile("error.jpg");

	if (!highlighttextBg01.loadFromFile("temiu.png")) //try to load the texture. if its wrong, give error
	highlighttextBg01.loadFromFile("error.jpg");

	bg01.setTexture(textBg01);
	highlightSprite01->setTexture(highlighttextBg01);
	*/
}

void ToolSelectMenu::setFonts()

{
	if (!font.loadFromFile("Resource Files/Fonts/arial.ttf"))
	{
		//handle error
	}
}

void ToolSelectMenu::moveUp()
{

}

void ToolSelectMenu::moveDown()
{

}

int ToolSelectMenu::checkState()
{
	//	std::cout << mState << std::endl;
	int i = mState;
	mState = 0;
	return i;
}
