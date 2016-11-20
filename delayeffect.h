#ifndef DELAYEFFECT_H
#define DELAYEFFECT_H

#include <string>
#include "FileWvIn.h"
#include "RtAudio.h"
#include "audioplayer.h"

#include <vector>
#include <signal.h>
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;
using namespace stk;

class DelayEffect
{
public:
	float delayMilliseconds;
	float decayCoef;
	int delaySamplesCoef;

	DelayEffect() : delayMilliseconds(500), decayCoef(0.5), delaySamplesCoef(44.1)
	{

	}

	void applyEffect(vector<StkFloat>& samples, int start, int end);
};
#endif