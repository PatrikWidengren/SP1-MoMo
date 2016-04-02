#pragma once
#include <FMOD/fmod_errors.h>
#include <FMOD/fmod_studio.hpp>
//#include "LogHandler.h"

class AudioHandler;

class AudioBank
{
private:
	FMOD::Studio::Bank* bank;
	FMOD::Studio::System* system;

	FMOD_RESULT result;


public:
	AudioBank(const char* file);
	~AudioBank();
};

