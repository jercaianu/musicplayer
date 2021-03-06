#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <string>
#include "FileWvIn.h"
#include "RtAudio.h"
#include "mainwindow.h"
#include "delayeffect.h"
#include "flangereffect.h"
#include "phasereffect.h"

#include <QSemaphore>
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
	QSemaphore finishSem;
	PhaserEffect phaserEffect;
	DelayEffect delayEffect;
	FlangerEffect flangerEffect;
	vector<StkFloat> samplesIn;
	vector<StkFloat> samplesOut;
	RtAudio* dac;
	FileWvIn initInput;
    FileWvIn input;
    StkFrames frames;
    StkFloat sampleRate;
    RtAudioFormat format;
    RtAudio::StreamParameters parameters;
    QSlider* delayDecay;
    QSlider* delayTimeDelay;
    unsigned int bufferFrames;
    double rate;
    int channels;
    bool done;
    bool isOpen;
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

	void setupDelayEffect(QSlider* delayDecay, QSlider* delayTimeDelay);
	void setupPhaserEffect(QSlider* phaserStages, QSlider* phaserFeedback, QSlider* phaserLFO, 
						   QSlider* phaserRange, QSlider* phaserDepth);
	void setupFlangerEffect(QSlider* flangerDelay, QSlider* flangerPeriod, QSlider* flangerDepth);
	void loadSong(string filename);
	void openStream();
	void closeStream();
	void play();
	void stop();
	void setSampleRate(StkFloat sampleRate);
};

#endif