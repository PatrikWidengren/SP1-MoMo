#include "DialogManager.h"

DialogManager::DialogManager(sf::RenderWindow &window)
{
	mTimer = 0;
	int mCurrentMapDialogue = 0;
	int mCurrentDialogue = 0;
	setTextures();
	spriteDialogs->setPosition(0,0);
	spriteDialogs->setScale((float)window.getSize().x / 1920, (float)window.getSize().y / 1080);
}

DialogManager::~DialogManager()
{
	for (int i = 0; i < 23; i++)
	{
		delete textureMap01a01BeforeDialogue[i];

	}

	delete spriteDialogs;
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


#pragma region Play BeforeDialogue
void DialogManager::playBeforeDialogue(std::string wichMap, sf::RenderWindow &window)
{
		mTimer++;
		drawBeforeDialogue(window);

	//std::cout << " Play Dialogue CHECK" << std::endl;	
	//std::cout << "whichMap?: " << wichMap << "   " << mCurrentBeforeMapDialogue << "   " << mTimer << std::endl;

}

void DialogManager::drawBeforeDialogue(sf::RenderWindow &window)
{

	swapDialogueTexture(0);
	window.draw(*spriteDialogs);
	//if (mTimer >= 4 * 60 && j > 0)
	//{
	//	spriteDialogs->setColor(sf::Color(255, 255, 255, j));
	//	j-=(255/35);
	//}

	/*window.draw(*spriteDialogs[mCurrentMapDialogue][mCurrentDialogue]);
	std::cout << "DrawDialog( &window) CHECK " << std::endl;
*/
}
#pragma endregion




void DialogManager::swapDialogueTexture(int beforeOrAfter)
{
	if (beforeOrAfter == 0)
	{
		//spriteDialogs.setTexture(*textBeforeDialogs[mCurrentBeforeMapDialogue][mCurrentDialogue]);
		//spriteDialogs.setTexture(*textBeforeDialogstest[mCurrentBeforeMapDialogue][mCurrentDialogue]);
		spriteDialogs->setTexture(*textureMap01a01BeforeDialogue[mCurrentDialogue]);

	}
	else
	{
		//qwespriteDialogs.setTexture(*textAfterDialogs[mCurrentAfterMapDialogue][mCurrentDialogue]);
	}
	//mCurrentDialogue++;

}


#pragma region Edit Dialogue conditions
bool DialogManager::checkBeforeDialogue(std::string mapName)
{
	if (mapName == "map01a01.txt" )
	{
		mCurrentBeforeMapDialogue = 0;

		i = true;
	}
	//if (mapName == "map01a02.txt" )
	//{
	//	mCurrentBeforeMapDialogue = 1;

	//	i = true;

	//}
	if (mCurrentDialogue >= 22)
		i = false;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClick)
	{
		mClick = false;

		if (mCurrentDialogue <= 22)
			mCurrentDialogue++;
	
	}
	else if(mCurrentDialogue >= 22)
	{
		spriteDialogs->setColor(sf::Color(255, 255, 255, 0));
		i = false;
	}
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mClick) {
		mClick = true;
	}

	return i;
}

bool DialogManager::checkAfterDialogue(std::string mapName)
{
	bool i = false;
	//if (mapName == "map01a02.txt" )
	//{
	//	mCurrentAfterMapDialogue = 1;
	//	i = true;
	//}

	return i;
}
#pragma endregion

void DialogManager::setTextures()
{
	//map01a01
				//Beforetexture
	for (int i = 0; i < 23; i++)
	{
		textureMap01a01BeforeDialogue[i] = new sf::Texture();
		//textureMap01a01BeforeDialogue[i] = new sf::Texture();
		std::cout << "Loop: " << i;
		textureMap01a01BeforeDialogue[i]->loadFromFile(writeDialogSearchName(i+1));

		//textureMap01a01BeforeDialogue[i]->loadFromFile("Resource Files/Dialogue/" + writeDialogSearchName(i));
	}

	//textureMap01a01BeforeDialogue[0]->loadFromFile("Resource Files/Dialogue/Before01a01 0.png");

						//	textureMap01a01Dialogue->loadFromFile("Resource Files/Dialogue/Before01a01 0.png");
				//textBeforeDialogstest[0][0]->loadFromFile("Resource Files/Dialogue/Before01a01 0.png");
				//textBeforeDialogs[0][1]->loadFromFile("Resource Files/Dialogue/Before01a01 1.png");
				//textBeforeDialogs[0][2]->loadFromFile("Resource Files/Dialogue/Before01a01 2.png");

				//Aftertexture


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

std::string DialogManager::writeDialogSearchName(int d)
{
	//"Resource Files/Dialogue/TutorialDialogs/" 
	std::ostringstream o;
	o << "Resource Files/Dialogue/TutorialDialogs/" << d << ".png";
	return o.str();
}
