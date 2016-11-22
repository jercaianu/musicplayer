#include "mainwindow.h"
#include "audioplayer.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) : 
QWidget(parent)
{
	setFixedSize(300, 300);

	playButton = new QPushButton("Play", this);
	playButton->setGeometry(10, 10, 80, 30);	
	connect(playButton, SIGNAL(clicked(bool)), 
		this, SLOT(slotPlayButtonClicked(bool)));

	phaserCheckBox = new QCheckBox("Phaser", this);
	phaserCheckBox->setGeometry(60, 60, 80, 30);	
	connect(phaserCheckBox, SIGNAL(toggled(bool)), 
		this, SLOT(slotPhaserToggled(bool)));

	delayCheckBox = new QCheckBox("Delay", this);
	delayCheckBox->setGeometry(110, 110, 80, 30);	
	connect(delayCheckBox, SIGNAL(toggled(bool)), 
		this, SLOT(slotDelayToggled(bool)));


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
