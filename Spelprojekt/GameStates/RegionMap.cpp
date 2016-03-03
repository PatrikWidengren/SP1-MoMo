﻿#include "RegionMap.h"

RegionMap::RegionMap(float width, float height)
{
	highlightSprite01.setPosition(10, 235);
	mTimer = 0;
	mState = 7;
	selectedMow = 0;
	mInternalState = 0;
	mRegionState = 0;

	mRegions[1].BackgroundName = "Resource Files/Backgrounds/Garden_01.png";
	mRegions[1].levelCount = 4;

	mRegions[2].BackgroundName = "Resource Files/Backgrounds/Garden_02.png";
	mRegions[2].levelCount = 7;

	setFonts();
	setTextures();


	spriteShop.setPosition(0, 1080);


	spriteArrow01.setPosition(120, 850);

	spriteMower.setPosition(140, 850);

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

		spriteArrow01.setPosition(120 * bg01.getScale().x, 1120 * bg01.getScale().y);
		spriteArrow02.setPosition(285 * bg01.getScale().x, 1120 * bg01.getScale().y);
		spriteArrow03.setPosition(610 * bg01.getScale().x, 1120 * bg01.getScale().y);
		spriteArrow04.setPosition(775 * bg01.getScale().x, 1120 * bg01.getScale().y);

		spriteMower.setPosition(140 * bg01.getScale().x, 1120 * bg01.getScale().y);

		/*mRects[3] = new sf::IntRect(sf::Vector2i(3 * bg01.getScale().x, 11200 * bg01.getScale().y), sf::Vector2i(116 * bg01.getScale().x, 173 * bg01.getScale().y));
		mRects[4] = new sf::IntRect(sf::Vector2i(285 * bg01.getScale().x, 11200 * bg01.getScale().y), sf::Vector2i(116 * bg01.getScale().x, 180 * bg01.getScale().y));
		mRects[5] = new sf::IntRect(sf::Vector2i(493 * bg01.getScale().x, 11200 * bg01.getScale().y), sf::Vector2i(116 * bg01.getScale().x, 173 * bg01.getScale().y));
		mRects[6] = new sf::IntRect(sf::Vector2i(775 * bg01.getScale().x, 11200 * bg01.getScale().y), sf::Vector2i(116 * bg01.getScale().x, 180 * bg01.getScale().y));
*/
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

		if (spriteShop.getPosition().y < window.getSize().y - 5)
		{
			spriteShop.move(0 * bg01.getScale().x, 5 * bg01.getScale().y);
			spriteArrow01.move(0 * bg01.getScale().x, 5 * bg01.getScale().y);
			spriteArrow02.move(0 * bg01.getScale().x, 5 * bg01.getScale().y);
			spriteArrow03.move(0 * bg01.getScale().x, 5 * bg01.getScale().y);
			spriteArrow04.move(0 * bg01.getScale().x, 5 * bg01.getScale().y);

			spriteMower.move(0 * bg01.getScale().x, 5 * bg01.getScale().y);

			/*mRects[3] = new sf::IntRect(sf::Vector2i(3 * bg01.getScale().x, 11200 * bg01.getScale().y), sf::Vector2i(116 * bg01.getScale().x, 173 * bg01.getScale().y));
			mRects[4] = new sf::IntRect(sf::Vector2i(285 * bg01.getScale().x, 11200 * bg01.getScale().y), sf::Vector2i(116 * bg01.getScale().x, 180 * bg01.getScale().y));
			mRects[5] = new sf::IntRect(sf::Vector2i(493 * bg01.getScale().x, 11200 * bg01.getScale().y), sf::Vector2i(116 * bg01.getScale().x, 173 * bg01.getScale().y));
			mRects[6] = new sf::IntRect(sf::Vector2i(775 * bg01.getScale().x, 11200 * bg01.getScale().y), sf::Vector2i(116 * bg01.getScale().x, 180 * bg01.getScale().y));
*/

		}



		//spriteShop.move(0 * bg01.getScale().x, 300 * bg01.getScale().y);
		break;


	case 2: //Shop visible
		std::cout << "Case 1   " << spriteShop.getPosition().y << std::endl;

		if (spriteShop.getPosition().y >= window.getSize().y - spriteShop.getGlobalBounds().height)
		{
			spriteShop.move(0 * bg01.getScale().x, -5 * bg01.getScale().y);
			spriteArrow01.move(0 * bg01.getScale().x, -5 * bg01.getScale().y);
			spriteArrow02.move(0 * bg01.getScale().x, -5 * bg01.getScale().y);
			spriteArrow03.move(0 * bg01.getScale().x, -5 * bg01.getScale().y);
			spriteArrow04.move(0 * bg01.getScale().x, -5 * bg01.getScale().y);

			spriteMower.move(0 * bg01.getScale().x, -5 * bg01.getScale().y);



		}
		/*mRects[3] = new sf::IntRect(sf::Vector2i(3 * bg01.getScale().x, 11200 * bg01.getScale().y), sf::Vector2i(116 * bg01.getScale().x, 173 * bg01.getScale().y));
		mRects[4] = new sf::IntRect(sf::Vector2i(285 * bg01.getScale().x, 11200 * bg01.getScale().y), sf::Vector2i(116 * bg01.getScale().x, 180 * bg01.getScale().y));
		mRects[5] = new sf::IntRect(sf::Vector2i(493 * bg01.getScale().x, 11200 * bg01.getScale().y), sf::Vector2i(116 * bg01.getScale().x, 173 * bg01.getScale().y));
		mRects[6] = new sf::IntRect(sf::Vector2i(775 * bg01.getScale().x, 11200 * bg01.getScale().y), sf::Vector2i(116 * bg01.getScale().x, 180 * bg01.getScale().y));
*/

		break;
	}


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
			if (mInternalState != 0) {
				mInternalState = 0;
			}
			else {
				mRegionState = 0;
			}

		}
		reset = true;

	}
	std::cout << "levelcount: " << mRegions[mRegionState].levelCount << std::endl;
	for (int i = 0; i < mRegions[mRegionState].levelCount; i++) {
		std::cout << "Checking " << i << std::endl;
		if (mLevelRects[i].contains(sf::Vector2i(mMouse.x, mMouse.y))) {
			std::cout << "It's inside " << i << "!" << std::endl;
		}
	}

