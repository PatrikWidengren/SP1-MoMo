#include <SFML/Graphics.hpp> 
//asdasdderp
//wat
//sssssss
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
	for (ObjectsVector::size_type i = 0; i < mObjects.size(); i++){
		cout << mObjects[i]->getX() << " " << mObjects[i]->getY() << endl;
	}
	
	bool keepMoving = true;
	int moveMeep = 0;
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
		window.draw(mPlayer->getSprite());


		level.render();

		//while (keepMoving){
		//	std::cin >> i;
		
		if (moveMeep <= 0 || moveMeep == 5 || moveMeep > 9){
				keepMoving = false;
		}
		else {
			level.takeTurn(moveMeep);
			//level1.printMap();
		}
		//}

		
		window.display();
	}
	return 0;
}

