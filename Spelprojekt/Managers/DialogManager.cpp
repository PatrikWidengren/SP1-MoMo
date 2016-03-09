#include "DialogManager.h"

DialogManager::DialogManager(sf::RenderWindow &window)
{
	int mCurrentMapDialouge = 0;
	int mCurrentDialouge = 0;
	//qwespriteDialogs.setTexture(*textBeforeDialogs[mCurrentMapDialouge][mCurrentDialouge]);

	//	*spriteDialogs
	//	*textDialogs
}

DialogManager::~DialogManager()
{

}



#pragma region Play AfterDialouge
void DialogManager::playAfterDialouge(std::string wichMap, sf::RenderWindow &window)
{
		drawAfterDialouge(window);

	//std::cout << " Play Dialouge CHECK" << std::endl;	
	std::cout << "whichMap?: " << wichMap << std::endl;

}

void DialogManager::drawAfterDialouge(sf::RenderWindow &window)
{
	swapDialougeTexture(1);
	//window.draw(*spriteDialogs[mCurrentMapDialouge][mCurrentDialouge]);
	//std::cout << "DrawDialog( &window) CHECK " << std::endl;

}
#pragma endregion


//void DialogManager::playDialog(int wichMap, int time)
//{
//	mTimer++;
//	if (time * 60 > mTimer)
//	{
//		std::cout << " Play Dialouge GO!: "<< mTimer /60 << "  " << time << std::endl;
//	}
//}

#pragma region Play BeforeDialouge
void DialogManager::playBeforeDialouge(std::string wichMap, sf::RenderWindow &window)
{
		drawBeforeDialouge(window);

	//std::cout << " Play Dialouge CHECK" << std::endl;	
	std::cout << "whichMap?: " << wichMap << std::endl;

}

void DialogManager::drawBeforeDialouge(sf::RenderWindow &window)
{
	swapDialougeTexture(0);
	//window.draw(*spriteDialogs[mCurrentMapDialouge][mCurrentDialouge]);
	//std::cout << "DrawDialog( &window) CHECK " << std::endl;

}
#pragma endregion




void DialogManager::swapDialougeTexture(int beforeOrAfter)
{
	if (beforeOrAfter == 0)
	{
		//qwespriteDialogs.setTexture(*textBeforeDialogs[mCurrentBeforeMapDialouge][mCurrentDialouge]);
	}
	else
	{
		//qwespriteDialogs.setTexture(*textAfterDialogs[mCurrentAfterMapDialouge][mCurrentDialouge]);
	}
	mCurrentDialouge++;

}


#pragma region Edit Dialouge conditions
bool DialogManager::checkBeforeDialouge(std::string mapName)
{
	bool i = false;
	if (mapName == "map01a01" )
	{
		mCurrentBeforeMapDialouge = 0;
		i = true;
	}
	if (mapName == "map01a02")
	{
		mCurrentBeforeMapDialouge = 1;

		i = true;

	}
	return i;
}


bool DialogManager::checkAfterDialouge(std::string mapName)
{
	bool i = false;
	if (mapName == "map01a02")
	{
		mCurrentAfterMapDialouge = 1;
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