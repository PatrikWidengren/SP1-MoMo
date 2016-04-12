#include "AudioHandler.h"
#include <iostream>

AudioHandler* AudioHandler::instance()
{
	static AudioHandler audiohandler;
	return &audiohandler;
}

void AudioHandler::init(int channels)
{
	LogHandler::log("Audio", "Start");
	extraDriverData = NULL;
	audioSys = NULL;
	lowLevelSys = NULL;
	result = FMOD::Studio::System::create(&audioSys);

	if (result != FMOD_OK)
	{
		LogHandler::error("Audio", "Failed to create sound system.");
		return;
	}

	//Low Level stuff
	
	result = audioSys->getLowLevelSystem(&lowLevelSys);
	if (result != FMOD_OK)
	{
		LogHandler::error("Audio", "Failed to get low level sound system.");
		return;
	}

	result = (lowLevelSys->setSoftwareFormat(0, FMOD_SPEAKERMODE_STEREO, 0));

	if (result != FMOD_OK)
	{
		LogHandler::error("Audio", "Failed to set software audio format."); 
		return;
	}

	//Cool Stuff
	setMaxChannels(channels);

	//Initialize FMOD instance with 12 channels
	result = audioSys->initialize(channels, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, extraDriverData);
	if (result != FMOD_OK)
	{
		LogHandler::error("Audio", FMOD_ErrorString(result));
	}

	setSampleASync(false); 
	setSampleDecompress(false);

	LogHandler::log("Audio", "Initialized");
}

void AudioHandler::setMaxChannels(int channels)
{
	maxChannels = channels;
}

int AudioHandler::getMaxChannels()
{
	return maxChannels;
}

void AudioHandler::setSampleDecompress(bool enabled)
{
	sampledecompress = enabled;
}
void AudioHandler::setSampleASync(bool enabled)
{
	sampleasync = enabled;
}

FMOD::Studio::System* AudioHandler::getSystem()
{
	return audioSys;
}

void AudioHandler::play(Audio* audio)
{
	if (audio->getInstance())
		audio->getInstance()->start();
	else
		LogHandler::notify("Audio", "Attempting to play unloaded sound.");
}

void AudioHandler::stop(Audio* audio)
{
	if (audio->getInstance())
		audio->getInstance()->stop(FMOD_STUDIO_STOP_IMMEDIATE);
	else
		LogHandler::notify("Audio", "Attempting to stop unloaded sound.");
}

void AudioHandler::run()
{
	audioSys->update();
}

void AudioHandler::pause(Audio* audio)
{
	if (audio->getInstance())
		audio->getInstance()->setPaused(true);
	else
		LogHandler::notify("Audio", "Attempting to pause unloaded sound.");
}

void AudioHandler::unpause(Audio* audio)
{
	if (audio->getInstance())
		audio->getInstance()->setPaused(false);
	else
		LogHandler::notify("Audio", "Attempting to unpause unloaded sound.");
}

void AudioHandler::trigger(Audio* audio)
{
	//Makes the cursor able to move past a sustain point
	if (audio->getInstance())
		audio->getInstance()->triggerCue();
	else
		LogHandler::notify("Audio", "Attempting to trigger unloaded sound.");
}

void AudioHandler::release(Audio* audio)
{
	//Destroys the event
	if (audio->getInstance())
		audio->getInstance()->release();
	else
	LogHandler::notify("Audio", "Attempting to release unloaded sound.");
}

void AudioHandler::setVolume(Audio* audio, double vol)
{
	if (audio->getInstance())
		audio->getInstance()->setVolume((float)(vol>1.0f ? 1.0f : (vol<0.0f ? 0.0f : vol)));
	else
	LogHandler::notify("Audio", "Attempting to set volume of an unloaded sound.");
}

void AudioHandler::setParameterValue(Audio* audio, const char* param, double value)
{
	if (audio->getInstance())
		audio->getInstance()->setParameterValue(param, (float)value);
	else
	LogHandler::notify("Audio", "Attempting to set parameter value of an unloaded sound.");
}

float AudioHandler::getParameterValue(Audio* audio, const char* param)
{
	float paramval = 0;
	if (audio->getInstance())
		audio->getInstance()->getParameterValue(param, &paramval);

	return paramval;
}

void AudioHandler::setPitch(Audio* audio, double pitch)
{
	audio->getInstance()->setPitch((float)pitch);
}

void AudioHandler::setTimePosition(Audio* audio, int position)
{
	//Timeline position in milliseconds
	if (audio->getInstance())
		audio->getInstance()->setTimelinePosition(position);
	else
	LogHandler::notify("Audio", "Attempting to set time position of an unloaded sound.");
	
}

void AudioHandler::setBusVolume(AudioBus* bus, double vol)
{
	if (bus->getBus())
		bus->getBus()->setFaderLevel(vol);
	else
		LogHandler::notify("Audio", "Attempting to set volume of an unexisting bus.");
}

double getBusVolume(AudioBus* bus)
{
	float busvol = 0;
	if (bus->getBus())
		return bus->getBus()->getFaderLevel(&busvol);

	return busvol;
}

AudioHandler::~AudioHandler()
{
	audioSys->unloadAll();
	audioSys->release();
	//LogHandler::log("Audio", "End");
}
