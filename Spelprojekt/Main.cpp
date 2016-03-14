#include <SFML/Graphics.hpp>
#include <Thor/Animations.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "gameState.h"
#include "Managers/MusicManager.h"
#include "Managers/SoundManager.h"
#include "Managers/AnimeManager.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main(){

	sf::Texture titleTexture;
	sf::Sprite titleScreen;
	titleTexture.loadFromFile("Resource Files/Backgrounds/Loading_Screen.png");
	titleTexture.setSmooth(true);
	titleScreen.setTexture(titleTexture);

	sf::RenderWindow window(sf::VideoMode
		(sf::VideoMode::getDesktopMode().width, 
			sf::VideoMode::getDesktopMode().height, 
			sf::VideoMode::getDesktopMode().bitsPerPixel), 
		"Mow Flow"/*, sf::Style::Fullscreen*/);

	titleScreen.setScale((float)window.getSize().x / 1920, (float)window.getSize().y / 1080);
	
	MusicManager mMusicManager(0);
	window.draw(titleScreen);
	window.display();

	sf::Vector2i mouse;
	AnimeManager mAnimeManager;
	SoundManager mSoundManager;
	gameState theGame(window);

	while (window.isOpen()){
		sf::Event event;
		window.setFramerateLimit(60);
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed){
				mSoundManager.~SoundManager();
				mMusicManager.~MusicManager();
				theGame.~gameState();
				window.close();
			}
			else if (event.type == sf::Event::Resized)
			{
				window.setView(sf::View(sf::FloatRect(0, 0, (float)event.size.width, (float)event.size.height)));
			}
		}
		mouse = sf::Mouse::getPosition(window);
		window.clear();
		theGame.gameStatesHandler(window, mouse, mMusicManager, mSoundManager, mAnimeManager);
		window.display();
	}
	return 0;
}

