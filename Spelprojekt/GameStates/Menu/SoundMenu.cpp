#include "SoundMenu.h"

SoundMenu::SoundMenu(float width, float height)
{
	highlightSprite01->setPosition(10, 235);
	mTimer = 0;
	mState = 4;
	mOptionMenuState = 2;
	setFonts();
	setTextures();

	spriteBack->setPosition(1385, 515);


	menu[0].setFont(font);
	menu[0].setColor(sf::Color::Red);
	menu[0].setString("Sound Settings");
	menu[0].setPosition(sf::Vector2f(width / 2, height / (mNumberOfSelections + 1) * 1));

	menu[1].setFont(font);
	menu[1].setColor(sf::Color::White);
	menu[1].setString("More Sound Settings");
	menu[1].setPosition(sf::Vector2f(width / 2, height / (mNumberOfSelections + 1) * 2));

	menu[2].setFont(font);
	menu[2].setColor(sf::Color::White);
	menu[2].setString("Back To Options");
	menu[2].setPosition(sf::Vector2f(width / 2, height / (mNumberOfSelections + 1) * 3));

	selectedIndex = 0;

	mRects[0] = new sf::IntRect(sf::Vector2i(500, 640), sf::Vector2i(550, 100));
	mRects[1] = new sf::IntRect(sf::Vector2i(500, 740), sf::Vector2i(550, 100));
	mRects[2] = new sf::IntRect(sf::Vector2i(1385, 515), sf::Vector2i(113, 91));


}

SoundMenu::~SoundMenu()
{

}

void SoundMenu::updateSoundMenu(sf::RenderWindow &window, sf::Vector2i &mouse, SoundManager &sound, MusicManager &music)
{

	mMouse.x = mouse.x;
	mMouse.y = mouse.y;
	std::cout << mMouse.x << ": 1 :" << mMouse.y << std::endl;

	/*if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mClick) {
		mClick = true;
	}*/

	if (mRects[2]->contains(sf::Vector2i(mMouse.x, mMouse.y)))
	{
		spriteBack->setTexture(*textHighlightBack);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick)
		{
			//Back
			mClick = false;
			mOptionMenuState = 1;
			sound.playSound(10.1);
		}
	}
	else
		spriteBack->setTexture(*textBack);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !mDown)
	{
		mDown = true;
		sound.setVolume(sound.getVolume() - 5);
		music.setVolume(music.getVolume() - 5);
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && mDown)
	{
		mDown = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !mUp)
	{
		mUp = true;
		sound.setVolume(sound.getVolume() + 5);
		music.setVolume(music.getVolume() + 5);
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
			mState = 4; //change sound settings
		}
		if (selectedIndex == 1) {
			mState = 4; //change sound settings
		}
		if (selectedIndex == 2) {
			mOptionMenuState = 1;
		}
	}

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mClick) {
		mClick = true;
	}

}

void SoundMenu::displayMenu01(sf::RenderWindow &window)
{

	for (int i = 0; i < mNumberOfSelections; i++)
	{
		window.draw(menu[i]);
	}

	window.draw(*bg01);
	window.draw(*spriteBack);

	//std::cout << mMouse.x << ": 1 :" << mMouse.y << std::endl;
	//std::cout << highlightSprite01.getPosition().x << ": SoundMenu :" << highlightSprite01.getPosition().y << std::endl;

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

void SoundMenu::setTextures()
{
	
	if (!textBg01->loadFromFile("Resource Files/Backgrounds/Background_Options.png")) //try to load the texture. if its wrong, give error
	textBg01->loadFromFile("error.jpg");

	if (!highlighttextBg01->loadFromFile("temiu.png")) //try to load the texture. if its wrong, give error
	highlighttextBg01->loadFromFile("error.jpg");

	if (!textBack->loadFromFile("Resource Files/Menus/BackArrow.png"))
		textBack->loadFromFile("error.jpg");

	if (!textHighlightBack->loadFromFile("Resource Files/Menus/BackArrow_Highlight.png"))
		textHighlightBack->loadFromFile("error.jpg");



	spriteBack->setTexture(*textBack);
	bg01->setTexture(*textBg01);
	highlightSprite01->setTexture(*highlighttextBg01);
	
}

void SoundMenu::setFonts()

{
	if (!font.loadFromFile("Resource Files/Fonts/arial.ttf"))
	{
		//handle error
	}
}

void SoundMenu::moveUp()
{
	if (selectedIndex - 1 >= 0)
	{
		menu[selectedIndex].setColor(sf::Color::White);
		selectedIndex--;
		menu[selectedIndex].setColor(sf::Color::Red);
	}
}

void SoundMenu::moveDown()
{
	if (selectedIndex + 1 < mNumberOfSelections)
	{
		menu[selectedIndex].setColor(sf::Color::White);
		selectedIndex++;
		menu[selectedIndex].setColor(sf::Color::Red);
	}

}


int SoundMenu::checkState() {
	return mState;
}


int SoundMenu::checkOptionState(){
	return mOptionMenuState;
}

void SoundMenu::scale(sf::RenderWindow &window) {

	mState = 4;
	mOptionMenuState = 2;

	bg01->setScale((float)window.getSize().x / 1920, (float)window.getSize().y / 1080);

	spriteBack->setScale((float)window.getSize().x / 1920, (float)window.getSize().y / 1080);

	mRects[0] = new sf::IntRect(sf::Vector2i(500 * bg01->getScale().x, 640 * bg01->getScale().y), sf::Vector2i(550 * bg01->getScale().x, 100 * bg01->getScale().y));
	mRects[1] = new sf::IntRect(sf::Vector2i(500 * bg01->getScale().x, 740 * bg01->getScale().y), sf::Vector2i(550 * bg01->getScale().x, 100 * bg01->getScale().y));
	mRects[2] = new sf::IntRect(sf::Vector2i(1385 * bg01->getScale().x, 515 * bg01->getScale().y), sf::Vector2i(113 * bg01->getScale().x, 91 * bg01->getScale().y));

	spriteBack->setPosition(1385 * bg01->getScale().x, 515 * bg01->getScale().y);

}

