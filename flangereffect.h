#ifndef FLANGEREFFECT_H
#define FLANGEREFFECT_H

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

struct FlangerState {
	StkFloat delayRight[5001] = {};
    StkFloat delayLeft[5001] = {};
};

class FlangerEffect : public QObject
{
	Q_OBJECT
public:
	StkFloat depth;
	StkFloat period;
	StkFloat delay;
	unsigned int time;
	unsigned int coef;

	FlangerState state;

	QSlider* flangerDepth;
	QSlider* flangerPeriod;
	QSlider* flangerDelay;

	FlangerEffect(QObject* parent = 0) : 
		time(0), coef(0), depth(0.5), period(70000), delay(250) 
	{
		
	}

	void applyEffect(vector<StkFloat>& samples, int start, int end);
	void connectSliders();

public slots:
	void setDepth(int val) {
		depth = (StkFloat)val / 100;
	}

	void setPeriod(int val) {
		period = val;
	}

	void setDelay(int val) {
		delay = val;
	}
};
#endif