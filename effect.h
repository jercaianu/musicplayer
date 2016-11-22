#ifndef EFFECT_H
#define EFFECT_H

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

class Effect 
{
public:
	virtual void applyEffect(vector<StkFloat>& samples, int start, int end) = 0;
};

#endif