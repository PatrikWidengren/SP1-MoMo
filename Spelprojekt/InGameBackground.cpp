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

static const string momentum2_01 = "Resource Files/Sprites/Momentum_Mower1_1.png";
static const string momentum2_02 = "Resource Files/Sprites/Momentum_Mower1_2.png";
static const string momentum3_01 = "Resource Files/Sprites/Momentum_Mower2_1.png";
static const string momentum3_02 = "Resource Files/Sprites/Momentum_Mower2_2.png";
static const string momentum3_03 = "Resource Files/Sprites/Momentum_Mower2_3.png";
static const string momentum4_01 = "Resource Files/Sprites/Momentum_Mower3_1.png";
static const string momentum4_02 = "Resource Files/Sprites/Momentum_Mower3_2.png";
static const string momentum4_03 = "Resource Files/Sprites/Momentum_Mower3_3.png";
static const string momentum4_04 = "Resource Files/Sprites/Momentum_Mower3_4.png";

static const string filename_inGameHud = "Resource Files/Sprites/wood.png";
static const string bronze_medal = "Resource Files/Sprites/Medal_Bronze.png";
static const string silver_medal = "Resource Files/Sprites/Medal_Silver.png";
static const string gold_medal = "Resource Files/Sprites/Medal_Gold.png";

static const string filename_arrow = "Resource Files/Sprites/downArrow.png";
static const string filename_woodMedal = "Resource Files/Sprites/Wood_Medal.png";
static const string filename_woodMenu = "Resource Files/Sprites/Wood_Menu.png";
static const string filename_woodMomentum = "Resource Files/Sprites/Wood_Momentum.png";
static const string filename_woodLawnmower = "Resource Files/Sprites/Wood_Tools.png";
static const string filename_woodHedgecutter = "Resource Files/Sprites/Wood_Tools_1.png";
static const string filename_momentumText = "Resource Files/Sprites/MOMENTUM.png";
static const string filename_menuText = "Resource Files/Sprites/MENU.png";

static const string filename_lawnmower01 = "Resource Files/Sprites/Mower_3.png";
static const string filename_lawnmower02 = "Resource Files/Sprites/Mower_4.png";
static const string filename_lawnmower03 = "Resource Files/Sprites/Mower_5.png";
static const string filename_lawnmower04 = "Resource Files/Sprites/Mower_1.png";
static const string filename_lawnmower05 = "Resource Files/Sprites/Mower_2.png";
static const string filename_hedgecutter01 = "Resource Files/Sprites/Hedgecutter.png";

