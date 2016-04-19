#include <SFML/Graphics.hpp>
#include <Thor/Animations.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "gameState.h"
#include "Managers/MusicManager.h"
#include "Managers/SoundManager.h"
#include "Managers/AnimeManager.h"
#include "Managers/LogHandler.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main(){
	LogHandler::setFile("log.txt");
	LogHandler::log("Engine", "Start");

	sf::Texture titleTexture;
	sf::Sprite titleScreen;
	titleTexture.loadFromFile("Resource Files/Backgrounds/Loading_Screen.png");
	titleTexture.setSmooth(true);
	titleScreen.setTexture(titleTexture);
	sf::RenderWindow window(sf::VideoMode
		(sf::VideoMode::getDesktopMode().width, 
			sf::VideoMode::getDesktopMode().height, 
			sf::VideoMode::getDesktopMode().bitsPerPixel), "Mow Flow", sf::Style::Default);/*, sf::Style::Fullscreen*/

	titleScreen.setScale((float)window.getSize().x / 1920, (float)window.getSize().y / 1080);
	
	AudioHandler* audio = AudioHandler::instance();
	audio->init(24);

	AudioBank MasterBank("Resource Files/Audio/Build/Desktop/Master Bank.bank");
	AudioBank MSB("Resource Files/Audio/Build/Desktop/Master Bank.strings.bank");
	srand(time(NULL));

#pragma region SlaskTest

	//Setting the bus volumes here for testing:
	AudioBus Music("AudioPause/Music"); //All in game music probably
	AudioBus Sound("AudioPause/MainSounds/Sound"); //All world sounds
	AudioBus Voices("AudioPause/Voices"); //All dialogue
	AudioBus PauseSound("AudioPause"); //Used for lowering music when paused etc
	AudioBus MenuSound("AudioPause/MainSounds/MenuSounds"); //Digetic Menusounds
	AudioBus SoundMaster("AudioPause/MainSounds");
	AudioBus Ambience("Ambience");  //Ambience, like mowers
	AudioBus Master(""); //Overall volume

	audio->setBusVolume(&PauseSound, 1);
	audio->setBusVolume(&Music, 0);
	audio->setBusVolume(&Sound, 0.5);
	audio->setBusVolume(&Voices, 0.5);
	audio->setBusVolume(&MenuSound, 0.5);
	audio->setBusVolume(&Ambience, 0.5);
	audio->setBusVolume(&Master, 0.9);
	audio->setBusVolume(&SoundMaster, 1);

	//Works, there's also getters for busvolumes


#pragma endregion


	MusicManager mMusicManager("Music/Menu/Title");
	audio->run(); //idk where to put this.
	window.draw(titleScreen);
	window.display();

	sf::Vector2i mouse;
	AnimeManager mAnimeManager;
	SoundManager mSoundManager;
	gameState theGame(window);

	SaveVariables mSaveStuff;
	mSaveStuff.checkSaves(); //Skapar 5 sparfiler.
	LogHandler::log("Engine", "Initialized");
	LogHandler::log("-------------------------------------");

	while (window.isOpen()){
		sf::Event event;
		window.setFramerateLimit(60);
		audio->run(); //idk where to put this.
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed){
				mSoundManager.~SoundManager();
				mMusicManager.~MusicManager();
				audio->~AudioHandler();
				MasterBank.~AudioBank();
				MSB.~AudioBank();
				
				theGame.~gameState();
				window.close();
			}
			else if (event.type == sf::Event::Resized)
			{
				window.setView(sf::View(sf::FloatRect(0, 0, (float)event.size.width, (float)event.size.height)));
			}
		}
		mouse = sf::Mouse::getPosition(window);
		window.clear();
		theGame.gameStatesHandler(window, mouse, mMusicManager, mSoundManager, mAnimeManager);
#pragma region Fullscreen or Windowed
		
		if (theGame.mVideoOptionMenu->getFullscreen() && !theGame.mVideoOptionMenu->getSwap())
		{
			window.clear();
			window.close();
			window.create(sf::VideoMode
				(sf::VideoMode::getDesktopMode().width,
					sf::VideoMode::getDesktopMode().height,
					sf::VideoMode::getDesktopMode().bitsPerPixel),
				"Mow Flow", sf::Style::Fullscreen);
			cout << " Fullscreen ";
		}
		else if (!theGame.mVideoOptionMenu->getFullscreen() && theGame.mVideoOptionMenu->getSwap())
		{
			window.clear();
			window.close();
			window.create(sf::VideoMode
				(sf::VideoMode::getDesktopMode().width,
					sf::VideoMode::getDesktopMode().height,
					sf::VideoMode::getDesktopMode().bitsPerPixel),
				"Mow Flow");
			cout << " Windowed ";
		}
#pragma endregion

		//(fullscreen ? Style::Fullscreen : Style::Resize | Style::Close)
		window.display();
	}
	LogHandler::log("-------------------------------------");
	LogHandler::log("Engine", "End");
	return 0;
}

