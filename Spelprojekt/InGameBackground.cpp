#include "InGameBackground.h"

using namespace std;

static const string filename_backGroundTop = "Resource Files/Backgrounds/World01_Lane01_BG.png";
static const string filename_backGroundBottom = "Resource Files/Backgrounds/World01_Lane01_FG.png";
static const string filename_inGameHud = "Resource Files/Backgrounds/In-game UI.png";

InGameBackground::InGameBackground() {
	setTextures();
	backgroundTop->setTexture(*texture_backgroundTop);
	backgroundBottom->setTexture(*texture_backgroundBottom);
	inGameHud->setTexture(*texture_inGameHud);
}
InGameBackground::~InGameBackground() 
{
	delete texture_backgroundTop;
	delete texture_backgroundBottom;
	delete texture_inGameHud;

	delete backgroundTop;
	delete backgroundBottom;
	delete inGameHud;
}
void InGameBackground::setMapname(string mapname) {
	mMapName = mapname;
}
void InGameBackground::drawBackgroundTop(sf::RenderWindow &window) {
	if (mMapName == "map01a01.txt") {
		window.draw(*backgroundTop);
	}
	window.draw(*inGameHud);

}
void InGameBackground::drawBackgroundBottom(sf::RenderWindow &window) {
	if (mMapName == "map01a01.txt") {
		window.draw(*backgroundBottom);
	}
}
void InGameBackground::setTextures() {
	if (!texture_backgroundTop->loadFromFile(filename_backGroundTop)) //try to load the texture. if its wrong, give error
		cout << "backgroundTop gick ej." << endl;
	if (!texture_backgroundBottom->loadFromFile(filename_backGroundBottom)) //try to load the texture. if its wrong, give error
		cout << "backgroundBottom gick ej." << endl;
	if (!texture_inGameHud->loadFromFile(filename_inGameHud)) //try to load the texture. if its wrong, give error
		cout << "ingamehud gick ej." << endl;
}

