#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <string>
#include "FileWvIn.h"
#include "RtAudio.h"
#include "delayeffect.h"
#include "phasereffect.h"

#include <vector>
#include <signal.h>
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;
using namespace stk;

class AudioPlayer
{
private:
	AudioPlayer();
	static AudioPlayer* instance;

public:
	PhaserEffect phaserEffect;
	DelayEffect delayEffect;
	vector<StkFloat> samplesIn;
	vector<StkFloat> samplesOut;
	RtAudio dac;
	FileWvIn initInput;
    FileWvIn input;
    StkFrames frames;
    StkFloat sampleRate;
    RtAudioFormat format;
    RtAudio::StreamParameters parameters;
    unsigned int bufferFrames;
    double rate;
    int channels;
    bool done;
    int ind;
    int currentEffect;
    static int tick(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
        double streamTime, RtAudioStreamStatus status, void *userData);

    
public:
	
	static AudioPlayer* getInstance()
	{
	    if (!instance)
			instance = new AudioPlayer();
    	return instance;
	}

	void loadSong(string filename);
	void openStream();
	void play();
	void stop();
	void setSampleRate(StkFloat sampleRate);
};

#endif