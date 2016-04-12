#include "SoundManager.h"
#include <iostream>
#include <math.h>
#include <cstdlib>

using namespace std;

SoundManager::SoundManager(){
	//0-9 Klippare
	sndFile[0] = "Sound/Lawn Tools/HandHunter";
	sndFile[1] = "Sound/Lawn Tools/LawnMower1";
	//10-19 Häcksaxar
}

void SoundManager::loadSounds(int i)
{

	/*
	0-9 Klippare
	10-19 Häcksax
	20-49 Kollisionsljud
	*/



	switch (i) 
	{
	case 1: //Generic
	{
		int toload[] = { 0,1 };
		load(2, toload);
	}
		break;
	case 2: //Tempel
	{
		int toload[] = { 0,1 };
		load(2, toload);
	}
		break;
	case 3: //Asien
	{
		int toload[] = { 0,1 };
		load(2, toload);
	}
		break;
	case 4: //Is
		break;
	}
}




void SoundManager::load(int number, int sounds[])
{
	for (int j = 0; j<number; j++)
	{
		if (!mSound[sounds[j]]) //not already loaded
			mSound[sounds[j]] = new Audio(sndFile[sounds[j]].c_str());

		std::string str = "Loaded: ";
		str += sndFile[sounds[j]].c_str();
		str += " at index: ";
		str += std::to_string(j);


		LogHandler::log("Sound", str.c_str());
	}
}

void SoundManager::unload()
{
	for (int j = 0; j < numOfSounds; j++)
	{
		if (mSound[j]) 
		{
			std::string str = "Unloading sound at index: ";
			str += std::to_string(j);


			LogHandler::log("Sound", str.c_str());

			delete mSound[j];
			mSound[j] = NULL;
		}
	}
}

SoundManager::~SoundManager() {
	/*int i = numberOfSounds-1;
	while (!mSoundList.empty()) {
		//mSoundList[i]->stop();
		delete mSoundList[i];
		mSoundList.pop_back();
		i--;
	}
	i = numberOfSounds-1;
	while (!mSoundBufferList.empty()) {
		delete mSoundBufferList[i];
		mSoundBufferList.pop_back();
		i--;
	}*/
}


void SoundManager::playSound(int id){
	if (id >= 0 && id <= numOfSounds) {
		audio->play(mSound[id]);
	}
}

void SoundManager::stopSound(int id) {
	audio->stop(mSound[id]);
}

void SoundManager::setVolume(int volume){

	for (int i = 0; i < numOfSounds; i++){
			audio->setVolume(mSound[i], volume);
		}
}

void SoundManager::setParamValue(int id, const char* param, double value)
{
	audio->setParameterValue(mSound[id], param, value);
}

float SoundManager::getParamValue(int id, const char* param)
{
	float params = audio->getParameterValue(mSound[id], param);
	return params;
}
