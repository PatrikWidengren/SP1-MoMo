#include <SFML/Graphics.hpp> 
#include <vector>
#include "gameState.h"
#include "MusicManager.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
static int const windowWidth = 1280;
static int const windowHeigth = 720;

int main(){
	
	MusicManager mMusicManager(0);

	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeigth), "garden");
	sf::Vector2i mouse;

	gameState theGame(window);
	mMusicManager.getMusic()->play();

	while (window.isOpen()){
		sf::Event event;
		window.setFramerateLimit(60);
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed){
			//delete &theGame;
			//delete &mMusicManager;
				window.close();
			}
		}

		window.clear();

		theGame.gameStatesHandler(window, mouse);
		
		window.display();
	}
	return 0;
}

