#ifndef AUDIOPROCESSOR_H
#define AUDIPROCESSOR_H

#include "fmod.hpp"
#include <queue>
#include <string>
#include <unordered_map>

#define NUM_CHANNELS 32

typedef std::pair<FMOD::Channel*,bool> channelPair;
typedef std::unordered_map<int, channelPair> channelMap;

static class CAudioProcessor
{
public:
	static void initAudio();
	static void tearDown();
	static void playSound(std::string sound);
	static void playMusic(std::string music, int playCount);


private:
	static FMOD::System * _system;
	static FMOD::Channel * _streamChannel;
	static channelMap _soundChannels;

	static std::queue<FMOD::Sound*> _soundQueue;
	static std::queue<FMOD::Sound*> _streamQueue;
};

#endif