#pragma region Old
	//if (mRects[0]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
	//{
	//	//Set sprite to highlight texture

	//	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick)
	//	{
	//		mClick = false;
	//		changeInternalState(1);
	//		reset = true;
	//	}
	//}
	//else
	//	//set sprite to regular texture

	//	if (mRects[1]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
	//	{
	//		//Set sprite to highlight texture
	//		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick)
	//		{
	//			mClick = false;
	//			changeInternalState(2);
	//			reset = true;
	//		}
	//	}
	//	else
	//		//set sprite to regular texture

	//		if (mRects[2]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
	//		{
	//			//Set sprite to highlight texture
	//			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick)
	//			{
	//				mClick = false;
	//				if (mInternalState == 0) {
	//					//window.close();
	//					mRegionState = 0;
	//				}
	//				else {
	//					changeInternalState(0);
	//				}
	//				reset = true;
	//			}
	//		}
	//		else
	//			//set sprite to regular texture


#pragma endregion

#pragma region ArrowRects
	if (mRects[3]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick)
		{
			spriteArrow01.setTexture(textHighlightArrow01);
			mClick = false;
			reset = true;
			if (selectedMow >= 1)
			{
				selectedMow--;
			}
			spriteMower.setTexture(textMowers[selectedMow]);

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
			if (selectedMow < 2)
			{
				selectedMow++;
			}
			spriteMower.setTexture(textMowers[selectedMow]);
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
			//if (selectedMow >= 1)
			//{
			//	selectedMow--;
			//}
			//spriteMower.setTexture(textMowers[selectedMow]);
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
			if (selectedMow  < 2)
			{
				selectedMow++;
			}
			spriteMower.setTexture(textMowers[selectedMow]);
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
		std::cout << "bbbbbbbbbbbbbb" << std::endl;

			//RegionMap::moveDown();
			
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
	window.draw(spriteArrow01);
	window.draw(spriteArrow02);
	window.draw(spriteArrow03);
	window.draw(spriteArrow04);
	window.draw(spriteMower);

	/*

	for (int i = 0; i < mNumberOfSelections; i++)
	{
	window.draw(menu[i]);
	}
	*/
}

