#include "inGameMenu.h"

inGameMenu::inGameMenu(float width, float height)
{
	highlightSprite01.setPosition(10, 235);
	mTimer = 0;
	mState = 2;
	setFonts();
	setTextures();
	menu[0].setFont(font);
	menu[0].setColor(sf::Color::Red);
	menu[0].setString("Resume");
	menu[0].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_SELECTIONS + 1) * 1));

	menu[1].setFont(font);
	menu[1].setColor(sf::Color::White);
	menu[1].setString("Options");
	menu[1].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_SELECTIONS + 1) * 2));

	menu[2].setFont(font);
	menu[2].setColor(sf::Color::White);
	menu[2].setString("Exit to main menu");
	menu[2].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_SELECTIONS + 1) * 3));

	selectedIndex = 0;
}

inGameMenu::~inGameMenu()
{
}

void inGameMenu::updateInGameMenu(sf::RenderWindow &window)
{
	mTimer++;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && selectedIndex == 0)
	{
		mState = 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && selectedIndex == 1)
	{
		mState = 4;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && selectedIndex == 2)
	{
		mState = 3;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && mTimer > 20)
	{
		mTimer = 0;

		inGameMenu::moveDown();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && mTimer > 20)
	{
		mTimer = 0;
		inGameMenu::moveUp();
	}
}

void inGameMenu::displayMenu01(sf::RenderWindow &window)
{

	for (int i = 0; i < MAX_NUMBER_OF_SELECTIONS; i++)
	{
		window.draw(menu[i]);
	}

	window.draw(bg01);
	//std::cout << mMouse.x << ": 1 :" << mMouse.y << std::endl;
	std::cout << highlightSprite01.getPosition().x << ": IngameMenu :" << highlightSprite01.getPosition().y << std::endl;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mMouse.x > 10 && mMouse.x < 200 && mMouse.y > 235 && mMouse.y < 365) // left click if its on the option
	{
		window.close();
	}
	if (mMouse.x > highlightSprite01.getPosition().x * highlightSprite01.getScale().x && mMouse.x < highlightSprite01.getPosition().y - 35 && mMouse.y > highlightSprite01.getPosition().y && mMouse.y < highlightSprite01.getPosition().y + 30)
	{
		highlightSprite01.setPosition(10, 235);
		window.draw(highlightSprite01);
	}


}

void inGameMenu::setTextures()
{
	if (!texture01.loadFromFile("testmenu.png")) //try to load the texture. if its wrong, give error
		texture01.loadFromFile("error.jpg");

	if (!highlightTexture01.loadFromFile("temiu.png")) //try to load the texture. if its wrong, give error
		highlightTexture01.loadFromFile("error.jpg");

	bg01.setTexture(texture01);
	highlightSprite01.setTexture(highlightTexture01);
}

void inGameMenu::setFonts()

{
	if (!font.loadFromFile("arial.ttf"))
	{
		//handle error
	}
}

void inGameMenu::moveUp()
{
	if (selectedIndex - 1 >= 0)
	{
		menu[selectedIndex].setColor(sf::Color::White);
		selectedIndex--;
		menu[selectedIndex].setColor(sf::Color::Red);
	}
}

void inGameMenu::moveDown()
{
	if (selectedIndex + 1 < MAX_NUMBER_OF_SELECTIONS)
	{
		menu[selectedIndex].setColor(sf::Color::White);
		selectedIndex++;
		menu[selectedIndex].setColor(sf::Color::Red);
	}

}

int inGameMenu::checkState()
{
	return mState;
}
