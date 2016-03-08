#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <iostream>

class DialogManager
{
public:
	DialogManager(sf::RenderWindow &window);
	~DialogManager();
	void playDialog(int dialogID, int time);
	void drawDialogs();
private:
	int mTimer;
	sf::Sprite *spriteDialogs;
	sf::Texture *textDialogs;
};