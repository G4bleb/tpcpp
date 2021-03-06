#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Scene.hpp"
#include <QMainWindow>
#include <QColor>
#include <QGraphicsView>
#include <QTimer>
#include <QSlider>
#include <QCheckBox>
#include <QLabel>
#include <QSpinBox>


class MainWindow : public QMainWindow {
	Q_OBJECT
public:
	MainWindow();
private:
	//Layouts
	QVBoxLayout * mainLayout;
	QFormLayout * formLayout;
	QVBoxLayout * secondLayout;
	QPushButton * startButton;
	QPushButton * exitButton;
	QWidget *mainWidget;
	Scene *myscene;
	QGraphicsView *myview;
	QSlider *tickSlider;
	QHBoxLayout *tickSliderLayout;
	QLabel *tickSliderLabel;
	QCheckBox *fullscreenCheckBox;
	QSpinBox *nbAnimSpinBox;
	QSpinBox *worldXSpinBox;
	QSpinBox *worldYSpinBox;
	QSpinBox *lionRateSpinBox;
	QSpinBox *gazelleRateSpinBox;
	QSpinBox *lifeSpinBox;
	QSpinBox *healthThresholdSpinBox;
	QSpinBox *birthHealthSpinBox;
	QSpinBox *birthCostSpinBox;
	public slots:
	void slot_tickSlider(int value);
	void slot_startButton();
	void slot_exitButton();
	void slot_fullscreenCheckBox(bool state);
	void slot_healthThresholdSpinBox(int value);
};

#endif
