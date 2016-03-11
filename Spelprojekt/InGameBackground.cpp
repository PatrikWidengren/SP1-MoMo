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
static const string bronze_medal = "Resource Files/Backgrounds/Medal_Bronze.png";
static const string silver_medal = "Resource Files/Backgrounds/Medal_Silver.png";
static const string gold_medal = "Resource Files/Backgrounds/Medal_Gold.png";

InGameBackground::InGameBackground() {
	setTextures();
	inGameHud->setTexture(*texture_inGameHud);
	if (!font.loadFromFile("Resource Files/Fonts/arial.ttf")) {
		cout << "Error loading arial.ttf" << endl;
	}
	sprite_medal->setPosition(594, 26);
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
	delete texture_bronzeMedal;
	delete texture_silverMedal;
	delete texture_goldMedal;

	delete backgroundTop;
	delete backgroundBottom;
	delete inGameHud;
	delete sprite_medal;

	delete mTurns;
	delete mProgress;
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
	window.draw(*sprite_medal);
}
void InGameBackground::drawBackgroundBottom(sf::RenderWindow &window) {
	if (mMapName == "map01a01.txt" || mMapName == "map01a02.txt" || mMapName == "map01a03.txt" || mMapName == "map01a04.txt" || mMapName == "map01a05.txt") {
		window.draw(*backgroundBottom);
	}
	window.draw(*mTurns);
	window.draw(*mProgress);
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
	if (!texture_bronzeMedal->loadFromFile(bronze_medal)) //try to load the texture. if its wrong, give error
		cout << "medalj gick ej." << endl;
	if (!texture_silverMedal->loadFromFile(silver_medal)) //try to load the texture. if its wrong, give error
		cout << "medalj gick ej." << endl;
	if (!texture_goldMedal->loadFromFile(gold_medal)) //try to load the texture. if its wrong, give error
		cout << "medalj gick ej." << endl;
}
string InGameBackground::writeTurns(int turnss) {
	ostringstream o;
	o << "Turn: " << turnss;
	return o.str();
}
string InGameBackground::writeProgress(int cutgrass, int cuthedges, int cutdandelions, vector<int>* goals) {
	ostringstream o;
	if (cutgrass >= goals->at(1) && cuthedges >= goals->at(4) && cutdandelions >= goals->at(7)) {
		sprite_medal->setTexture(*texture_goldMedal);
		if (goals->at(0) != 0) {
			o << "Grass (%): " << cutgrass << "\t Goal for gold medal: " << goals->at(2) << endl;
		}
		if (goals->at(3) != 0) {
			o << "Hedges (%): " << cuthedges << "\t Goal for gold medal: " << goals->at(5) << endl;
		}
		if (goals->at(6) != 0) {
			o << "Dandylions (%): " << cutdandelions << "\t Goal for gold medal: " << goals->at(8);
		}
	}
	else if (cutgrass >= goals->at(0) && cuthedges >= goals->at(3) && cutdandelions >= goals->at(6)) {
		sprite_medal->setTexture(*texture_silverMedal);
		if (goals->at(0) != 0) {
			o << "Grass (%): " << cutgrass << "\t Goal for silver medal: " << goals->at(1) << endl;
		}
		if (goals->at(3) != 0) {
			o << "Hedges (%): " << cuthedges << "\t Goal for silver medal: " << goals->at(4) << endl;
		}
		if (goals->at(6) != 0) {
			o << "Dandylions (%): " << cutdandelions << "\t Goal for silver medal: " << goals->at(7);
		}
	}
	else if (cutgrass <= goals->at(0) || cuthedges <= goals->at(3) || cutdandelions <= goals->at(6)) {
		sprite_medal->setTexture(*texture_bronzeMedal);
		if (goals->at(0) != 0) {
			o << "Grass (%): " << cutgrass << "\t Goal for bronze medal: " << goals->at(0) << endl;
		}
		if (goals->at(3) != 0) {
			o << "Hedges (%): " << cuthedges << "\t Goal for bronze medal: " << goals->at(3) << endl;
		}
		if (goals->at(6) != 0) {
			o << "Dandylions (%): " << cutdandelions << "\t Goal for bronze medal: " << goals->at(6);
		}
	}
	
	return o.str();
}
void InGameBackground::write(int turncount, int cutgrass, int cuthedges, int cutdandelions, vector<int>* goals) {
	writeTurns(turncount);
	sf::Text* turns = new sf::Text(writeTurns(turncount), font, 20);
	mTurns = turns;
	sf::Text* tempProgress = new sf::Text(writeProgress(cutgrass, cuthedges, cutdandelions, goals), font, 20);
	mProgress = tempProgress;
	mProgress->setPosition(50, 50);
	mTurns->setPosition(1700, 150);
}

