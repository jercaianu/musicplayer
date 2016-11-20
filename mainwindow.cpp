#include "mainwindow.h"
#include "audioplayer.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) : 
QWidget(parent)
{
	setFixedSize(300, 300);

	m_button = new QPushButton("Play", this);
	m_button->setGeometry(10, 10, 80, 30);	

	connect(m_button, SIGNAL(clicked(bool)), 
		this, SLOT(slotPlayButtonClicked(bool)));
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

