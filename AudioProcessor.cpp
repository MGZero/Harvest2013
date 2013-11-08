#include "AudioProcessor.h"

FMOD::System * CAudioProcessor::_system = nullptr;
FMOD::Channel * CAudioProcessor::_streamChannel = nullptr;
channelMap CAudioProcessor::_soundChannels = channelMap();
std::queue<FMOD::Sound*> CAudioProcessor::_streamQueue = std::queue<FMOD::Sound*>();
std::queue<FMOD::Sound*> CAudioProcessor::_soundQueue = std::queue<FMOD::Sound*>();

void CAudioProcessor::initAudio()
{
	_system->init(32, FMOD_INIT_NORMAL, 0);
	FMOD::System_Create(&_system);
	
	//fill up the channel slots
	int i = 0;
	while (i < NUM_CHANNELS)
		_soundChannels.insert(std::make_pair(i++, std::make_pair(nullptr, false)));
}

void CAudioProcessor::tearDown()
{
	//stop any channels
	int i = 0;
	while (i < NUM_CHANNELS)
	{
		if (_soundChannels[i].first->isPlaying(&_soundChannels[i].second));
			_soundChannels[i].first->stop();
		i++;
	}

	if (_streamChannel != nullptr)
		_streamChannel->stop();

	//clear any queued sounds
	while (!_soundQueue.empty())
	{
		_soundQueue.back()->release();
		_soundQueue.pop();
	}

	while (!_streamQueue.empty())
	{
		_streamQueue.back()->release();
		_streamQueue.pop();
	}

	_system->close();
	_system->release();
}


void CAudioProcessor::playMusic(std::string music, int playCount)
{
	FMOD::Sound * playMe = nullptr;

	_system->createStream(music.c_str(), FMOD_HARDWARE | playCount == 0 ? FMOD_LOOP_OFF : FMOD_LOOP_NORMAL | FMOD_2D, 0, &playMe);
	_system->playSound(FMOD_CHANNEL_FREE, playMe, false, &_streamChannel);

	//queue the sound so we can clean it up later
	_streamQueue.push(playMe);
	
}

void CAudioProcessor::playSound(std::string sound)
{
	FMOD::Sound * playMe = nullptr;

	_system->createSound(sound.c_str(), FMOD_HARDWARE, 0, &playMe);
	
	//find an available sound channel
	int i = 0;
	
	while (i < NUM_CHANNELS)
	{
		if (!_soundChannels[i].first->isPlaying(&_soundChannels[i].second))
		{
			_system->playSound(FMOD_CHANNEL_FREE, playMe, false, &_soundChannels[i].first);
			_soundQueue.push(playMe);
			break;
		}
	}

	playMe->release();
	throw std::exception("Unable to play sound, out of channels");
}

