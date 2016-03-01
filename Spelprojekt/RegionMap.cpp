#include "RegionMap.h"

RegionMap::RegionMap(float width, float height)
{
	highlightSprite01.setPosition(10, 235);
	mTimer = 0;
	mState = 8;
	mInternalState = 0;
	mRegionState = 0;
	setFonts();
	setTextures();

	spriteShop.setPosition(0, 780);

	mRects[0] = new sf::IntRect(sf::Vector2i(360, 295), sf::Vector2i(410, 200));
	mRects[1] = new sf::IntRect(sf::Vector2i(925, 300), sf::Vector2i(395, 200));
	mRects[2] = new sf::IntRect(sf::Vector2i(1660, 75), sf::Vector2i(180, 145));

	mRects[3] = new sf::IntRect(sf::Vector2i(85, 850), sf::Vector2i(116, 173));
	mRects[4] = new sf::IntRect(sf::Vector2i(285, 850), sf::Vector2i(116, 180));
	mRects[5] = new sf::IntRect(sf::Vector2i(575, 850), sf::Vector2i(116, 173));
	mRects[6] = new sf::IntRect(sf::Vector2i(775, 850), sf::Vector2i(116, 180));

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

	/*if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mClick) {
		mClick = true;
	}*/

	std::cout << mMouse.x << ": 1 :" << mMouse.y << std::endl;
	//std::cout << highlightSprite01.getPosition().x << ": RegionMap :" << highlightSprite01.getPosition().y << std::endl;


	if (mRects[0]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
	{
		//Set sprite to highlight texture

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick)
		{
			mClick = false;
			changeInternalState(1);
			reset = true;
		}
	}
	else
		//set sprite to regular texture

		if (mRects[1]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
		{
			//Set sprite to highlight texture
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick)
			{
				mClick = false;
				changeInternalState(2);
				reset = true;
			}
		}
		else
			//set sprite to regular texture

			if (mRects[2]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
			{
				//Set sprite to highlight texture
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick)
				{
					mClick = false;
					if (mInternalState == 0) {
						window.close();
					}
					else {
						changeInternalState(0);
					}
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

		spriteShop.setScale((float)window.getSize().x / 1920, (float)window.getSize().y / 1080);

		mRects[0] = new sf::IntRect(sf::Vector2i(360 * bg01.getScale().x, 295 * bg01.getScale().y), sf::Vector2i(410 * bg01.getScale().x, 200 * bg01.getScale().y));
		mRects[1] = new sf::IntRect(sf::Vector2i(925 * bg01.getScale().x, 300 * bg01.getScale().y), sf::Vector2i(395 * bg01.getScale().x, 200 * bg01.getScale().y));
		mRects[2] = new sf::IntRect(sf::Vector2i(1660 * bg01.getScale().x, 75 * bg01.getScale().y), sf::Vector2i(180 * bg01.getScale().x, 145 * bg01.getScale().y));

		if (mInternalState == 1) {
			spriteShop.setPosition(0 * bg01.getScale().x, 780 * bg01.getScale().y);
		}
		else {
			spriteShop.setPosition(0 * bg01.getScale().x, 1080 * bg01.getScale().y);
		}
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

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mClick) {
		mClick = true;
	}

}

void RegionMap::displayMenu01(sf::RenderWindow &window)
{
	window.draw(bg01);
	window.draw(spriteShop);
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
	if (!textureShop.loadFromFile("Resource Files/Menus/Shop_temp.png"))
		textureShop.loadFromFile("error.jpg");


	//if (!highlightTexture01.loadFromFile("temiu.png")) //try to load the texture. if its wrong, give error
	//	highlightTexture01.loadFromFile("error.jpg");

	bg01.setTexture(texture01);
	spriteShop.setTexture(textureShop);
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

int RegionMap::checkRegionState() {
	return mRegionState;
}

void RegionMap::changeInternalState(int newState) {
	if (mInternalState != newState) {
		switch (mInternalState) {
		case 0:
			switch (newState) {
			case 1:
				spriteShop.move(0 * bg01.getScale().x, -300 * bg01.getScale().y);
				mInternalState = newState;
				break;
			case 2:
				mInternalState = newState;
				break;
			}
			break;
		case 1:
			switch (newState) {
			case 0:
				spriteShop.move(0 * bg01.getScale().x, 300 * bg01.getScale().y);
				mInternalState = newState;
				break;
			case 2:
				spriteShop.move(0 * bg01.getScale().x, 300 * bg01.getScale().y);
				mInternalState = newState;
				break;
			}
			break;

		case 2:
			switch (newState) {
			case 0:
				mInternalState = newState;
				break;
			case 1:
				spriteShop.move(0 * bg01.getScale().x, -300 * bg01.getScale().y);
				mInternalState = newState;
				break;
			}
			break;

		}
	}
}
