#pragma once
#include <SFML\Graphics.hpp>
#include <thread>
#include <string>
#include <iostream>
#include <list>
#include <fstream>


//#include "../GameStates/Map1.h" Used for "checkIfBeforeAfterDialogue" Maybe. //Fnatte
class DialogManager
{
private:

	std::string dialogue;
	bool isTyping;
	int currentLine;
	int endAtLine;
	bool quickText;
	bool pressDown;
	void scrollText(std::string lineOfText);
	sf::Text theText;
	

public:
	DialogManager(sf::RenderWindow &window);
	~DialogManager();
	void getDialogue(std::string file);
	void readText();

};