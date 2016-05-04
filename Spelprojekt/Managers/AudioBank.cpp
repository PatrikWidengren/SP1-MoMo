#include "AudioBank.h"
#include <iostream>
#include "AudioHandler.h"


AudioBank::AudioBank(const char* file)
{
	system = AudioHandler::instance()->getSystem();

	result = system->loadBankFile(file, AudioHandler::instance()->getSampleFlags(), &bank);
	if (result != FMOD_OK)
	{
		std::string str = "Loading bank file: ";
		str += FMOD_ErrorString(result);
		LogHandler::error("AudioBank", str.c_str());
		bank = NULL;
		return;
	}
}

AudioBank::~AudioBank()
{
	if (bank)
	bank->unload();
}
