#ifndef DELAYEFFECT_H
#define DELAYEFFECT_H

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


class DelayEffect : public QObject
{
	Q_OBJECT
public:
	float delayMilliseconds;
	float decayCoef;
	int delaySamplesCoef;
	QSlider* delayDecay;
	QSlider* delayTimeDelay;

	DelayEffect(QObject *parent = 0) : 
		delayMilliseconds(500), 
		decayCoef(0.5), 
		delaySamplesCoef(44.1)
	{

	}

	void connectSliders();
	void applyEffect(vector<StkFloat>& samples, int start, int end);
public slots:
	void setDecay(int val);
	void setTimeDelay(int val);
};
#endif