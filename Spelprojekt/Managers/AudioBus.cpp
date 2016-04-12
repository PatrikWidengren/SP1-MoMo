#include "AudioBus.h"
#include "AudioHandler.h"
#include <iostream>


AudioBus::AudioBus(const char* busName)
{
	system = AudioHandler::instance()->getSystem();

	std::string s = "bus:/";
	s += busName;
	
	result = system->getBus(s.c_str(), &bus);
	if (result != FMOD_OK)
	{
		std::string str = "Finding bus: ";
		str += FMOD_ErrorString(result);
		LogHandler::error("AudioBus", str.c_str());
		bus = NULL;
		return;
	}
}

FMOD::Studio::Bus* AudioBus::getBus()
{
	return bus;
}

AudioBus::~AudioBus()
{
}
