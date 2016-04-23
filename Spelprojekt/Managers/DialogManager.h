#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <iostream>
#include <list>
#include <sstream>


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
	std::string writeDialogSearchName(int d);

	void setTextures();

private:
	int mTimer;
	int mCurrentBeforeMapDialogue;
	int mCurrentAfterMapDialogue;
	int j = 255;
	bool mClick = false;
	bool i = false;


	//typedef std::vector<sf::Texture*> DialogueTextures;

	//DialogueTextures textureMap01a01BeforeDialogue[23];

	//std::vector<sf::Texture*> textureMap01a01BeforeDialogue;

	sf::Texture* textureMap01a01BeforeDialogue[23];

	//sf::Texture* **textBeforeDialogstest;
//	sf::Texture* textureMap01a01Dialogue = new sf::Texture();
	sf::Sprite* spriteDialogs = new sf::Sprite();
	//DialogueTextures *textBeforeDialogs;
	//DialogueTextures *textAfterDialogs;
};