#include <SFML/Graphics.hpp> 
#include <vector>
#include "Map1.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
static int const windowWidth = 1280;
static int const windowHeigth = 720;

int main()
{
	typedef vector<StaticObjects*> ObjectsVector;
	ObjectsVector mObjects;
	Player* mPlayer;

	//Skapar instans av "Map1"
	Map1 level("map1.txt");
	//Funktion för att level ska få storleken på arrayen
	level.getArraySize();
	//Anropar funktion för att spawna alla objekt
	level.spawnObjects();

	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeigth), "garden");

	//Kopierar objekten
	mObjects = level.getObjects();
	mPlayer = level.getPlayer();
	// Skriver ut position för alla object
	for (unsigned int i = 0; i < mObjects.size(); i++){
		cout << mObjects[i]->getX() << " " << mObjects[i]->getY() << endl;
	}
	
	int moveMeep = 0;
	bool keyPressed = true;
	bool space = false;
	while (window.isOpen())
	{
		sf::Event event;
		window.setKeyRepeatEnabled(false);
		window.setFramerateLimit(60);
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		//Ritar ut objekten
		for (unsigned int i = 0; i < mObjects.size(); i++){
			window.draw(mObjects[i]->getSprite());
			window.draw(mPlayer->getSprite());
			//mObjects[i]->render();
		}

		level.render();

		//while (keepMoving){
		//	std::cin >> i;
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1)){
			moveMeep = 1;
			keyPressed = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)){
			moveMeep = 2;
			keyPressed = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3)){
			moveMeep = 3;
			keyPressed = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4)){
			moveMeep = 4;
			keyPressed = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5)){
			moveMeep = 5;
			keyPressed = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6)){
			moveMeep = 6;
			keyPressed = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7)){
			moveMeep = 7;
			keyPressed = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8)){
			moveMeep = 8;
			keyPressed = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad9)){
			moveMeep = 9;
			keyPressed = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
			space = true;
		}

		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && space && keyPressed){
			space = false;
			level.takeTurn(moveMeep);
		}

/*		if (moveMeep <= 0 || moveMeep == 5 || moveMeep > 9){
				keepMoving = false;
		}
		else {
			level.takeTurn(moveMeep);
			//level1.printMap();
		}*/
		//}

		
		window.display();
	}
	return 0;
}

