#include "ToolSelectMenu.h"

ToolSelectMenu::ToolSelectMenu(float width, float height)
{
	highlightSprite01.setPosition(10, 235);
	mTimer = 0;
	mState = 0;
	setFonts();
	setTextures();
	menu[0].setFont(font);
	menu[0].setColor(sf::Color::Red);
	menu[0].setString("Next Lawnmower");
	menu[0].setPosition(sf::Vector2f(width / 2, height / (mNumberOfSelections + 1) * 1));

	menu[1].setFont(font);
	menu[1].setColor(sf::Color::White);
	menu[1].setString("Next Hedge cutter");
	menu[1].setPosition(sf::Vector2f(width / 2, height / (mNumberOfSelections + 1) * 2));

	menu[2].setFont(font);
	menu[2].setColor(sf::Color::White);
	menu[2].setString("Resume");
	menu[2].setPosition(sf::Vector2f(width / 2, height / (mNumberOfSelections + 1) * 3));

	selectedIndex = 0;
}

ToolSelectMenu::~ToolSelectMenu()
{

}

void ToolSelectMenu::updateToolSelectMenu(sf::RenderWindow &window)
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
		if (selectedIndex == 0){
			mState = 8;
		}
		if (selectedIndex == 1){
			mState = 9;
		}
		if (selectedIndex == 2){
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

	window.draw(bg01);
	//std::cout << mMouse.x << ": 1 :" << mMouse.y << std::endl;
	std::cout << highlightSprite01.getPosition().x << ": ToolSelectMenu :" << highlightSprite01.getPosition().y << std::endl;

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

void ToolSelectMenu::setTextures()
{
	if (!texture01.loadFromFile("testmenu.png")) //try to load the texture. if its wrong, give error
		texture01.loadFromFile("error.jpg");

	if (!highlightTexture01.loadFromFile("temiu.png")) //try to load the texture. if its wrong, give error
		highlightTexture01.loadFromFile("error.jpg");

	bg01.setTexture(texture01);
	highlightSprite01.setTexture(highlightTexture01);
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
	if (selectedIndex - 1 >= 0)
	{
		menu[selectedIndex].setColor(sf::Color::White);
		selectedIndex--;
		menu[selectedIndex].setColor(sf::Color::Red);
	}
}

void ToolSelectMenu::moveDown()
{
	if (selectedIndex + 1 < mNumberOfSelections)
	{
		menu[selectedIndex].setColor(sf::Color::White);
		selectedIndex++;
		menu[selectedIndex].setColor(sf::Color::Red);
	}

}

int ToolSelectMenu::checkState()
{
	std::cout << mState << std::endl;
	int i = mState;
	mState = 0;
	return i;
}
