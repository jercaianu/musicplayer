#include <string>
#include "FileWvIn.h"
#include "RtAudio.h"
#include "flangereffect.h"

#include <vector>
#include <signal.h>
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;
using namespace stk;

void FlangerEffect::applyEffect(vector<StkFloat>& samples, int start, int end)
{
    StkFloat* delayLeft = state.delayLeft;
    StkFloat* delayRight = state.delayRight;

    const int kChannels = 2;
    const int maxDelay = 1025;

    for (unsigned int i = start; i < end; i += kChannels) {
        delayLeft[coef] = samples[i];
        delayRight[coef] = samples[i+1];

        coef = (coef + 1) % maxDelay;

        time++;
        if (time > period) {
            time = 0;
        }

        StkFloat periodFraction = (StkFloat(time) )/ period;
        StkFloat delayParam = 250 + delay * sin(M_PI * 2.0f * periodFraction);

        int framePrev = (coef - (int)delayParam - 1) % maxDelay;
        int frameNext = (coef - (int)delayParam) % maxDelay;
        StkFloat prevLeft = delayLeft[framePrev];
        StkFloat nextLeft = delayLeft[frameNext];

        StkFloat prevRight = delayRight[framePrev];
        StkFloat nextRight = delayRight[frameNext];

        StkFloat frac = delayParam - floorf(delayParam);
        StkFloat delayedSampleLeft = prevLeft + frac * (nextLeft - prevLeft);
        StkFloat delayedSampleRight = prevRight + frac * (nextRight - prevRight);

        samples[i] = samples[i] + depth * delayedSampleLeft;
        samples[i+1] = samples[i+1] + depth * delayedSampleRight;
    }
}

void FlangerEffect::connectSliders()
{
	connect(flangerDepth, SIGNAL(valueChanged(int)), this, SLOT(setDepth(int)));
	connect(flangerDelay, SIGNAL(valueChanged(int)), this, SLOT(setDelay(int)));
	connect(flangerPeriod, SIGNAL(valueChanged(int)), this, SLOT(setPeriod(int)));
}
