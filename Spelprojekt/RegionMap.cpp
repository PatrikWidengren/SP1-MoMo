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

	spriteShop.setPosition(0, 1080);

	spriteArrow01.setPosition(120, 850);
	spriteArrow01.setScale(-1, 1);
	spriteArrow02.setPosition(285, 850);

	spriteArrow03.setPosition(610, 850);
	spriteArrow03.setScale(-1, 1);
	spriteArrow04.setPosition(775, 850);


	mRects[0] = new sf::IntRect(sf::Vector2i(360, 295), sf::Vector2i(410, 200));
	mRects[1] = new sf::IntRect(sf::Vector2i(925, 300), sf::Vector2i(395, 200));
	mRects[2] = new sf::IntRect(sf::Vector2i(1660, 75), sf::Vector2i(180, 145));

	mRects[3] = new sf::IntRect(sf::Vector2i(3, 850), sf::Vector2i(116, 173));
	mRects[4] = new sf::IntRect(sf::Vector2i(285, 850), sf::Vector2i(116, 180));
	mRects[5] = new sf::IntRect(sf::Vector2i(493, 850), sf::Vector2i(116, 173));
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
	mMouse.x = mouse.x;
	mMouse.y = mouse.y;

	switch (mInternalState) {
	case 0: //nothing visible, yet
		std::cout << "Case 0";

		if (spriteShop.getPosition().y >= 1080 * bg01.getScale().y)
			spriteShop.setPosition(0 * bg01.getScale().x, 1080 * bg01.getScale().y);

		spriteArrow01.setPosition(120 * bg01.getScale().x, 1100 * bg01.getScale().y);
		spriteArrow02.setPosition(285 * bg01.getScale().x, 1100 * bg01.getScale().y);
		spriteArrow03.setPosition(610 * bg01.getScale().x, 1100 * bg01.getScale().y);
		spriteArrow04.setPosition(775 * bg01.getScale().x, 1100 * bg01.getScale().y);

		//spriteArrow01.move
		//spriteArrow02.move
		//spriteArrow03.move
		//spriteArrow04.move

		break;

	case 1: //Level select visible
		std::cout << "Case 1   " << spriteShop.getPosition().y << std::endl;

		//spriteShop.move(0 * bg01.getScale().x, 300 * bg01.getScale().y);

		/*
		spriteArrow01.move
		spriteArrow02.move
		spriteArrow03.move
		spriteArrow04.move
		*/

		if (spriteShop.getPosition().y <= bg01.getScale().y * window.getSize().y )
		{
			spriteShop.move(0 * bg01.getScale().x, 4 * bg01.getScale().y);
			spriteArrow01.move(0 * bg01.getScale().x, 4 * bg01.getScale().y);
			spriteArrow02.move(0 * bg01.getScale().x, 4 * bg01.getScale().y);
			spriteArrow03.move(0 * bg01.getScale().x, 4 * bg01.getScale().y);
			spriteArrow04.move(0 * bg01.getScale().x, 4 * bg01.getScale().y);
	}



		//spriteShop.move(0 * bg01.getScale().x, 300 * bg01.getScale().y);
		break;


	case 2: //Shop visible
		std::cout << "Case 2   " << spriteShop.getPosition().y << std::endl;

		if (spriteShop.getPosition().y >= bg01.getScale().y * window.getSize().y - 300 )
		{
			spriteShop.move(0 * bg01.getScale().x, -4 * bg01.getScale().y);
			spriteArrow01.move(0 * bg01.getScale().x, -4 * bg01.getScale().y);
			spriteArrow02.move(0 * bg01.getScale().x, -4 * bg01.getScale().y);
			spriteArrow03.move(0 * bg01.getScale().x, -4 * bg01.getScale().y);
			spriteArrow04.move(0 * bg01.getScale().x, -4 * bg01.getScale().y);
		}
		//	spriteShop.move(0 * bg01.getScale().x, -300 * bg01.getScale().y);




		break;
	}


	//changeInternalState(mInternalStateSelect);

	if (mRects[0]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
	{
		//Set sprite to highlight texture

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick)
		{
			mClick = false;
			mInternalState = 2;
			reset = true;
		}
	}

		if (mRects[1]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
		{
			//Set sprite to highlight texture
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick)
			{
				mClick = false;
			mInternalState = 1;
				reset = true;
			}
		}

			if (mRects[2]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
			{
				//Set sprite to highlight texture
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick)
				{
					mClick = false;
					window.close();

		}
					reset = true;

				}

#pragma region ArrowRects
	if (mRects[3]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick)
		{
			spriteArrow01.setTexture(textHighlightArrow01);
			mClick = false;
			reset = true;
			}
			else
			spriteArrow01.setTexture(textArrow01);
	}



	if (mRects[4]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
				{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick)
		{
			spriteArrow02.setTexture(textHighlightArrow01);
			mClick = false;
			reset = true;
				}
		else
			spriteArrow02.setTexture(textArrow01);
	}


	if (mRects[5]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick)
		{
			spriteArrow03.setTexture(textHighlightArrow01);
			mClick = false;
			reset = true;
		}
		else
			spriteArrow03.setTexture(textArrow01);

	}


	if (mRects[6]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick)
		{
			spriteArrow04.setTexture(textHighlightArrow01);
			mClick = false;
			reset = true;
		}
		else
			spriteArrow04.setTexture(textArrow01);
	}


