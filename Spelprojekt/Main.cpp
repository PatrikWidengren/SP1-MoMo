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
	typedef vector<Character*> NpcVector;
	NpcVector mNpcs;
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
	mNpcs = level.getNpcs();
	// Skriver ut position för alla object
	for (ObjectsVector::size_type i = 0; i < mObjects.size(); i++){
		cout << mObjects[i]->getX() << " " << mObjects[i]->getY() << endl;
	}
	int moveMeep = 0;
	bool keyPressed = false;
	bool space = false;
	while (window.isOpen())
	{
		sf::Event event;
		window.setFramerateLimit(60);
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		//Ritar ut objekten
		for (ObjectsVector::size_type i = 0; i < mObjects.size(); i++){
			window.draw(mObjects[i]->getSprite());
			//mObjects[i]->render();
		}
		for (NpcVector::size_type i = 0; i < mNpcs.size(); i++){
			window.draw(mNpcs[i]->getSprite());
		}
		window.draw(mPlayer->getSprite());

		level.render();
		
		//While shift is held, WASD moves diagonally, shifted left 45 degrees
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
			switch (event.key.code){
			case sf::Keyboard::W:
				moveMeep = 7;
				keyPressed = true;
				break;
			case sf::Keyboard::D:
				moveMeep = 9;
				keyPressed = true;
				break;
			case sf::Keyboard::S:
				moveMeep = 3;
				keyPressed = true;
				break;
			case sf::Keyboard::A:
				moveMeep = 1;
				keyPressed = true;
				break;
			}
		}
		else {
			switch (event.key.code){
			//Move up
			case sf::Keyboard::Numpad8:
				moveMeep = 8;
				keyPressed = true;
				break;
			case sf::Keyboard::W:
				moveMeep = 8;
				keyPressed = true;
				break;
			//Move Right
			case sf::Keyboard::Numpad6:
				moveMeep = 6;
				keyPressed = true;
				break;
			case sf::Keyboard::D:
				moveMeep = 6;
				keyPressed = true;
				break;
			//Move Down
			case sf::Keyboard::Numpad2:
				moveMeep = 2;
				keyPressed = true;
				break;
			case sf::Keyboard::S:
				moveMeep = 2;
				keyPressed = true;
				break;
			//Move left
			case sf::Keyboard::Numpad4:
				moveMeep = 4;
				keyPressed = true;
				break;
			case sf::Keyboard::A:
				moveMeep = 4;
				keyPressed = true;
				break;
			//Move diagonally (only on numpad. Hold shift for diagonal WASD movement)
			case sf::Keyboard::Numpad7:
				moveMeep = 7;
				keyPressed = true;
				break;
			case sf::Keyboard::Numpad9:
				moveMeep = 9;
				keyPressed = true;
				break;
			case sf::Keyboard::Numpad3:
				moveMeep = 3;
				keyPressed = true;
				break;
			case sf::Keyboard::Numpad1:
				moveMeep = 1;
				keyPressed = true;
				break;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
			space = true;
		}

		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && space && keyPressed){
			space = false;
			level.takeTurn(moveMeep);
			moveMeep = 0;
			keyPressed = false;
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

