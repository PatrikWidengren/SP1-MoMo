#include "optionMenu.h"

optionMenu::optionMenu(float width, float height)
{
	minSliderX = 956; maxSliderX = 1462;

	mTimer = 0;
	mState = 4;
	mOptionMenuState = 1;
	setFonts();
	setTextures();

	slider01.setPosition(1400, 718);

	spriteControl.setPosition(745, 660);
	spriteVideo.setPosition(786, 780);
	spriteAudio.setPosition(786, 900);
	spriteBack.setPosition(1385, 515);

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

	mRects[0] = new sf::IntRect(sf::Vector2i(730, 650), sf::Vector2i(360, 75));
	mRects[1] = new sf::IntRect(sf::Vector2i(730, 770), sf::Vector2i(360, 75));
	mRects[2] = new sf::IntRect(sf::Vector2i(730, 890), sf::Vector2i(360, 75));
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

	/*if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mClick) {
		mClick = true;
	}*/


	if (mRects[0]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
	{
		spriteControl.setTexture(textHighlightControl);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick)
		{
			mClick = false;
			mOptionMenuState = 3;
		}
	}
	else
		spriteControl.setTexture(textControl);

	if (mRects[1]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
	{
		spriteVideo.setTexture(textHighlightVideo);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick)
		{
			mClick = false;
			//Video Option
		}
	}
	else
		spriteVideo.setTexture(textVideo);

	if (mRects[2]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
	{
		spriteAudio.setTexture(textHighlightAudio);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick)
		{
			mClick = false;
			mOptionMenuState = 2;
			//Audio Option

		}
	}
	else
		spriteAudio.setTexture(textAudio);

	if (mRects[3]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
	{
		spriteBack.setTexture(textHighlightBack);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick)
		{
			//Back
			mClick = false;
			mState = 3;
			mOptionMenuState = 1;
		}
	}
	else
		spriteBack.setTexture(textBack);

	/*if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mRects[4]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
	{
		if (mMouse.x <= maxX && mMouse.x >= minX)
		{
			slider01.setPosition((float)(mMouse.x - 32), (float)718);
		}
	}*/

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !mDown)
	{
		bg01.setScale((float)window.getSize().x / 1920, (float)window.getSize().y / 1080);

		spriteControl.setScale((float)window.getSize().x / 1920, (float)window.getSize().y / 1080);
		spriteVideo.setScale((float)window.getSize().x / 1920, (float)window.getSize().y / 1080);
		spriteAudio.setScale((float)window.getSize().x / 1920, (float)window.getSize().y / 1080);
		spriteBack.setScale((float)window.getSize().x / 1920, (float)window.getSize().y / 1080);

		mRects[0] = new sf::IntRect(sf::Vector2i(745 * bg01.getScale().x, 660 * bg01.getScale().y), sf::Vector2i(360 * bg01.getScale().x, 75 * bg01.getScale().y));
		mRects[1] = new sf::IntRect(sf::Vector2i(786 * bg01.getScale().x, 780 * bg01.getScale().y), sf::Vector2i(360 * bg01.getScale().x, 75 * bg01.getScale().y));
		mRects[2] = new sf::IntRect(sf::Vector2i(786 * bg01.getScale().x, 900 * bg01.getScale().y), sf::Vector2i(360 * bg01.getScale().x, 75 * bg01.getScale().y));
		mRects[3] = new sf::IntRect(sf::Vector2i(1385 * bg01.getScale().x, 515 * bg01.getScale().y), sf::Vector2i(113 * bg01.getScale().x, 91 * bg01.getScale().y));

		spriteControl.setPosition(745 * bg01.getScale().x, 660 * bg01.getScale().y);
		spriteVideo.setPosition(786 * bg01.getScale().x, 780 * bg01.getScale().y);
		spriteAudio.setPosition(786 * bg01.getScale().x, 900 * bg01.getScale().y);
		spriteBack.setPosition(1385 * bg01.getScale().x, 515 * bg01.getScale().y);

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

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mClick) {
		mClick = true;
	}

}

void optionMenu::displayMenu01(sf::RenderWindow &window)
{
	window.draw(bg01);

	window.draw(spriteControl);
	window.draw(spriteAudio);
	window.draw(spriteVideo);
	window.draw(spriteBack);

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

	if (!textBg01.loadFromFile("Resource Files/Backgrounds/Background_Options.png")) //try to load the texture. if its wrong, give error
		textBg01.loadFromFile("error.jpg");

	if (!textControl.loadFromFile("Resource Files/Menus/Controls_Small.png"))
		textControl.loadFromFile("error.jpg");
	if (!textAudio.loadFromFile("Resource Files/Menus/Audio_Small.png"))
		textAudio.loadFromFile("error.jpg");
	if (!textVideo.loadFromFile("Resource Files/Menus/Video_Small.png"))
		textVideo.loadFromFile("error.jpg");
	if (!textBack.loadFromFile("Resource Files/Menus/BackArrow.png"))
		textBack.loadFromFile("error.jpg");

	if (!textHighlightControl.loadFromFile("Resource Files/Menus/Controls_Small_Highlight.png"))
		textHighlightControl.loadFromFile("error.jpg");
	if (!textHighlightAudio.loadFromFile("Resource Files/Menus/Audio_Small_highlight.png"))
		textHighlightAudio.loadFromFile("error.jpg");
	if (!textHighlightVideo.loadFromFile("Resource Files/Menus/Video_Small_Highlight.png"))
		textHighlightVideo.loadFromFile("error.jpg");
	if (!textHighlightBack.loadFromFile("Resource Files/Menus/BackArrow_Highlight.png"))
		textHighlightBack.loadFromFile("error.jpg");


	spriteControl.setTexture(textControl);
	spriteAudio.setTexture(textAudio);
	spriteVideo.setTexture(textVideo);
	spriteBack.setTexture(textBack);

	bg01.setTexture(textBg01);


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