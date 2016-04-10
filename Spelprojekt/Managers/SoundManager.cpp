#include "SoundManager.h"
#include <iostream>
#include <math.h>
#include <cstdlib>

using namespace std;

SoundManager::SoundManager(){
	mVolume = 35;
	mMowerVolume = 70;


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


	/*if (i >= 104 && i <= 106) {
		audio->setVolume(mSound[0], mMowerVolume * (mVolume / 100));
	}
	else {
		mSoundList[i]->setVolume(mVolume);
	}*/
}




void SoundManager::load(int number, int sounds[])
{
	for (int j = 0; j<number; j++)
	{
		if (!mSound[sounds[j]]) //not already loaded
			mSound[sounds[j]] = new Audio(sndFile[sounds[j]].c_str());
	}
}

void SoundManager::unload()
{
	for (int j = 0; j < numOfSounds; j++)
	{
		if (!mSound[j]) 
		{
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
	mVolume = volume;
	for (int i = 0; i < numOfSounds; i++){
		if (i >= 0 && i <= 0) {
			audio->setVolume(mSound[0], mMowerVolume * (mVolume / 100));
		}
		else {
			audio->setVolume(mSound[i], mVolume);
		}
	}
}

void SoundManager::setMowerVolume(int mowerVolume) {
	mMowerVolume = mowerVolume;
	audio->setVolume(mSound[0], mMowerVolume * (mVolume / 100));
}

void SoundManager::setParamValue(int id, const char* param, double value)
{
	audio->setParameterValue(mSound[id], param, value);
}

int SoundManager::getVolume() {
	return mVolume;
}