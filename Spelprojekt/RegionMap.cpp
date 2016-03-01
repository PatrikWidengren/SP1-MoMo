#include "RegionMap.h"

RegionMap::RegionMap(float width, float height)
{
	highlightSprite01.setPosition(10, 235);
	mTimer = 0;
	mState = 8;
	setFonts();
	setTextures();

	mRects[0] = new sf::IntRect(sf::Vector2i(360, 295), sf::Vector2i(410, 200));
	mRects[1] = new sf::IntRect(sf::Vector2i(925, 300), sf::Vector2i(395, 200));
	mRects[2] = new sf::IntRect(sf::Vector2i(1660, 75), sf::Vector2i(180, 145));

}

RegionMap::RegionMap()
{

}

RegionMap::~RegionMap()
{

}

void RegionMap::updateRegionMap(sf::RenderWindow &window, sf::Vector2i &mouse)
{
	//std::cout << window.getSize().x << " " << window.getSize().y << " " << mEvent.size.width << " " << mEvent.size.height << std::endl;
	mMouse.x = mouse.x;
	mMouse.y = mouse.y;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mClick) {
		mClick = true;
	}

	std::cout << mMouse.x << ": 1 :" << mMouse.y << std::endl;
	//std::cout << highlightSprite01.getPosition().x << ": RegionMap :" << highlightSprite01.getPosition().y << std::endl;


	if (mRects[0]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
	{
		//Set sprite to highlight texture

		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick)
		{
			mClick = false;
			mState = 1;
			reset = true;
		}
	}
	else
		//set sprite to regular texture

		if (mRects[1]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
		{
			//Set sprite to highlight texture
			if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick)
			{
				mClick = false;
				mState = 4;
				reset = true;
			}
		}
		else
			//set sprite to regular texture

			if (mRects[2]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
			{
				//Set sprite to highlight texture
				if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick)
				{
					mClick = false;
					window.close();
					reset = true;
				}
			}
			else
				//set sprite to regular texture

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !mReturn)
				{
					mReturn = true;
				}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mRects[0]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
	{
		std::cout << "Inside" << " ";
		//window.close();
	}
	if (mRects[0]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
		std::cout << "dasda";


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !mDown)
	{
		mDown = true;
		//RegionMap::moveDown();
		bg01.setScale((float)window.getSize().x / 1920, (float)window.getSize().y / 1080);

		/*	mRects[0] = new sf::IntRect(sf::Vector2i(360, 295), sf::Vector2i(410, 200));
			mRects[1] = new sf::IntRect(sf::Vector2i(925, 300), sf::Vector2i(395, 200));
			mRects[2] = new sf::IntRect(sf::Vector2i(1660, 75), sf::Vector2i(180, 145));
		*/
		mRects[0] = new sf::IntRect(sf::Vector2i(360 * bg01.getScale().x, 295 * bg01.getScale().y), sf::Vector2i(410 * bg01.getScale().x, 200 * bg01.getScale().y));
		mRects[1] = new sf::IntRect(sf::Vector2i(925 * bg01.getScale().x, 300 * bg01.getScale().y), sf::Vector2i(395 * bg01.getScale().x, 200 * bg01.getScale().y));
		mRects[2] = new sf::IntRect(sf::Vector2i(1660 * bg01.getScale().x, 75 * bg01.getScale().y), sf::Vector2i(180 * bg01.getScale().x, 145 * bg01.getScale().y));

	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && mDown)
	{
		mDown = false;
	}

	/*	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !mUp)
	{
	mUp = true;
	RegionMap::moveUp();
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && mUp)
	{
	mUp = false;
	}*/


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !mReturn)
	{
		mReturn = true;
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && mReturn)
	{
		mReturn = false;
		if (selectedIndex == 0) {
			mState = 10;
		}
		if (selectedIndex == 1) {
			mState = 4;
		}
		if (selectedIndex == 2) {
			window.close();
		}
	}

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick) {
		mClick = false;
	}

}

void RegionMap::displayMenu01(sf::RenderWindow &window)
{
	window.draw(bg01);
	/*

	for (int i = 0; i < mNumberOfSelections; i++)
	{
	window.draw(menu[i]);
	}
	*/
}

void RegionMap::setTextures()
{

	if (!texture01.loadFromFile("Resource Files/Backgrounds/garden_01.png")) //try to load the texture. if its wrong, give error
		texture01.loadFromFile("error.jpg");

	//if (!highlightTexture01.loadFromFile("temiu.png")) //try to load the texture. if its wrong, give error
	//	highlightTexture01.loadFromFile("error.jpg");

	bg01.setTexture(texture01);
	//highlightSprite01.setTexture(highlightTexture01);


}

void RegionMap::setFonts()

{
	if (!font.loadFromFile("Resource Files/Fonts/arial.ttf"))
	{
		//handle error
	}
}

void RegionMap::moveUp()
{
	/*if (selectedIndex - 1 >= 0)
	{
	menu[selectedIndex].setColor(sf::Color::White);
	selectedIndex--;
	menu[selectedIndex].setColor(sf::Color::Red);
	}*/
}

void RegionMap::moveDown()
{
	/*if (selectedIndex + 1 < mNumberOfSelections)
	{
	menu[selectedIndex].setColor(sf::Color::White);
	selectedIndex++;
	menu[selectedIndex].setColor(sf::Color::Red);
	}*/

}

int RegionMap::checkState()
{
	//std::cout << mState << std::endl;
	int i = mState;
	mState = 8;
	return i;
}
