#include "DialogManager.h"

DialogManager::DialogManager(sf::RenderWindow &window)
{
	int mCurrentMapDialogue = 0;
	int mCurrentDialogue = 0;
	//qwespriteDialogs.setTexture(*textBeforeDialogs[mCurrentMapDialogue][mCurrentDialogue]);

	//	*spriteDialogs
	//	*textDialogs
}

DialogManager::~DialogManager()
{

}



#pragma region Play AfterDialogue
void DialogManager::playAfterDialogue(std::string wichMap, sf::RenderWindow &window)
{
		drawAfterDialogue(window);

	//std::cout << " Play Dialogue CHECK" << std::endl;	
	std::cout << "whichMap?: " << wichMap << std::endl;

}

void DialogManager::drawAfterDialogue(sf::RenderWindow &window)
{
	swapDialogueTexture(1);
	//window.draw(*spriteDialogs[mCurrentMapDialogue][mCurrentDialogue]);
	//std::cout << "DrawDialog( &window) CHECK " << std::endl;

}
#pragma endregion


//void DialogManager::playDialog(int wichMap, int time)
//{
//	mTimer++;
//	if (time * 60 > mTimer)
//	{
//		std::cout << " Play Dialogue GO!: "<< mTimer /60 << "  " << time << std::endl;
//	}
//}

#pragma region Play BeforeDialogue
void DialogManager::playBeforeDialogue(std::string wichMap, sf::RenderWindow &window)
{
		drawBeforeDialogue(window);

	//std::cout << " Play Dialogue CHECK" << std::endl;	
	std::cout << "whichMap?: " << wichMap << std::endl;

}

void DialogManager::drawBeforeDialogue(sf::RenderWindow &window)
{
	swapDialogueTexture(0);
	//window.draw(*spriteDialogs[mCurrentMapDialogue][mCurrentDialogue]);
	//std::cout << "DrawDialog( &window) CHECK " << std::endl;

}
#pragma endregion




void DialogManager::swapDialogueTexture(int beforeOrAfter)
{
	if (beforeOrAfter == 0)
	{
		//qwespriteDialogs.setTexture(*textBeforeDialogs[mCurrentBeforeMapDialogue][mCurrentDialogue]);
	}
	else
	{
		//qwespriteDialogs.setTexture(*textAfterDialogs[mCurrentAfterMapDialogue][mCurrentDialogue]);
	}
	mCurrentDialogue++;

}


#pragma region Edit Dialogue conditions
bool DialogManager::checkBeforeDialogue(std::string mapName)
{
	bool i = false;
	if (mapName == "map01a01" )
	{
		mCurrentBeforeMapDialogue = 0;
		i = true;
	}
	if (mapName == "map01a02")
	{
		mCurrentBeforeMapDialogue = 1;

		i = true;

	}
	return i;
}

bool DialogManager::checkAfterDialogue(std::string mapName)
{
	bool i = false;
	if (mapName == "map01a02")
	{
		mCurrentAfterMapDialogue = 1;
		i = true;
	}

	return i;
}
#pragma endregion

void DialogManager::setTextures()
{
	////map01a01
	//			//Beforetexture
				//textBeforeDialogs[0][0]->loadFromFile();
				//textBeforeDialogs[0][1]->loadFromFile();
				//textBeforeDialogs[0][2]->loadFromFile();

				////Aftertexture


	////map01a02
				////Beforetexture
			/*	textBeforeDialogs[0][0]->loadFromFile();
				textBeforeDialogs[0][1]->loadFromFile();
				textBeforeDialogs[0][2]->loadFromFile();*/

				////Aftertexture
	/*			textAfterDialogs[0][0]->loadFromFile();
				textAfterDialogs[0][1]->loadFromFile();
				textAfterDialogs[0][2]->loadFromFile();
				textAfterDialogs[0][3]->loadFromFile();*/

#pragma region Copy & Paste Templates

				////map01a02
				////Beforetexture
				//textBeforeDialogs[0][0]->loadFromFile();
				//textBeforeDialogs[0][1]->loadFromFile();
				//textBeforeDialogs[0][2]->loadFromFile();
				//textBeforeDialogs[0][3]->loadFromFile();

				////Aftertexture
				//textAfterDialogs[0][0]->loadFromFile();
				//textAfterDialogs[0][1]->loadFromFile();
				//textAfterDialogs[0][2]->loadFromFile();
				//textAfterDialogs[0][3]->loadFromFile();

#pragma endregion



}