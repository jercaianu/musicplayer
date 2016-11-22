#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QWidget>
#include <QCheckBox>
class QPushButton;
class MainWindow : public QWidget
{
	Q_OBJECT
    public:
        explicit MainWindow(QWidget *parent = 0);
    private:
    	QPushButton* playButton;
    	QCheckBox* delayCheckBox;
    	QCheckBox* phaserCheckBox;
    private slots:
    	void slotPlayButtonClicked(bool checked);
    	void slotPhaserToggled(bool checked);
    	void slotDelayToggled(bool checked);
};
#endif
