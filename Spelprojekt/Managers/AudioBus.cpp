#include "AudioBus.h"
#include <iostream>
#include "AudioHandler.h"



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
		str += " ";
		str += s;
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
