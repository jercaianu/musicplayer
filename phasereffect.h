#ifndef PHASEREFFECT_H
#define PHASEREFFECT_H

#include <string>
#include "FileWvIn.h"
#include "RtAudio.h"
#include "audioplayer.h"
#include "effect.h"

#include <vector>
#include <signal.h>
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;
using namespace stk;

#define MAXSTAGES 12

struct PhaserState {
	StkFloat leftPhase;
	StkFloat rightPhase;
	StkFloat oldInLeft[MAXSTAGES];
	StkFloat oldInRight[MAXSTAGES];
	StkFloat oldOutLeft[MAXSTAGES];
	StkFloat oldOutRight[MAXSTAGES];
};

class PhaserEffect : public Effect
{
public:
	StkFloat freq;
	StkFloat depth;
	StkFloat feedback;
	StkFloat range;
	int stages;
	PhaserState state;

	PhaserEffect() : 
		freq(2.0), depth(0.5), feedback(0.1), range(0.5), stages(8)
	{
		state.leftPhase = 0;
		state.rightPhase = 0;
		memset(state.oldInLeft, 0, MAXSTAGES * sizeof(StkFloat));
		memset(state.oldInRight, 0, MAXSTAGES * sizeof(StkFloat));
		memset(state.oldOutLeft, 0, MAXSTAGES * sizeof(StkFloat));
		memset(state.oldOutRight, 0, MAXSTAGES * sizeof(StkFloat));
	}

	inline StkFloat processSample(StkFloat input, StkFloat* oldIn, StkFloat* oldOut, StkFloat mainCoef) {
		for (int j = 0; j < stages; j++) {
            oldOut[j] = (mainCoef * input) + (mainCoef * oldOut[j]) - oldIn[j];
            oldIn[j] = input;
            input = oldOut[j];
        }
        return input;
	}

	void applyEffect(vector<StkFloat>& samples, int start, int end);
};
#endif