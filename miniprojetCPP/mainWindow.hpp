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
#include <QColor>

class MainWindow : public QMainWindow {
	Q_OBJECT
	public:
		MainWindow();
		~MainWindow();
		// QGroupBox *BuildGroupBoxControle();
		Scene *myscene;
		QGraphicsView *myview;
	private:
		QWidget *widget_general;
		// QMenu *menuFichier;
	public slots:
};

#endif
