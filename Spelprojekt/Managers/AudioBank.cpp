#include "AudioBank.h"
#include "AudioHandler.h"
#include <iostream>


AudioBank::AudioBank(const char* file)
{
	system = AudioHandler::instance()->getSystem();

	result = system->loadBankFile(file, AudioHandler::instance()->getSampleFlags(), &bank);
	if (result != FMOD_OK)
	{
		std::string str = "Loading bank file: ";
		str += FMOD_ErrorString(result);
		//LogHandler::error("Audio", str.c_str());
		bank = NULL;
		return;
	}
}

AudioBank::~AudioBank()
{
	if (bank)
	bank->unload();
}
