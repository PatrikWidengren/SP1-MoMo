#include "InGameBackground.h"

using namespace std;

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
	int nr = -1;
	setTextures();
	sprite_inGameHud->setTexture(*texture_inGameHud);
	if (!font.loadFromFile("Resource Files/Fonts/arial.ttf")) {
		cout << "Error loading arial.ttf" << endl;
	}

	for (int i = 0; i < numberOfLevels; i++) {
		backgroundArrayTop[i] = new sf::Texture();
		backgroundArrayBottom[i] = new sf::Texture();
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 5; j++) {
			nr++;
			backgroundArrayBottom[nr]->loadFromFile(getTextureFilenameBottom(i, j));
			backgroundArrayTop[nr]->loadFromFile(getTextureFilenameTop(i, j));
		}
	}

	imageArrow->loadFromFile(filename_arrow);
	imageArrow->createMaskFromColor(sf::Color::White);
	texture_arrow->loadFromImage(*imageArrow);

	sprite_downArrow->setTexture(*texture_arrow);
	sprite_woodHedgecutter->setTexture(*texture_woodHedgecutter);
	sprite_woodLawnmower->setTexture(*texture_woodLawnmower);
	sprite_woodMedal->setTexture(*texture_woodMedal);
	sprite_woodMenu->setTexture(*texture_woodMenu);
	sprite_woodMomentum->setTexture(*texture_woodMomentum);
	sprite_momentumText->setTexture(*texture_momentumText);
	sprite_menuText->setTexture(*texture_menuText);

}
InGameBackground::~InGameBackground() 
{

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
	int nr = -1;
	drawBackground = false;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 5; j++) {
			nr++;
			stringstream name;
			name << "map0" << i + 1 << "a0" << j + 1 << ".txt";
			if (name.str() == mapname) {
				drawBackground = true;
				sprite_backgroundTop->setTexture(*backgroundArrayTop[nr]);
				sprite_backgroundBottom->setTexture(*backgroundArrayBottom[nr]);
			}
		}
	}
}
void InGameBackground::drawBackgroundTop(sf::RenderWindow &window) {
	if (drawBackground) {
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
	if (drawBackground) {
		window.draw(*sprite_backgroundBottom);
	}
	window.draw(*mTurns);
	window.draw(*mProgress);
}
void InGameBackground::setTextures() {

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
	
	if (!texture_lawnmower01->loadFromFile(filename_lawnmower01)) //try to load the texture. if its wrong, give error
		texture_lawnmower01->loadFromFile("Resource Files/Backgrounds/error.jpg");
	if (!texture_lawnmower02->loadFromFile(filename_lawnmower02)) //try to load the texture. if its wrong, give error
		texture_lawnmower02->loadFromFile("Resource Files/Backgrounds/error.jpg");
	if (!texture_lawnmower03->loadFromFile(filename_lawnmower03)) //try to load the texture. if its wrong, give error
		texture_lawnmower03->loadFromFile("Resource Files/Backgrounds/error.jpg");
	if (!texture_lawnmower04->loadFromFile(filename_lawnmower04)) //try to load the texture. if its wrong, give error
		texture_lawnmower04->loadFromFile("Resource Files/Backgrounds/error.jpg");
	if (!texture_lawnmower05->loadFromFile(filename_lawnmower05)) //try to load the texture. if its wrong, give error
		texture_lawnmower05->loadFromFile("Resource Files/Backgrounds/error.jpg");

	if (!texture_woodHedgecutter->loadFromFile(filename_woodHedgecutter)) //try to load the texture. if its wrong, give error
		texture_woodHedgecutter->loadFromFile("Resource Files/Backgrounds/error.jpg");
	if (!texture_woodLawnmower->loadFromFile(filename_woodLawnmower)) //try to load the texture. if its wrong, give error
		texture_woodLawnmower->loadFromFile("Resource Files/Backgrounds/error.jpg");
	if (!texture_woodMedal->loadFromFile(filename_woodMedal)) //try to load the texture. if its wrong, give error
		texture_woodMedal->loadFromFile("Resource Files/Backgrounds/error.jpg");
	if (!texture_woodMenu->loadFromFile(filename_woodMenu)) //try to load the texture. if its wrong, give error
		texture_woodMenu->loadFromFile("Resource Files/Backgrounds/error.jpg");
	if (!texture_woodMomentum->loadFromFile(filename_woodMomentum)) //try to load the texture. if its wrong, give error
		texture_woodMomentum->loadFromFile("Resource Files/Backgrounds/error.jpg");
	if (!texture_momentumText->loadFromFile(filename_momentumText)) //try to load the texture. if its wrong, give error
		texture_momentumText->loadFromFile("Resource Files/Backgrounds/error.jpg");
	if (!texture_menuText->loadFromFile(filename_menuText)) //try to load the texture. if its wrong, give error
		texture_menuText->loadFromFile("Resource Files/Backgrounds/error.jpg");
	if (!texture_hedgecutter01->loadFromFile(filename_hedgecutter01)) //try to load the texture. if its wrong, give error
		texture_hedgecutter01->loadFromFile("Resource Files/Backgrounds/error.jpg");

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
	delete mTurns;
	mTurns = turns;
	sf::Text* tempProgress = new sf::Text(writeProgress(cutgrass, cuthedges, cutdandelions, goals), font, 20);
	delete mProgress;
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
	sprite_woodMedal->setScale(scaleX, scaleY);
	sprite_woodMomentum->setScale(scaleX, scaleY);
	sprite_woodLawnmower->setScale(scaleX, scaleY);
	sprite_woodHedgecutter->setScale(scaleX, scaleY);
	sprite_woodMenu->setScale(scaleX, scaleY);
	sprite_momentumText->setScale(scaleX, scaleY);
	sprite_menuText->setScale(scaleX, scaleY);
	sprite_lawnmower->setScale(scaleX, scaleY);
	sprite_hedgecutter->setScale(scaleX, scaleY);
	sprite_downArrow->setScale(scaleX, scaleY);

	sprite_medal->setPosition(594 * scaleX, 26 * scaleY);
	sprite_momentum->setPosition(775 * scaleX, 95 * scaleY);
	mTurns->setPosition(1700 * scaleX, 150 * scaleY);
	mProgress->setPosition(50 * scaleX, 50 * scaleY);
	sprite_woodMedal->setPosition(550 * scaleX, 15 * scaleY);
	sprite_woodMomentum->setPosition(750 * scaleX, 8 * scaleY);
	sprite_woodLawnmower->setPosition(1210 * scaleX, 35 * scaleY);
	sprite_woodHedgecutter->setPosition(1425 * scaleX, 35 * scaleY);
	sprite_woodMenu->setPosition(1630 * scaleX, 15 * scaleY);
	sprite_momentumText->setPosition(775 * scaleX, 17 * scaleY);
	sprite_menuText->setPosition(1642 * scaleX, 25 * scaleY);
	sprite_lawnmower->setPosition(1210 * scaleX, 35 * scaleY);
	sprite_hedgecutter->setPosition(1425 * scaleX, 35 * scaleY);
	
	if (mCheckMower) {
		sprite_downArrow->setPosition(1275 * scaleX, 15 * scaleY);
	}
	else {
		sprite_downArrow->setPosition(1490 * scaleX, 15 * scaleY);
	}
}
void InGameBackground::getInfo(int maxmomentum, int minmomentum, int currentmomentum, int fallvalue, int risevalue, bool checkmower) {
	mMowerMaxMomentum = maxmomentum;
	mMowerMinMomentum = minmomentum;
	mMowerCurrentMomentum = currentmomentum;
	mMowerFallValue = fallvalue;
	mMowerRiseValue = risevalue;
	mCheckMower = checkmower;
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
	if (mCurrentHedgecutter == 1) {
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
string InGameBackground::getTextureFilenameTop(int i, int j) {
	stringstream o;
	o << "Resource Files/Backgrounds/World0" << i + 1 << "_Lane0" << j + 1 << "_BG.png";
	cout << o.str() << endl;
	return o.str();
}
string InGameBackground::getTextureFilenameBottom(int i, int j) {
	stringstream o;
	o << "Resource Files/Backgrounds/World0" << i + 1 << "_Lane0" << j + 1 << "_FG.png";
	cout << o.str() << endl;
	return o.str();
}
