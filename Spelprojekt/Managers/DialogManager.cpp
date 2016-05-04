#include "DialogManager.h"

DialogManager::DialogManager(sf::RenderWindow &window)
{

}

DialogManager::~DialogManager()
{
}

void DialogManager::getDialogue(std::string file)
{
	std::ifstream f;

	f.open(file);
	if (f.is_open())
	{
		std::string content((std::istreambuf_iterator<char>(f)), (std::istreambuf_iterator<char>()));
		dialogue = content;
	}
}

void DialogManager::readText()
{



	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !pressDown)
	{
		pressDown = true;

		if (!isTyping)
		{
			currentLine += 1;

			if (currentLine > endAtLine)
			{
				//DisableTextBox();
			}
			else return;

		}
		else if (isTyping && !quickText)
		{
			quickText = true;
		}
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		pressDown = false;


	/*if (currentLine > endAtLine)
	{
		//DisableTextBox();
	}*/
}

void DialogManager::scrollText(std::string lineOfText)
{
	int letter = 0;
	theText.setString("");
	std::string str = "";
	isTyping = true;
	quickText = false;

	while (isTyping && !quickText && (letter < lineOfText.length() - 1))
	{
		str += lineOfText[letter];
		theText.setString(str);
		letter += 1;
		std::this_thread::sleep_for(std::chrono::milliseconds(12));
	}
	theText.setString(lineOfText);
	{
		if (currentLine == endAtLine)
		{
			isTyping = false;
			quickText = false;
		}
	}
	isTyping = false;
	quickText = false;
}
