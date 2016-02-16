#include "SoundManager.h"
#include <iostream>

static const std::string nameArray[2] = { "Resource Files/Sound/kollision_sten.flac", "Resource Files/Sound/kollision_vas.flac" };
int asd;

SoundManager::SoundManager(){
	for (int i = 0; i < 2; i++){
		mSoundBuffer.loadFromFile(nameArray[i]); //mNameArry har igent i sig än, ****************** ladda från txt?
		mSoundList.push_back(new sf::Sound);
		mSoundList[i]->setBuffer(mSoundBuffer);
	}
}

SoundManager::~SoundManager(){
}


void SoundManager::playSound(float id){
	asd = (int)id * 10;
	mSoundList[asd]->play();
}