#pragma endregion



	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !mReturn)
	{
		mReturn = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !mDown)
	{
		mDown = true;
		//RegionMap::moveDown();

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

	window.draw(spriteArrow01);
	window.draw(spriteArrow02);
	window.draw(spriteArrow03);
	window.draw(spriteArrow04);
}

void RegionMap::setTextures()
{

	if (!texture01.loadFromFile("Resource Files/Backgrounds/garden_01.png")) //try to load the texture. if its wrong, give error
		texture01.loadFromFile("error.jpg");
	if (!textureShop.loadFromFile("Resource Files/Menus/Shop_temp.png"))
		textureShop.loadFromFile("error.jpg");

	if (!textArrow01.loadFromFile("Resource Files/Menus/HUD_Arrow_Right.png"))
		textArrow01.loadFromFile("error.jpg");

	if (!textHighlightArrow01.loadFromFile("Resource Files/Menus/HUD_Arrow_Right_Highlight.png"))
		textHighlightArrow01.loadFromFile("error.jpg");


	//	highlightTexture01.loadFromFile("error.jpg");

		spriteArrow01.setTexture(textArrow01);
	spriteArrow02.setTexture(textArrow01);
	spriteArrow03.setTexture(textArrow01);
	spriteArrow04.setTexture(textArrow01);

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

int RegionMap::checkState() {
	return mState;
}

void RegionMap::scale(sf::RenderWindow &window) {

	mState = 8;

	bg01.setScale((float)window.getSize().x / 1920, (float)window.getSize().y / 1080);

	//(sf::Vector2i(900, 335), sf::Vector2i(75, 25));
	//sf::Vector2i(1635, 780), sf::Vector2i(95, 25)
	mRects[0] = new sf::IntRect(sf::Vector2i(900 * bg01.getScale().x, 335 * bg01.getScale().y), sf::Vector2i(75 * bg01.getScale().x, 25 * bg01.getScale().y));
	mRects[1] = new sf::IntRect(sf::Vector2i(650 * bg01.getScale().x, 740 * bg01.getScale().y), sf::Vector2i(550 * bg01.getScale().x, 100 * bg01.getScale().y));
	mRects[2] = new sf::IntRect(sf::Vector2i(1635 * bg01.getScale().x, 780 * bg01.getScale().y), sf::Vector2i(95 * bg01.getScale().x, 25 * bg01.getScale().y));


}

int RegionMap::checkRegionState() {
	return mRegionState;
}

//void RegionMap::changeInternalState(int newState) {
//
//	if (mInternalState != newState) {
//
//		switch (mInternalState) {
//		case 0: //nothing visible
//			switch (newState) {
//			case 1:
//				if (spriteShop.getPosition().y >= bg01.getScale().y + 300)
//					spriteShop.move(0 * bg01.getScale().x, -100 * bg01.getScale().y);
//
//				//spriteShop.move(0 * bg01.getScale().x, -300 * bg01.getScale().y);
//
//				//spriteArrow01.move
//				//spriteArrow02.move
//				//spriteArrow03.move
//				//spriteArrow04.move
//
//				mInternalState = newState;
//				break;
//			case 2:
//				mInternalState = newState;
//				break;
//			}
//			break;
//		case 1: //Shop visible
//			switch (newState) {
//			case 0:
//				//spriteShop.move(0 * bg01.getScale().x, 300 * bg01.getScale().y);
//
//		/*		spriteArrow01.move
//				spriteArrow02.move
//				spriteArrow03.move
//				spriteArrow04.move*/
//
//				mInternalState = newState;
//				break;
//			case 2:
//				if (spriteShop.getPosition().y >= bg01.getScale().y - 300)
//					spriteShop.move(0 * bg01.getScale().x, 100 * bg01.getScale().y);
//
//				//spriteShop.move(0 * bg01.getScale().x, 300 * bg01.getScale().y);
//				mInternalState = newState;
//				break;
//			}
//			break;
//
//		case 2: //Level select visible
//			switch (newState) {
//			case 0:
//				mInternalState = newState;
//				break;
//			case 1:
//				if (spriteShop.getPosition().y >= bg01.getScale().y + 300)
//					spriteShop.move(0 * bg01.getScale().x, -100 * bg01.getScale().y);
//
//			//	spriteShop.move(0 * bg01.getScale().x, -300 * bg01.getScale().y);
//	/*			spriteArrow01.move
//				spriteArrow02.move
//				spriteArrow03.move
//				spriteArrow04.move*/
//				mInternalState = newState;
//				break;
//			}
//			break;
//
//		}
//	}
//}
