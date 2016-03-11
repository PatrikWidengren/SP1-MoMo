#include "InGameBackground.h"

using namespace std;

static const string m01a01_backGroundTop = "Resource Files/Backgrounds/World01_Lane01_BG.png";
static const string m01a01_backGroundBottom = "Resource Files/Backgrounds/World01_Lane01_FG.png";
static const string m01a02_backGroundTop = "Resource Files/Backgrounds/World01_Lane02_BG.png";
static const string m01a02_backGroundBottom = "Resource Files/Backgrounds/World01_Lane02_FG.png";
static const string m01a03_backGroundTop = "Resource Files/Backgrounds/World01_Lane03_BG.png";
static const string m01a03_backGroundBottom = "Resource Files/Backgrounds/World01_Lane03_FG.png";
static const string m01a04_backGroundTop = "Resource Files/Backgrounds/World01_Lane04_BG.png";
static const string m01a04_backGroundBottom = "Resource Files/Backgrounds/World01_Lane04_FG.png";
static const string m01a05_backGroundTop = "Resource Files/Backgrounds/World01_Lane05_BG.png";
static const string m01a05_backGroundBottom = "Resource Files/Backgrounds/World01_Lane05_FG.png";
static const string filename_inGameHud = "Resource Files/Backgrounds/In-game UI.png";

InGameBackground::InGameBackground() {
	sf::Text turns(writeTurns(mIntTurns), font, 20);
	mTurns = turns;
	setTextures();
	//backgroundTop->setTexture(*texture01_backgroundTop);
	//backgroundBottom->setTexture(*texture01_backgroundBottom);
	inGameHud->setTexture(*texture_inGameHud);
	if (!font.loadFromFile("Resource Files/Fonts/arial.ttf")) {
		cout << "Error loading arial.ttf" << endl;
	}
	mTurns.setColor(sf::Color::White);
	mTurns.setPosition(1700, 150);

}
InGameBackground::~InGameBackground() 
{
	delete texture01_backgroundTop;
	delete texture01_backgroundBottom;
	delete texture02_backgroundTop;
	delete texture02_backgroundBottom;
	delete texture03_backgroundTop;
	delete texture03_backgroundBottom;
	delete texture04_backgroundTop;
	delete texture04_backgroundBottom;
	delete texture05_backgroundTop;
	delete texture05_backgroundBottom;
	delete texture_inGameHud;

	delete backgroundTop;
	delete backgroundBottom;
	delete inGameHud;
}
void InGameBackground::setMapname(string mapname) {
	mMapName = mapname;
	if (mMapName == "map01a01.txt") {
		backgroundTop->setTexture(*texture01_backgroundTop);
		backgroundBottom->setTexture(*texture01_backgroundBottom);
	}
	else if (mMapName == "map01a02.txt") {
		backgroundTop->setTexture(*texture02_backgroundTop);
		backgroundBottom->setTexture(*texture02_backgroundBottom);
	}
	else if (mMapName == "map01a03.txt") {
		backgroundTop->setTexture(*texture03_backgroundTop);
		backgroundBottom->setTexture(*texture03_backgroundBottom);
	}
	else if (mMapName == "map01a04.txt") {
		backgroundTop->setTexture(*texture04_backgroundTop);
		backgroundBottom->setTexture(*texture04_backgroundBottom);
	}
	else if (mMapName == "map01a05.txt") {
		backgroundTop->setTexture(*texture05_backgroundTop);
		backgroundBottom->setTexture(*texture05_backgroundBottom);
	}
}
void InGameBackground::drawBackgroundTop(sf::RenderWindow &window) {
	if (mMapName == "map01a01.txt" || mMapName == "map01a02.txt" || mMapName == "map01a03.txt" || mMapName == "map01a04.txt" || mMapName == "map01a05.txt") {
		window.draw(*backgroundTop);
	}
	window.draw(*inGameHud);

}
void InGameBackground::drawBackgroundBottom(sf::RenderWindow &window) {
	if (mMapName == "map01a01.txt" || mMapName == "map01a02.txt" || mMapName == "map01a03.txt" || mMapName == "map01a04.txt" || mMapName == "map01a05.txt") {
		window.draw(*backgroundBottom);
	}
	window.draw(mTurns);
}
void InGameBackground::setTextures() {
	if (!texture01_backgroundTop->loadFromFile(m01a01_backGroundTop)) //try to load the texture. if its wrong, give error
		cout << "backgroundTop gick ej." << endl;
	if (!texture01_backgroundBottom->loadFromFile(m01a01_backGroundBottom)) //try to load the texture. if its wrong, give error
		cout << "backgroundBottom gick ej." << endl;
	if (!texture02_backgroundTop->loadFromFile(m01a02_backGroundTop)) //try to load the texture. if its wrong, give error
		cout << "backgroundTop gick ej." << endl;
	if (!texture02_backgroundBottom->loadFromFile(m01a02_backGroundBottom)) //try to load the texture. if its wrong, give error
		cout << "backgroundBottom gick ej." << endl;
	if (!texture03_backgroundTop->loadFromFile(m01a03_backGroundTop)) //try to load the texture. if its wrong, give error
		cout << "backgroundTop gick ej." << endl;
	if (!texture03_backgroundBottom->loadFromFile(m01a03_backGroundBottom)) //try to load the texture. if its wrong, give error
		cout << "backgroundBottom gick ej." << endl;
	if (!texture04_backgroundTop->loadFromFile(m01a04_backGroundTop)) //try to load the texture. if its wrong, give error
		cout << "backgroundTop gick ej." << endl;
	if (!texture04_backgroundBottom->loadFromFile(m01a04_backGroundBottom)) //try to load the texture. if its wrong, give error
		cout << "backgroundBottom gick ej." << endl;
	if (!texture05_backgroundTop->loadFromFile(m01a05_backGroundTop)) //try to load the texture. if its wrong, give error
		cout << "backgroundTop gick ej." << endl;
	if (!texture05_backgroundBottom->loadFromFile(m01a05_backGroundBottom)) //try to load the texture. if its wrong, give error
		cout << "backgroundBottom gick ej." << endl;
	if (!texture_inGameHud->loadFromFile(filename_inGameHud)) //try to load the texture. if its wrong, give error
		cout << "ingamehud gick ej." << endl;
}
string InGameBackground::writeTurns(int turnss) {
	ostringstream o;
	mIntTurns = turnss;
	o << "Turn: " << mIntTurns;
	//sf::Text turns(writeTurns(5), font, 20);
	//mTurns = turns;
	return o.str();
}
void InGameBackground::write(int turncount) {
	writeTurns(turncount);
	sf::Text turns(writeTurns(mIntTurns), font, 30);
	mTurns = turns;
	mTurns.setPosition(1700, 150);
}

