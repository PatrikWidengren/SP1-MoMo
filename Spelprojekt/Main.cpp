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
	ObjectsVector mLongObjects;

	//Skapar instans av "Map1"
	Map1 level("map1.txt");

	//Anropar funktion för att spawna alla objekt
	level.spawnObjects();

	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeigth), "garden");

	//Kopierar objekten
	mObjects = level.getObjects();
	mPlayer = level.getPlayer();
	mNpcs = level.getNpcs();
	mLongObjects = level.getLongObjects();
	// Skriver ut position för alla object
	for (ObjectsVector::size_type i = 0; i < mObjects.size(); i++){
		cout << mObjects[i]->getPosX() << " " << mObjects[i]->getPosY() << endl;
	}
	int moveMeep = 0;
	//A lot of flags for key inputs
	bool keyPressed = false;
	bool space = false;
	bool dir1 = false;
	bool dir2 = false;
	bool dir3 = false;
	bool dir4 = false;
	bool dir6 = false;
	bool dir7 = false;
	bool dir8 = false;
	bool dir9 = false;
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
		for (ObjectsVector::size_type i = 0; i < mLongObjects.size(); i++){
			window.draw(mLongObjects[i]->getSprite());
			//mObjects[i]->render();
		}
		level.render();
		
		//Movement reacts to numpad, and WASD/Shift+WASD
		//Currently both methods work, but later, this should be something that can be changed in the options menu

		if (moveMeep != 1 && ((sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) &&
			sf::Keyboard::isKeyPressed(sf::Keyboard::A)) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1))){
			moveMeep = 1;
			keyPressed = true;
		}
		if (moveMeep != 3 && ((sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) &&
			sf::Keyboard::isKeyPressed(sf::Keyboard::S)) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3))){
			moveMeep = 3;
			keyPressed = true;
		}
		if (moveMeep!=7 && ((sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) &&
			sf::Keyboard::isKeyPressed(sf::Keyboard::W)) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7))){
			moveMeep = 7;
			keyPressed = true;
		}
		if (moveMeep != 9 && ((sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) &&
			sf::Keyboard::isKeyPressed(sf::Keyboard::D)) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad9))){
			moveMeep = 9;
			keyPressed = true;
		}

		if (moveMeep != 2 && ((!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) &&
			sf::Keyboard::isKeyPressed(sf::Keyboard::S)) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))){
			moveMeep = 2;
			keyPressed = true;
		}
		if (moveMeep != 4 && ((!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) &&
			sf::Keyboard::isKeyPressed(sf::Keyboard::A)) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4))){
			moveMeep = 4;
			keyPressed = true;
		}
		if (moveMeep != 6 && ((!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) &&
			sf::Keyboard::isKeyPressed(sf::Keyboard::D)) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6))){
			moveMeep = 6;
			keyPressed = true;
		}
		if (moveMeep != 8 && ((!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) &&
			sf::Keyboard::isKeyPressed(sf::Keyboard::W)) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8))){
			moveMeep = 8;
			keyPressed = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !space && keyPressed){
			space = true;
			level.takeTurn(moveMeep);
			moveMeep = 0;
			keyPressed = false;
		}

		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && space){
			space = false;
		}
		
		window.display();
	}
	return 0;
}

