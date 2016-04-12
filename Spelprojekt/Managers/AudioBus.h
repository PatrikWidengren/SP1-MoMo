#pragma once
#include <FMOD/fmod_errors.h>
#include <FMOD/fmod_studio.hpp>
//#include "LogHandler.h"

class AudioBus
{
private:
	FMOD::Studio::Bus* bus;

	FMOD::Studio::System* system;

	FMOD_RESULT result;


public:
	AudioBus(const char* busName);

	FMOD::Studio::Bus* getBus();
	~AudioBus();
};