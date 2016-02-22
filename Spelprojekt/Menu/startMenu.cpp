#include "startMenu.h"

startMenu::startMenu(float width, float height)
{
	highlightSprite01.setPosition(10, 235);
	mTimer = 0;
	mState = 3;
	setFonts();
	setTextures();
	menu[0].setFont(font);
	menu[0].setColor(sf::Color::Red);
	menu[0].setString("New Game");
	menu[0].setPosition(sf::Vector2f(width / 2, height / (mNumberOfSelections + 1) * 1));

	mRects[0] = new sf::IntRect(sf::Vector2i(640, 500), sf::Vector2i(500, 100));

	menu[1].setFont(font);
	menu[1].setColor(sf::Color::White);
	menu[1].setString("Options");
	menu[1].setPosition(sf::Vector2f(width / 2, height / (mNumberOfSelections + 1) * 2));

	menu[2].setFont(font);
	menu[2].setColor(sf::Color::White);
	menu[2].setString("Exit to Desktop");
	menu[2].setPosition(sf::Vector2f(width / 2, height / (mNumberOfSelections + 1) * 3));

	selectedIndex = 0;
}

startMenu::startMenu()
{

}

startMenu::~startMenu()
{

}

void startMenu::updateStartMenu(sf::RenderWindow &window, sf::Vector2i &mouse)
{
	//std::cout << window.getSize().x << " " << window.getSize().y << " " << mEvent.size.width << " " << mEvent.size.height << std::endl;
	mMouse.x = mouse.x;
	mMouse.y = mouse.y;

	//std::cout << mMouse.x << ": 1 :" << mMouse.y << std::endl;
	//std::cout << highlightSprite01.getPosition().x << ": StartMenu :" << highlightSprite01.getPosition().y << std::endl;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mMouse.x > 10 && mMouse.x < 200 && mMouse.y > 235 && mMouse.y < 365) // left click if its on the option
	{
	}
	/*if (mMouse.x > highlightSprite01.getPosition().x * highlightSprite01.getScale().x && mMouse.x < highlightSprite01.getPosition().y - 35 && mMouse.y > highlightSprite01.getPosition().y && mMouse.y < highlightSprite01.getPosition().y + 30)
	{
	highlightSprite01.setPosition(10, 235);
	window.draw(highlightSprite01);
	}*/
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !mReturn)
	{
		mReturn = true;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mRects[0]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
	{
		std::cout << "Inside" << " ";
		//window.close();
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !mDown)
	{
		mDown = true;
		startMenu::moveDown();
		bg01.setScale((float)window.getSize().x / 1920, (float)window.getSize().y / 1080);

		mRects[0] = new sf::IntRect(sf::Vector2i(640 * bg01.getScale().x, 500 * bg01.getScale().y), sf::Vector2i(500 * bg01.getScale().x, 100 * bg01.getScale().y));

		//mRects = tempmRects;
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && mDown)
	{
		mDown = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !mUp)
	{
		mUp = true;
		startMenu::moveUp();
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
			reset = true;
			mState = 1;
		}
		if (selectedIndex == 1){
			mState = 4;
		}
		if (selectedIndex == 2){
			window.close();
		}
	}
}

void startMenu::displayMenu01(sf::RenderWindow &window)
{
	window.draw(bg01);
	
	for (int i = 0; i < mNumberOfSelections; i++)
	{
		window.draw(menu[i]);
	}
}

void startMenu::setTextures()
{
	
	if (!texture01.loadFromFile("Resource Files/Backgrounds/start_menu_1.png")) //try to load the texture. if its wrong, give error
		texture01.loadFromFile("error.jpg");

	//if (!highlightTexture01.loadFromFile("temiu.png")) //try to load the texture. if its wrong, give error
	//	highlightTexture01.loadFromFile("error.jpg");

	bg01.setTexture(texture01);
	//highlightSprite01.setTexture(highlightTexture01);
	
	
}

void startMenu::setFonts()

{
	if (!font.loadFromFile("Resource Files/Fonts/arial.ttf"))
	{
		//handle error
	}
}

void startMenu::moveUp()
{
	if (selectedIndex - 1 >= 0)
	{
		menu[selectedIndex].setColor(sf::Color::White);
		selectedIndex--;
		menu[selectedIndex].setColor(sf::Color::Red);
	}
}

void startMenu::moveDown()
{
	if (selectedIndex + 1 < mNumberOfSelections)
	{
		menu[selectedIndex].setColor(sf::Color::White);
		selectedIndex++;
		menu[selectedIndex].setColor(sf::Color::Red);
	}

}

int startMenu::checkState()
{
	//std::cout << mState << std::endl;
	int i = mState;
	mState = 3;
	return i;
}
