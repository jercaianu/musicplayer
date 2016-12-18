#include <string>
#include "FileWvIn.h"
#include "RtAudio.h"
#include "delayeffect.h"

#include <vector>
#include <signal.h>
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;
using namespace stk;

void DelayEffect::applyEffect(vector<StkFloat>& samples, int start, int end)
{
	int kChannels = 2;
	int delaySamples = delaySamplesCoef * delayMilliseconds;
    for (int i = start; i < end; i += kChannels) {
        if (i >= 2 * delaySamples) {
            samples[i] += decayCoef * samples[i - 2 * delaySamples];
            samples[i + 1] += decayCoef * samples[i + 1 - 2 * delaySamples];
        }
    }
}

void DelayEffect::connectSliders()
{
	connect(delayDecay, SIGNAL(valueChanged(int)), this, SLOT(setDecay(int)));
	connect(delayTimeDelay, SIGNAL(valueChanged(int)), this, SLOT(setTimeDelay(int)));
}

void DelayEffect::setDecay(int val) 
{
	decayCoef = (float)val / 1000;
}

void DelayEffect::setTimeDelay(int val)
{
	delayMilliseconds = (float)val;
}