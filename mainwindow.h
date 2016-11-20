#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QWidget>
class QPushButton;
class MainWindow : public QWidget
{
	Q_OBJECT
    public:
        explicit MainWindow(QWidget *parent = 0);
    private:
    	QPushButton *m_button;
    private slots:
    	void slotPlayButtonClicked(bool checked);
};
#endif
