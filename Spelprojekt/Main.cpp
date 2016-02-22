#include <SFML/Graphics.hpp> 
#include <vector>
#include "gameState.h"
#include "MusicManager.h"
#include "SoundManager.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
static int const windowWidth = 1920;
static int const windowHeigth = 1080;

int main(){
	
	MusicManager mMusicManager(0);
	SoundManager mSoundManager;

	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeigth), "garden");
	sf::Vector2i mouse;

	gameState theGame(window);
	//mMusicManager.getMusic()->play();
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
				window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
			}
		}
		mouse = sf::Mouse::getPosition(window);
		window.clear();
		
		theGame.gameStatesHandler(window, mouse, mMusicManager, mSoundManager);
		
		window.display();
	}
	return 0;
}

