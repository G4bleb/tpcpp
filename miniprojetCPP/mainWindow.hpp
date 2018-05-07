#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Scene.hpp"
#include <QMainWindow>
#include <QDebug>
#include <QColor>
#include <QMenuBar>
#include <QKeySequence>
// #include <QGroupBox>
#include <QGraphicsView>
#include <QTimer>
#include <QSlider>
#include <QCheckBox>


class MainWindow : public QMainWindow {
	Q_OBJECT
	public:
		MainWindow();
		~MainWindow();
		// QGroupBox *BuildGroupBoxControle();
		QPushButton * startButton;
		QPushButton * exitButton;
		Scene *myscene;
		QGraphicsView *myview;
		QSlider *tickSlider;
		QCheckBox *fullscreenCheckBox;
	private:
		QWidget *widget_general;
		// QMenu *menuFichier;
	public slots:
	void slot_startButton();
  void slot_exitButton();
	void slot_fullscreenCheckBox(bool state);
};

#endif
