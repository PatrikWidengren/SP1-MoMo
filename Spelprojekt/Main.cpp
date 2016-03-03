#include <SFML/Graphics.hpp>
#include <Thor/Animations.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "gameState.h"
#include "Managers/MusicManager.h"
#include "Managers/SoundManager.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
//static int const windowWidth = 1920;
//static int const windowHeigth = 1080;

int main(){

	sf::Texture titleTexture;
	sf::Sprite titleScreen;
	titleTexture.loadFromFile("Resource Files/Backgrounds/Background_Title.png");
	titleScreen.setTexture(titleTexture);

	sf::RenderWindow window(sf::VideoMode
		(sf::VideoMode::getDesktopMode().width, 
			sf::VideoMode::getDesktopMode().height, 
			sf::VideoMode::getDesktopMode().bitsPerPixel), 
		"garden"/*, sf::Style::Fullscreen*/);

	titleScreen.setScale((float)window.getSize().x / 1920, (float)window.getSize().y / 1080);
	
	MusicManager mMusicManager(0);
	window.draw(titleScreen);
	window.display();

	sf::Vector2i mouse;
	SoundManager mSoundManager;
	gameState theGame(window);

	while (window.isOpen()){
		sf::Event event;
		window.setFramerateLimit(60);
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed){
			//delete &theGame;
			//delete &mMusicManager;
				window.close();
			}
			else if (event.type == sf::Event::Resized)
			{
				window.setView(sf::View(sf::FloatRect(0, 0, (float)event.size.width, (float)event.size.height)));
			}
		}
		mouse = sf::Mouse::getPosition(window);
		theGame.gameStatesHandler(window, mouse, mMusicManager, mSoundManager);
		//cout << theGame.mState << "     " <<  theGame.mOptionMenu01->checkOptionState() << endl;
		window.display();
	}
	return 0;
}

