#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#include "MyScene.hpp"
#include <QMainWindow>
#include <QDebug>
#include <QColor>
#include <QMenuBar>
#include <QKeySequence>
#include <QGroupBox>
#include <QGraphicsView>
#include <QTimer>
#include <QColor>

class FenetrePrincipale : public QMainWindow {
	Q_OBJECT
	public:
		FenetrePrincipale();
		~FenetrePrincipale();
		QGroupBox *BuildGroupBoxControle();
		MyScene *myscene;
		QGraphicsView *myview;
	private:
		QWidget *widget_general;
		QMenu *menuFichier;
	public slots:
};

#endif
