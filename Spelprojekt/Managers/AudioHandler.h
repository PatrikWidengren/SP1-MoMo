#pragma once
#include "FMOD/fmod_errors.h"
#include "FMOD/fmod_studio.hpp"
#include "Audio.h"
#include "AudioBank.h"
#include "AudioBus.h"
#include "LogHandler.h"



class AudioHandler
{
private:
	FMOD::Studio::System* audioSys;
	FMOD::System* lowLevelSys;

	int driverCount;
	int maxChannels;
	void setMaxChannels(int channels);
	void *extraDriverData;
	float *paramval;

	bool sampleasync; 
	bool sampledecompress;

	FMOD_RESULT result;

	AudioHandler() {}

public:
	static AudioHandler* instance();

	void init(int channels);
	~AudioHandler();

	void run();

	FMOD_STUDIO_LOAD_BANK_FLAGS getSampleFlags()
	{
		//return FMOD_STUDIO_LOAD_BANK_NORMAL;
		return (FMOD_STUDIO_LOAD_BANK_NONBLOCKING*sampleasync) | (FMOD_STUDIO_LOAD_BANK_DECOMPRESS_SAMPLES*sampledecompress);
	}

	int getMaxChannels();

	void setSampleDecompress(bool enabled);
	void setSampleASync(bool enabled);
	void play(Audio* audio);
	void stop(Audio* audio);
	void pause(Audio* audio);
	void unpause(Audio* audio);
	void trigger(Audio* audio);
	void release(Audio* audio);

	void setVolume(Audio* audio, double vol);
	void setParameterValue(Audio* audio, const char* param, double value);
	void setPitch(Audio* audio, double pitch);
	void setTimePosition(Audio* audio, int position);

	void setBusVolume(AudioBus* bus, double vol);
	double getBusVolume(AudioBus* bus);


	float getParameterValue(Audio* audio, const char* param);



	FMOD::Studio::System* getSystem();
};