InGameBackground::InGameBackground() {
	setTextures();
	sprite_inGameHud->setTexture(*texture_inGameHud);
	if (!font.loadFromFile("Resource Files/Fonts/arial.ttf")) {
		cout << "Error loading arial.ttf" << endl;
	}

	texture_momentum4_04->loadFromFile(momentum4_04);
	sprite_momentum->setTexture(*texture_momentum4_04);

	imageArrow->loadFromFile(filename_arrow);
	imageArrow->createMaskFromColor(sf::Color::White);
	texture_arrow->loadFromImage(*imageArrow);
	sprite_downArrow->setTexture(*texture_arrow);

	texture_woodHedgecutter->loadFromFile(filename_woodHedgecutter);
	texture_woodLawnmower->loadFromFile(filename_woodLawnmower);
	texture_woodMedal->loadFromFile(filename_woodMedal);
	texture_woodMenu->loadFromFile(filename_woodMenu);
	texture_woodMomentum->loadFromFile(filename_woodMomentum);
	texture_momentumText->loadFromFile(filename_momentumText);
	texture_menuText->loadFromFile(filename_menuText);
	texture_lawnmower01->loadFromFile(filename_lawnmower01);
	texture_hedgecutter01->loadFromFile(filename_hedgecutter01);

	sprite_woodHedgecutter->setTexture(*texture_woodHedgecutter);
	sprite_woodLawnmower->setTexture(*texture_woodLawnmower);
	sprite_woodMedal->setTexture(*texture_woodMedal);
	sprite_woodMenu->setTexture(*texture_woodMenu);
	sprite_woodMomentum->setTexture(*texture_woodMomentum);
	sprite_momentumText->setTexture(*texture_momentumText);
	sprite_menuText->setTexture(*texture_menuText);
	sprite_lawnmower->setTexture(*texture_lawnmower01);
	sprite_hedgecutter->setTexture(*texture_hedgecutter01);

	sprite_woodMedal->setPosition(550, 15);
	sprite_woodMomentum->setPosition(750, 8);
	sprite_woodLawnmower->setPosition(1210, 35);
	sprite_woodHedgecutter->setPosition(1425, 35);
	sprite_woodMenu->setPosition(1630, 15);
	sprite_momentumText->setPosition(775, 17);
	sprite_menuText->setPosition(1642, 25);
	sprite_lawnmower->setPosition(1210, 35);
	sprite_hedgecutter->setPosition(1425, 35);

	sprite_medal->setPosition(594, 26);
	sprite_momentum->setPosition(775, 95);
	sprite_downArrow->setPosition(750, 50);
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
	delete texture_arrow;

	delete texture_woodMedal;
	delete texture_woodMomentum;
	delete texture_woodMenu;
	delete texture_woodLawnmower;
	delete texture_woodHedgecutter;

	delete texture_lawnmower01;
	delete texture_lawnmower02;
	delete texture_lawnmower03;
	delete texture_lawnmower04;
	delete texture_lawnmower05;
	delete texture_hedgecutter01;
	delete texture_momentumText;
	delete texture_menuText;

	delete texture_momentum2_01;
	delete texture_momentum2_02;
	delete texture_momentum3_01;
	delete texture_momentum3_02;
	delete texture_momentum3_03;
	delete texture_momentum4_01;
	delete texture_momentum4_02;
	delete texture_momentum4_03;
	delete texture_momentum4_04;

	delete sprite_woodMedal;
	delete sprite_woodLawnmower;
	delete sprite_woodHedgecutter;
	delete sprite_woodMenu;
	delete sprite_woodMomentum;
	delete sprite_hedgecutter;
	delete sprite_lawnmower;
	delete sprite_downArrow;
	delete sprite_menuText;

	delete sprite_momentumText;
	delete sprite_momentum;
	delete sprite_backgroundTop;
	delete sprite_backgroundBottom;
	delete sprite_inGameHud;
	delete sprite_medal;

	delete mTurns;
	delete mProgress;
	delete imageArrow;
}
void InGameBackground::setMapname(string mapname) {
	mMapName = mapname;
	if (mMapName == "map01a01.txt") {
		sprite_backgroundTop->setTexture(*texture01_backgroundTop);
		sprite_backgroundBottom->setTexture(*texture01_backgroundBottom);
	}
	else if (mMapName == "map01a02.txt") {
		sprite_backgroundTop->setTexture(*texture02_backgroundTop);
		sprite_backgroundBottom->setTexture(*texture02_backgroundBottom);
	}
	else if (mMapName == "map01a03.txt") {
		sprite_backgroundTop->setTexture(*texture03_backgroundTop);
		sprite_backgroundBottom->setTexture(*texture03_backgroundBottom);
	}
	else if (mMapName == "map01a04.txt") {
		sprite_backgroundTop->setTexture(*texture04_backgroundTop);
		sprite_backgroundBottom->setTexture(*texture04_backgroundBottom);
	}
	else if (mMapName == "map01a05.txt") {
		sprite_backgroundTop->setTexture(*texture05_backgroundTop);
		sprite_backgroundBottom->setTexture(*texture05_backgroundBottom);
	}
	
}
void InGameBackground::drawBackgroundTop(sf::RenderWindow &window) {
	if (mMapName == "map01a01.txt" || mMapName == "map01a02.txt" || mMapName == "map01a03.txt" || mMapName == "map01a04.txt" || mMapName == "map01a05.txt") {
		window.draw(*sprite_backgroundTop);
	}
	window.draw(*sprite_inGameHud);
	window.draw(*sprite_momentum);
	window.draw(*sprite_woodMedal);
	window.draw(*sprite_woodHedgecutter);
	//window.draw(*sprite_woodLawnmower);
	//window.draw(*sprite_woodMenu);
	window.draw(*sprite_woodMomentum);
	window.draw(*sprite_momentumText);
	window.draw(*sprite_menuText);
	window.draw(*sprite_hedgecutter);
	window.draw(*sprite_lawnmower);
	window.draw(*sprite_medal);
	window.draw(*sprite_momentum);
	window.draw(*sprite_downArrow);

}
void InGameBackground::drawBackgroundBottom(sf::RenderWindow &window) {
	if (mMapName == "map01a01.txt" || mMapName == "map01a02.txt" || mMapName == "map01a03.txt" || mMapName == "map01a04.txt" || mMapName == "map01a05.txt") {
		window.draw(*sprite_backgroundBottom);
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
	if (!texture_momentum2_01->loadFromFile(momentum2_01)) //try to load the texture. if its wrong, give error
		texture_momentum2_01->loadFromFile("Resource Files/Backgrounds/error.jpg");
	if (!texture_momentum2_02->loadFromFile(momentum2_02)) //try to load the texture. if its wrong, give error
		texture_momentum2_02->loadFromFile("Resource Files/Backgrounds/error.jpg");
	if (!texture_momentum3_01->loadFromFile(momentum3_01)) //try to load the texture. if its wrong, give error
		texture_momentum3_01->loadFromFile("Resource Files/Backgrounds/error.jpg");
	if (!texture_momentum3_02->loadFromFile(momentum3_02)) //try to load the texture. if its wrong, give error
		texture_momentum3_02->loadFromFile("Resource Files/Backgrounds/error.jpg");
	if (!texture_momentum3_03->loadFromFile(momentum3_03)) //try to load the texture. if its wrong, give error
		texture_momentum3_03->loadFromFile("Resource Files/Backgrounds/error.jpg");
	if (!texture_momentum4_01->loadFromFile(momentum4_01)) //try to load the texture. if its wrong, give error
		texture_momentum4_01->loadFromFile("Resource Files/Backgrounds/error.jpg");
	if (!texture_momentum4_02->loadFromFile(momentum4_02)) //try to load the texture. if its wrong, give error
		texture_momentum4_02->loadFromFile("Resource Files/Backgrounds/error.jpg");
	if (!texture_momentum4_03->loadFromFile(momentum4_03)) //try to load the texture. if its wrong, give error
		texture_momentum4_03->loadFromFile("Resource Files/Backgrounds/error.jpg");
	if (!texture_momentum4_04->loadFromFile(momentum4_04)) //try to load the texture. if its wrong, give error
		texture_momentum4_04->loadFromFile("Resource Files/Backgrounds/error.jpg");
	
	if (!texture_lawnmower02->loadFromFile(filename_lawnmower02)) //try to load the texture. if its wrong, give error
		texture_lawnmower02->loadFromFile("Resource Files/Backgrounds/error.jpg");
	if (!texture_lawnmower03->loadFromFile(filename_lawnmower03)) //try to load the texture. if its wrong, give error
		texture_lawnmower03->loadFromFile("Resource Files/Backgrounds/error.jpg");
	if (!texture_lawnmower04->loadFromFile(filename_lawnmower04)) //try to load the texture. if its wrong, give error
		texture_lawnmower04->loadFromFile("Resource Files/Backgrounds/error.jpg");
	if (!texture_lawnmower05->loadFromFile(filename_lawnmower05)) //try to load the texture. if its wrong, give error
		texture_lawnmower05->loadFromFile("Resource Files/Backgrounds/error.jpg");
}
string InGameBackground::writeTurns(int turnss) {
	ostringstream o;
	o << "Turns left: " << turnss;
	return o.str();
}
string InGameBackground::writeProgress(int cutgrass, int cuthedges, int cutdandelions, vector<int>* goals) {
	ostringstream o;

	//Fått guld
	if (cutgrass >= goals->at(2) && cuthedges >= goals->at(5) && cutdandelions >= goals->at(8)) {
		sprite_medal->setTexture(*texture_goldMedal);
		mMedal = "Gold";
		o << "All goals completed. ";
	
	}
	//Fått silver
	else if (cutgrass >= goals->at(1) && cuthedges >= goals->at(4) && cutdandelions >= goals->at(7)) {
		sprite_medal->setTexture(*texture_silverMedal);
		mMedal = "Silver";
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
	//Fått brons
	else if (cutgrass >= goals->at(0) && cuthedges >= goals->at(3) && cutdandelions >= goals->at(6)) {
		sprite_medal->setColor(sf::Color(255, 255, 255, 255));
		sprite_medal->setTexture(*texture_bronzeMedal);
		mMedal = "Bronze";
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
	//Påväg till brons
	else if (cutgrass <= goals->at(0) || cuthedges <= goals->at(3) || cutdandelions <= goals->at(6)) {
		//sprite_medal->setTexture(*texture_bronzeMedal);
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
void InGameBackground::scale(sf::RenderWindow &window) {
	float scaleX = (float)window.getSize().x / 1920;
	float scaleY = (float)window.getSize().y / 1080;

	sprite_backgroundBottom->setScale(scaleX, scaleY);
	sprite_backgroundTop->setScale(scaleX, scaleY);
	sprite_inGameHud->setScale(scaleX, scaleY);
	sprite_medal->setScale(scaleX, scaleY);
	mTurns->setScale(scaleX, scaleY);
	mProgress->setScale(scaleX, scaleY);
	sprite_momentum->setScale(scaleX, scaleY);

	sprite_medal->setPosition(594 * scaleX, 26 * scaleY);
	sprite_momentum->setPosition(775 * scaleX, 95 * scaleY);
	mTurns->setPosition(1700 * scaleX, 150 * scaleY);
	mProgress->setPosition(50 * scaleX, 50 * scaleY);
}
void InGameBackground::getInfo(int maxmomentum, int minmomentum, int currentmomentum, int fallvalue, int risevalue, bool checkmower) {
	mMowerMaxMomentum = maxmomentum;
	mMowerMinMomentum = minmomentum;
	mMowerCurrentMomentum = currentmomentum;
	mMowerFallValue = fallvalue;
	mMowerRiseValue = risevalue;
	if (checkmower) {
		sprite_downArrow->setPosition(1275, 15);
	}
	else {
		sprite_downArrow->setPosition(1490, 15);
	}
}
void InGameBackground::selectMomentumSprite() {
	if (mMowerMaxMomentum == 2) {
		if (mMowerCurrentMomentum == 1) {
			sprite_momentum->setTexture(*texture_momentum2_01);
		}
		if (mMowerCurrentMomentum == 2) {
			sprite_momentum->setTexture(*texture_momentum2_02);
		}
	}
	if (mMowerMaxMomentum == 3) {
		if (mMowerCurrentMomentum == 1) {
			sprite_momentum->setTexture(*texture_momentum3_01);
		}
		if (mMowerCurrentMomentum == 2) {
			sprite_momentum->setTexture(*texture_momentum3_02);
		}
		if (mMowerCurrentMomentum == 3) {
			sprite_momentum->setTexture(*texture_momentum3_03);
		}
	}
	if (mMowerMaxMomentum == 4) {
		if (mMowerCurrentMomentum == 1) {
			sprite_momentum->setTexture(*texture_momentum4_01);
		}
		if (mMowerCurrentMomentum == 2) {
			sprite_momentum->setTexture(*texture_momentum4_02);
		}
		if (mMowerCurrentMomentum == 3) {
			sprite_momentum->setTexture(*texture_momentum4_03);
		}
		if (mMowerCurrentMomentum == 4) {
			sprite_momentum->setTexture(*texture_momentum4_04);
		}
	}
}
void InGameBackground::selectLawnmowerSprite(int number) {
	if (number == 0) {
		sprite_lawnmower->setTexture(*texture_lawnmower01);
	}
	if (number == 1) {
		sprite_lawnmower->setTexture(*texture_lawnmower02);
	}
	if (number == 2) {
		sprite_lawnmower->setTexture(*texture_lawnmower03);
	}
	if (number == 3) {
		sprite_lawnmower->setTexture(*texture_lawnmower04);
	}
	if (number == 4) {
		sprite_lawnmower->setTexture(*texture_lawnmower05);
	}
}
void InGameBackground::selectHedgecutterSprite() {
	if (mCurrentLawnmower == 1) {
		sprite_hedgecutter->setTexture(*texture_hedgecutter01);
	}
}
void InGameBackground::resetInGameHud() {
	sprite_medal->setColor(sf::Color(255, 255, 255, 0));
	mMedal = "0";
}
string InGameBackground::getMedal() {
	return mMedal;
}