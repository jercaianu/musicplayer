#ifndef PHASEREFFECT_H
#define PHASEREFFECT_H

#include <string>
#include "FileWvIn.h"
#include "RtAudio.h"
#include "mainwindow.h"

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
	StkFloat oldInLeft[MAXSTAGES] = {};
	StkFloat oldInRight[MAXSTAGES] = {};
	StkFloat oldOutLeft[MAXSTAGES] = {};
	StkFloat oldOutRight[MAXSTAGES] = {};
};

class PhaserEffect : public QObject
{
	Q_OBJECT
public:
	StkFloat freq;
	StkFloat depth;
	StkFloat feedback;
	StkFloat range;
	int stages;
	PhaserState state;

	QSlider* phaserStages;
	QSlider* phaserFeedback;
	QSlider* phaserLFO;
	QSlider* phaserRange;
	QSlider* phaserDepth;

	PhaserEffect(QObject *parent = 0) : 
		freq(1.5), depth(0.75), feedback(0.1), range(0.5), stages(4)
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
	void connectSliders();

public slots:
	void setFreq(int val) {
		freq = (float)val / 100;
	}

	void setDepth(int val) {
		depth = (float)val / 100;
	}

	void setFeedback(int val) {
		feedback = (float)val / 100;
	}

	void setRange(int val) {
		range = (float)val / 100;
	}

	void setStages(int val) {
		stages = val;
	}
};
#endif