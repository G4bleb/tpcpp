#include "mainWindow.hpp"
MainWindow::MainWindow() : QMainWindow() {
  this->setWindowTitle("Lions et gazelles");
  // le widget dans lequel tout s'affiche
  widget_general = new QWidget;
  widget_general->resize (1200, 700);
  QHBoxLayout * qbl_general = new QHBoxLayout;
  widget_general->setLayout(qbl_general);
  this->setCentralWidget(widget_general);
  this->showMaximized();
  //exemple de creation d'une zone ou mettre boutons...
  // qbl_general->addWidget(BuildGroupBoxControle());
  // exemple de création d'un menu
  // menuFichier = menuBar()->addMenu(tr("&Fichier"));

  myscene = new Scene(this);
  myview = new QGraphicsView(myscene, this);

  // myview->setFixedSize(800, 600);
  // myview->setSceneRect(0, 0, 1200, 700);
  // myview->fitInView(widget_general);

  qbl_general->addWidget(myview);
  this->adjustSize();

}
MainWindow::~MainWindow() {
}