void RegionMap::setTextures()
{

	/*if (!texture01.loadFromFile("Resource Files/Backgrounds/Garden_02.png")) //try to load the texture. if its wrong, give error
		texture01.loadFromFile("error.jpg");*/

		/*if (!textBackgrounds[mRegionState].loadFromFile(mRegions[mRegionState].BackgroundName)) //try to load the texture. if its wrong, give error
			textBackgrounds[mRegionState].loadFromFile("error.jpg");*/


	for (int i = 0; i < mMaxRegions; i++) {
		if (!textBackgrounds[i].loadFromFile(mRegions[i].BackgroundName)) //try to load the texture. if its wrong, give error
			textBackgrounds[i].loadFromFile("error.jpg");
	}

	if (!textureShop.loadFromFile("Resource Files/Menus/Shop_temp.png"))
		textureShop.loadFromFile("error.jpg");

	if (!textArrow01.loadFromFile("Resource Files/Menus/HUD_Arrow_Right.png"))
		textArrow01.loadFromFile("error.jpg");

	if (!textHighlightArrow01.loadFromFile("Resource Files/Menus/HUD_Arrow_Right_Highlight.png"))
		textHighlightArrow01.loadFromFile("error.jpg");
#pragma region Set Textures Mowers

	if (!textMowers[0].loadFromFile("Resource Files/Sprites/Mowers/mow0.png"))
		textMowers[0].loadFromFile("error.jpg");
	if (!textMowers[1].loadFromFile("Resource Files/Sprites/Mowers/mow1.png"))
		textMowers[1].loadFromFile("error.jpg");
	if (!textMowers[2].loadFromFile("Resource Files/Sprites/Mowers/mow2.png"))
		textMowers[2].loadFromFile("error.jpg");

	spriteMower.setTexture(textMowers[0]);

#pragma endregion

	
	//if (!highlightTexture01.loadFromFile("temiu.png")) //try to load the texture. if its wrong, give error
	//	highlightTexture01.loadFromFile("error.jpg");

	spriteArrow01.setTexture(textArrow01);
	spriteArrow02.setTexture(textArrow01);
	spriteArrow03.setTexture(textArrow01);
	spriteArrow04.setTexture(textArrow01);
	
	bg01.setTexture(textBackgrounds[mRegionState]);
	//bg01.setTexture(texture01);
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
	return mState;
}

int RegionMap::checkRegionState() {
	return mRegionState;
}

void RegionMap::setRegionState(int state) {
	delete[] mLevelRects;
	mRegionState = state;
	bg01.setTexture(textBackgrounds[mRegionState]);
	mLevelRects = new sf::IntRect[mRegions[mRegionState].levelCount];
	for (int i = 0; i < mRegions[mRegionState].levelCount; i++) {
		mLevelRects[i] = sf::IntRect(sf::Vector2i(0, i * 100), sf::Vector2i(200, 100));
	}
}

