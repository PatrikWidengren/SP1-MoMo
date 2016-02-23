#include "optionMenu.h"

optionMenu::optionMenu(float width, float height)
{
	highlightSprite01.setPosition(1400, 718);
	mTimer = 0;
	mState = 4;
	mOptionMenuState = 1;
	setFonts();
	setTextures();
	/*

	menu[0].setFont(font);
	menu[0].setColor(sf::Color::Red);
	menu[0].setString("Sound settings");
	menu[0].setPosition(sf::Vector2f(width / 2, height / (mNumberOfSelections + 1) * 1));

	menu[1].setFont(font);
	menu[1].setColor(sf::Color::White);
	menu[1].setString("Keyboard settings");
	menu[1].setPosition(sf::Vector2f(width / 2, height / (mNumberOfSelections + 1) * 2));

	menu[2].setFont(font);
	menu[2].setColor(sf::Color::White);
	menu[2].setString("Back");
	menu[2].setPosition(sf::Vector2f(width / 2, height / (mNumberOfSelections + 1) * 3));
	*/
	selectedIndex = 0;

	mRects[0] = new sf::IntRect(sf::Vector2i(500, 640), sf::Vector2i(550, 100));
	mRects[1] = new sf::IntRect(sf::Vector2i(500, 740), sf::Vector2i(550, 100));
	mRects[2] = new sf::IntRect(sf::Vector2i(1750, 35), sf::Vector2i(115, 95));
	mRects[3] = new sf::IntRect(sf::Vector2i(1375, 504), sf::Vector2i(113, 91));

}

optionMenu::~optionMenu()
{

}

void optionMenu::updateoptionMenu(sf::RenderWindow &window, sf::Vector2i &mouse)
{
	mMouse.x = mouse.x;
	mMouse.y = mouse.y;
	std::cout << mMouse.x << ": 1 :" << mMouse.y << std::endl;

	/*
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mRects[0]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
	{
	mState = 1;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mRects[1]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
	{
	mState = 4;
	}
	*/
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mRects[2]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
	{
		window.close();
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mRects[3]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
	{
		mState = 3;
	}

	if (mMouse.x <= maxX && mMouse.x >= minX && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		highlightSprite01.setPosition(mMouse.x - 32, 718);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !mDown)
	{
		
		mRects[0] = new sf::IntRect(sf::Vector2i(500 * bg01.getScale().x, 640 * bg01.getScale().y), sf::Vector2i(550 * bg01.getScale().x, 100 * bg01.getScale().y));
		mRects[1] = new sf::IntRect(sf::Vector2i(500 * bg01.getScale().x, 740 * bg01.getScale().y), sf::Vector2i(550 * bg01.getScale().x, 100 * bg01.getScale().y));
		mRects[2] = new sf::IntRect(sf::Vector2i(1750 * bg01.getScale().x, 35 * bg01.getScale().y), sf::Vector2i(115 * bg01.getScale().x, 95 * bg01.getScale().y));
		mRects[3] = new sf::IntRect(sf::Vector2i(1375 * bg01.getScale().x, 504 * bg01.getScale().y), sf::Vector2i(113 * bg01.getScale().x, 91 * bg01.getScale().y));

		bg01.setScale((float)window.getSize().x / 1920, (float)window.getSize().y / 1080);

		mDown = true;
		optionMenu::moveDown();
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && mDown)
	{
		mDown = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !mUp)
	{
		mUp = true;
		optionMenu::moveUp();
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
			mOptionMenuState = 2;
		}
		if (selectedIndex == 1) {
			mOptionMenuState = 3;
		}
		if (selectedIndex == 2) {
			mState = 3;
		}
	}
}

void optionMenu::displayMenu01(sf::RenderWindow &window)
{
	window.draw(bg01);
	window.draw(highlightSprite01);
	/*

	for (int i = 0; i < mNumberOfSelections; i++)
	{
		window.draw(menu[i]);
	}
	*/

	//std::cout << mMouse.x << ": 1 :" << mMouse.y << std::endl;
	//std::cout << highlightSprite01.getPosition().x << ": optionMenu :" << highlightSprite01.getPosition().y << std::endl;

}

void optionMenu::setTextures()
{
	if (!sliderTextuer01.loadFromFile("Resource Files/Sprites/slider_button.png")) //try to load the texture. if its wrong, give error
		sliderTextuer01.loadFromFile("error.jpg");

	if (!texture01.loadFromFile("Resource Files/Backgrounds/start_menu_options_1.png")) //try to load the texture. if its wrong, give error
		texture01.loadFromFile("error.jpg");

	if (!highlightTexture01.loadFromFile("Resource Files/Sprites/cat.png")) //try to load the texture. if its wrong, give error
		highlightTexture01.loadFromFile("error.jpg");

	slider01.setTexture(sliderTextuer01);
	bg01.setTexture(texture01);
	highlightSprite01.setTexture(highlightTexture01);


}
void optionMenu::setFonts()

{
	if (!font.loadFromFile("Resource Files/Fonts/arial.ttf"))
	{
		//handle error
	}
}

void optionMenu::moveUp()
{
	if (selectedIndex - 1 >= 0)
	{
		menu[selectedIndex].setColor(sf::Color::White);
		selectedIndex--;
		menu[selectedIndex].setColor(sf::Color::Red);
	}
}

void optionMenu::moveDown()
{
	if (selectedIndex + 1 < mNumberOfSelections)
	{
		menu[selectedIndex].setColor(sf::Color::White);
		selectedIndex++;
		menu[selectedIndex].setColor(sf::Color::Red);
	}

}


int optionMenu::checkState()
{
	//std::cout << mState << std::endl;
	int i = mState;
	mState = 4;
	return i;
}

int optionMenu::checkOptionState()
{
	int i = mOptionMenuState;
	mOptionMenuState = 1;
	return i;
}