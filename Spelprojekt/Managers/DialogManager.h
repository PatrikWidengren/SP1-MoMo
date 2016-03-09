#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>

//#include "../GameStates/Map1.h" Used for "checkIfBeforeAfterDialouge" Maybe. //Fnatte
class DialogManager
{
public:
	DialogManager(sf::RenderWindow &window);
	~DialogManager();
	//void playDialog(int dialogID, int time);
	void playBeforeDialouge(std::string wichMap, sf::RenderWindow &window);
	void playAfterDialouge(std::string wichMap, sf::RenderWindow &window);
	void drawBeforeDialouge(sf::RenderWindow &window);
	void drawAfterDialouge(sf::RenderWindow &window);
	bool checkBeforeDialouge(std::string mapName);
	bool checkAfterDialouge(std::string mapName);
	int mCurrentDialouge;
	void swapDialougeTexture(int beforeOrAfter);

	void setTextures();

private:
	int mTimer;
	int mCurrentBeforeMapDialouge;
	int mCurrentAfterMapDialouge;

	typedef std::vector<sf::Texture*> HouseTextures;

	sf::Sprite spriteDialogs;
	//qweHouseTextures *textBeforeDialogs;
	//qweHouseTextures *textAfterDialogs;
};