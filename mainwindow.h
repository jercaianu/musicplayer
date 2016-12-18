#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QWidget>
#include <QCheckBox>
#include <QAbstractSlider>
#include <QSlider>
#include <QLabel>

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

        QSlider* delayDecay;
        QSlider* delayTimeDelay;
        QSlider* phaserStages;
        QSlider* phaserFeedback;
        QSlider* phaserLFO;
        QSlider* phaserRange;
        QSlider* phaserDepth;

        QLabel* delayDecayText;
        QLabel* delayTimeDelayText;
        QLabel* phaserStagesText;
        QLabel* phaserFeedbackText;
        QLabel* phaserLFOText;
        QLabel* phaserRangeText;
        QLabel* phaserDepthText;

        double height;
        double width;
        int delayColPosition;
        int phaserColPosition;
        double effectColWidth;
        double windowEdgeDistance;
        double effectTopOffset;
        double effectRowHeight;
        double labelHeight;

    private slots:
    	void slotPlayButtonClicked(bool checked);
    	void slotPhaserToggled(bool checked);
    	void slotDelayToggled(bool checked);
        void debug(int val);
};
#endif
