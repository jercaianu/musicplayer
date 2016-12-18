#include "mainwindow.h"
#include "audioplayer.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) : 
QWidget(parent),
width(640),
height(480),
delayColPosition(0),
phaserColPosition(1),
effectColWidth(150),
windowEdgeDistance(100),
effectTopOffset(150),
effectRowHeight(50),
labelHeight(15)
{
	setFixedSize(width, height);

	double delayStartWidth = 
		windowEdgeDistance + delayColPosition * effectColWidth;
	double phaserStartWidth = 
		windowEdgeDistance + phaserColPosition * effectColWidth;

	playButton = new QPushButton("Play", this);
	playButton->setGeometry(10, 10, 80, 30);	
	connect(playButton, SIGNAL(clicked(bool)), 
		this, SLOT(slotPlayButtonClicked(bool)));

	phaserCheckBox = new QCheckBox("Phaser", this);
	phaserCheckBox->setGeometry(phaserStartWidth, effectTopOffset, 80, 30);	
	connect(phaserCheckBox, SIGNAL(toggled(bool)), 
		this, SLOT(slotPhaserToggled(bool)));

	delayCheckBox = new QCheckBox("Delay", this);
	delayCheckBox->setGeometry(delayStartWidth, effectTopOffset, 80, 30);	
	connect(delayCheckBox, SIGNAL(toggled(bool)), 
		this, SLOT(slotDelayToggled(bool)));

	delayDecay = new QSlider(Qt::Horizontal, this);
	delayDecay->setGeometry(delayStartWidth, effectTopOffset + effectRowHeight, 100, 30);
	delayDecay->setRange(100, 800);
	delayDecay->setValue(500);

	delayDecayText = new QLabel(this);
	delayDecayText->setText("Decay");
	delayDecayText->setGeometry(delayStartWidth, effectTopOffset + effectRowHeight - labelHeight, 100, 30);

	delayTimeDelay = new QSlider(Qt::Horizontal, this);
	delayTimeDelay->setGeometry(delayStartWidth, effectTopOffset + 2 * effectRowHeight, 100, 30);
	delayTimeDelay->setRange(100, 3000);
	delayTimeDelay->setValue(500);

	delayTimeDelayText = new QLabel(this);
	delayTimeDelayText->setText("Milliseconds");
	delayTimeDelayText->setGeometry(delayStartWidth, effectTopOffset + 2 * effectRowHeight - labelHeight, 100, 30);

	phaserStages = new QSlider(Qt::Horizontal, this);
	phaserStages->setGeometry(phaserStartWidth, effectTopOffset + effectRowHeight, 100, 30);
	phaserStages->setRange(2, 16);
	phaserStages->setValue(4);

	phaserStagesText = new QLabel(this);
	phaserStagesText->setText("Stages");
	phaserStagesText->setGeometry(phaserStartWidth, effectTopOffset + effectRowHeight - labelHeight, 100, 30);

	phaserFeedback = new QSlider(Qt::Horizontal, this);
	phaserFeedback->setGeometry(phaserStartWidth, effectTopOffset + 2 * effectRowHeight, 100, 30);
	phaserFeedback->setRange(0, 100);
	phaserFeedback->setValue(10);

	phaserFeedbackText = new QLabel(this);
	phaserFeedbackText->setText("Feedback");
	phaserFeedbackText->setGeometry(phaserStartWidth, effectTopOffset + 2 * effectRowHeight - labelHeight, 100, 30);

	phaserLFO = new QSlider(Qt::Horizontal, this);
	phaserLFO->setGeometry(phaserStartWidth, effectTopOffset + 3 * effectRowHeight, 100, 30);
	phaserLFO->setRange(0, 300);
	phaserLFO->setValue(50);

	phaserLFOText = new QLabel(this);
	phaserLFOText->setText("LFO");
	phaserLFOText->setGeometry(phaserStartWidth, effectTopOffset + 3 * effectRowHeight - labelHeight, 100, 30);

	phaserRange = new QSlider(Qt::Horizontal, this);
	phaserRange->setGeometry(phaserStartWidth, effectTopOffset + 4 * effectRowHeight, 100, 30);
	phaserRange->setRange(0, 500);
	phaserRange->setValue(100);

	phaserRangeText = new QLabel(this);
	phaserRangeText->setText("Range");
	phaserRangeText->setGeometry(phaserStartWidth, effectTopOffset + 4 * effectRowHeight - labelHeight, 100, 30);

	phaserDepth = new QSlider(Qt::Horizontal, this);
	phaserDepth->setGeometry(phaserStartWidth, effectTopOffset + 5 * effectRowHeight, 100, 30);
	phaserDepth->setRange(0, 500);
	phaserDepth->setValue(70);

	phaserDepthText = new QLabel(this);
	phaserDepthText->setText("Depth");
	phaserDepthText->setGeometry(phaserStartWidth, effectTopOffset + 5 * effectRowHeight - labelHeight, 100, 30);

	AudioPlayer::getInstance()->setupDelayEffect(delayDecay, delayTimeDelay);
	AudioPlayer::getInstance()->delayEffect.connectSliders();

	AudioPlayer::getInstance()->setupPhaserEffect(phaserStages, phaserFeedback, phaserLFO, phaserRange, phaserDepth);
	AudioPlayer::getInstance()->phaserEffect.connectSliders();

	connect(delayDecay, SIGNAL(valueChanged(int)), this, SLOT(debug(int)));
}

bool isPlaying = false;

void MainWindow::slotPlayButtonClicked(bool checked)
{
	if (!isPlaying) {
		AudioPlayer::getInstance()->play();
	}
	else 
		AudioPlayer::getInstance()->stop();
	isPlaying = !isPlaying;
}

void MainWindow::slotPhaserToggled(bool checked)
{
	AudioPlayer::getInstance()->currentEffect ^= 1;
}
void MainWindow::slotDelayToggled(bool checked)
{
	AudioPlayer::getInstance()->currentEffect ^= 2;
}

void MainWindow::debug(int val)
{
	cout << "value is " << (int *)delayDecay << endl;
}
