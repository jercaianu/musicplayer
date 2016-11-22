#include <string>
#include "FileWvIn.h"
#include "RtAudio.h"
#include "audioplayer.h"
#include "phasereffect.h"

#include <vector>
#include <signal.h>
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;
using namespace stk;

int updateCoef = 32;

void PhaserEffect::applyEffect(vector<StkFloat>& samples, int start, int end)
{
	StkFloat* oldInLeft = state.oldInLeft;
	StkFloat* oldOutLeft = state.oldOutLeft;
	StkFloat* oldInRight = state.oldInRight;
	StkFloat* oldOutRight = state.oldOutRight;

	StkFloat filterCoefLeft = 0;
	StkFloat filterCoefRight = 0;

	StkFloat left = 0;
	StkFloat right = 0;

 	int kChannels = 2;
	int counter = 0;
	StkFloat freqSkip = freq * 2.0 * M_PI / 44100;

    for (int i = start; i < end; i += kChannels) {

    	left = samples[i] + tanh(left * feedback);
    	right = samples[i + 1] + tanh(right * feedback);

    	state.leftPhase = fmod(state.leftPhase + freqSkip, 2.0 * M_PI);
    	state.rightPhase = fmod(state.rightPhase + freqSkip + M_PI, 2.0 * M_PI);

    	if ((counter++) % updateCoef == 0) {
	        StkFloat delayLeft = 0.5 + 0.5 * sin(state.leftPhase);
	        StkFloat delayRight = 0.5 + 0.5 * sin(state.rightPhase);

	        StkFloat wLeft = range * delayLeft;
	        StkFloat wRight = range * delayRight;

	        StkFloat tanwLeft = tanh(wLeft / 2);
	        StkFloat tanwRight = tanh(wRight / 2);

	        filterCoefLeft = (1.0 - tanwLeft) / (1.0 + tanwLeft);
	        filterCoefRight = (1.0 - tanwRight) / (1.0 + tanwRight);
    	}

    	left = processSample(left, state.oldInLeft, state.oldOutLeft, filterCoefLeft);
    	right = processSample(right, state.oldInRight, state.oldOutRight, filterCoefRight);

    	samples[i] = samples[i] * (1.0 - 0.5 * depth) + left * depth * 0.5;
    	samples[i + 1] = samples[i + 1] * (1.0 - 0.5 * depth) + right * depth * 0.5;
    }

}