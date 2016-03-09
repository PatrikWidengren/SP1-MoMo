#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>

//#include "../GameStates/Map1.h" Used for "checkIfBeforeAfterDialogue" Maybe. //Fnatte
class DialogManager
{
public:
	DialogManager(sf::RenderWindow &window);
	~DialogManager();
	//void playDialog(int dialogID, int time);
	void playBeforeDialogue(std::string wichMap, sf::RenderWindow &window);
	void playAfterDialogue(std::string wichMap, sf::RenderWindow &window);
	void drawBeforeDialogue(sf::RenderWindow &window);
	void drawAfterDialogue(sf::RenderWindow &window);
	bool checkBeforeDialogue(std::string mapName);
	bool checkAfterDialogue(std::string mapName);
	int mCurrentDialogue;
	void swapDialogueTexture(int beforeOrAfter);

	void setTextures();

private:
	int mTimer;
	int mCurrentBeforeMapDialogue;
	int mCurrentAfterMapDialogue;

	typedef std::vector<sf::Texture*> HouseTextures;

	sf::Sprite spriteDialogs;
	//qweHouseTextures *textBeforeDialogs;
	//qweHouseTextures *textAfterDialogs;
};