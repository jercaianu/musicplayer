#include <string>
#include "FileWvIn.h"
#include "RtAudio.h"
#include "audioplayer.h"
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
	auto tmpSamples = samples;
	int delaySamples = delaySamplesCoef * delayMilliseconds;
    for (int i = start; i < end; i++) {
        if (i >= delaySamples)
            samples[i] += decayCoef * samples[i - delaySamples]; 
    }

}