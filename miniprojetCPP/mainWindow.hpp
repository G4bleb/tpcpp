#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Scene.hpp"
#include <QMainWindow>
#include <QDebug>
#include <QColor>
#include <QMenuBar>
#include <QKeySequence>
#include <QGroupBox>
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
		QVBoxLayout * mainLayout;
	  QFormLayout * formLayout;
	  QVBoxLayout * secondLayout;
		QPushButton * startButton;
		QPushButton * exitButton;
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
		// QLabel *nbAnimalsLabel;
		// QLabel *victimsLabel;
		QWidget *widget_general;
		// QMenu *menuFichier;
	public slots:
	void slot_tickSlider(int value);
	void slot_startButton();
  void slot_exitButton();
	void slot_fullscreenCheckBox(bool state);
};

#endif