void RegionMap::scale(sf::RenderWindow &window) {

	mState = 7;

	bg01.setScale((float)window.getSize().x / 1920, (float)window.getSize().y / 1080);

	/*	mRects[0] = new sf::IntRect(sf::Vector2i(360, 295), sf::Vector2i(410, 200));
	mRects[1] = new sf::IntRect(sf::Vector2i(925, 300), sf::Vector2i(395, 200));
	mRects[2] = new sf::IntRect(sf::Vector2i(1660, 75), sf::Vector2i(180, 145));
	*/

	spriteShop.setScale((float)window.getSize().x / 1920, (float)window.getSize().y / 1080);
	spriteMower.setScale((float)window.getSize().x / 1920, (float)window.getSize().y / 1080);
	spriteArrow01.setScale(-(float)window.getSize().x / 1920, (float)window.getSize().y / 1080);
	spriteArrow02.setScale((float)window.getSize().x / 1920, (float)window.getSize().y / 1080);
	spriteArrow03.setScale(-(float)window.getSize().x / 1920, (float)window.getSize().y / 1080);
	spriteArrow04.setScale((float)window.getSize().x / 1920, (float)window.getSize().y / 1080);

	mRects[0] = new sf::IntRect(sf::Vector2i(360 * bg01.getScale().x, 295 * bg01.getScale().y), sf::Vector2i(410 * bg01.getScale().x, 200 * bg01.getScale().y));
	mRects[1] = new sf::IntRect(sf::Vector2i(925 * bg01.getScale().x, 300 * bg01.getScale().y), sf::Vector2i(395 * bg01.getScale().x, 200 * bg01.getScale().y));
	mRects[2] = new sf::IntRect(sf::Vector2i(1660 * bg01.getScale().x, 75 * bg01.getScale().y), sf::Vector2i(180 * bg01.getScale().x, 145 * bg01.getScale().y));
	mRects[3] = new sf::IntRect(sf::Vector2i(3 * bg01.getScale().x, 1120 * bg01.getScale().y), sf::Vector2i(116 * bg01.getScale().x, 173 * bg01.getScale().y));
	mRects[4] = new sf::IntRect(sf::Vector2i(285 * bg01.getScale().x, 1120 * bg01.getScale().y), sf::Vector2i(116 * bg01.getScale().x, 180 * bg01.getScale().y));
	mRects[5] = new sf::IntRect(sf::Vector2i(493 * bg01.getScale().x, 1120 * bg01.getScale().y), sf::Vector2i(116 * bg01.getScale().x, 173 * bg01.getScale().y));
	mRects[6] = new sf::IntRect(sf::Vector2i(775 * bg01.getScale().x, 1120 * bg01.getScale().y), sf::Vector2i(116 * bg01.getScale().x, 180 * bg01.getScale().y));

	if (mInternalState == 1) {
		spriteShop.setPosition(0 * bg01.getScale().x, 780 * bg01.getScale().y);
		spriteMower.setPosition(140 * bg01.getScale().x, 550 * bg01.getScale().y);
		spriteArrow01.setPosition(120 * bg01.getScale().x, 550 * bg01.getScale().y);
		spriteArrow02.setPosition(285 * bg01.getScale().x, 550 * bg01.getScale().y);
		spriteArrow03.setPosition(610 * bg01.getScale().x, 550 * bg01.getScale().y);
		spriteArrow04.setPosition(775 * bg01.getScale().x, 550 * bg01.getScale().y);
	}
	else {
		spriteShop.setPosition(0 * bg01.getScale().x, 1080 * bg01.getScale().y);
		spriteMower.setPosition(140 * bg01.getScale().x, 850 * bg01.getScale().y);
		spriteArrow01.setPosition(120 * bg01.getScale().x, 850 * bg01.getScale().y);
		spriteArrow02.setPosition(285 * bg01.getScale().x, 850 * bg01.getScale().y);
		spriteArrow03.setPosition(610 * bg01.getScale().x, 850 * bg01.getScale().y);
		spriteArrow04.setPosition(775 * bg01.getScale().x, 850 * bg01.getScale().y);
	}

}

//
//void RegionMap::changeInternalState(int newState) {
//	if (mInternalState != newState) {
//		switch (mInternalState) {
//		case 0:
//			switch (newState) {
//			case 1:
//				spriteShop.move(0 * bg01.getScale().x, -300 * bg01.getScale().y);
//				mInternalState = newState;
//				break;
//			case 2:
//				mInternalState = newState;
//				break;
//			}
//			break;
//		case 1:
//			switch (newState) {
//			case 0:
//				spriteShop.move(0 * bg01.getScale().x, 300 * bg01.getScale().y);
//				mInternalState = newState;
//				break;
//			case 2:
//				spriteShop.move(0 * bg01.getScale().x, 300 * bg01.getScale().y);
//				mInternalState = newState;
//				break;
//			}
//			break;
//
//		case 2:
//			switch (newState) {
//			case 0:
//				mInternalState = newState;
//				break;
//			case 1:
//				spriteShop.move(0 * bg01.getScale().x, -300 * bg01.getScale().y);
//				mInternalState = newState;
//				break;
//			}
//			break;
//
//		}
//	}
//}