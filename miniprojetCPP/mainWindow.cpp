#include "mainWindow.hpp"
MainWindow::MainWindow() : QMainWindow() {
  this->setWindowTitle("Lions et gazelles");
  // le widget dans lequel tout s'affiche
  widget_general = new QWidget;
  // widget_general->resize (1200, 700);
  QVBoxLayout * qbl_general = new QVBoxLayout;
  widget_general->setLayout(qbl_general);
  this->setCentralWidget(widget_general);
  this->showMaximized();
  //exemple de creation d'une zone ou mettre boutons...
  // qbl_general->addWidget(BuildGroupBoxControle());
  // exemple de création d'un menu
  // menuFichier = menuBar()->addMenu(tr("&Fichier"));
  tickSlider = new QSlider(Qt::Horizontal);
  tickSlider->setTickInterval(1);
  tickSlider->setMinimum(1);
  tickSlider->setMaximum(750);
  tickSlider->setValue(200);
  startButton = new QPushButton("Start");
  exitButton = new QPushButton("Quit");
  fullscreenCheckBox = new QCheckBox("Fullscreen");

  qbl_general->addWidget(startButton);
  qbl_general->addWidget(exitButton);
  qbl_general->addWidget(tickSlider);
  qbl_general->addWidget(fullscreenCheckBox);

  connect(startButton, SIGNAL(clicked()), this, SLOT(slot_startButton()));
  connect(exitButton, SIGNAL(clicked()), this, SLOT(slot_exitButton()));
  connect(fullscreenCheckBox, SIGNAL(clicked(bool)), this, SLOT(slot_fullscreenCheckBox(bool)));

  myscene = new Scene(this);
  myview = new QGraphicsView(myscene, this);

  // myview->setFixedSize(800, 600);
  // myview->setSceneRect(0, 0, 1200, 700);
  // myview->fitInView(widget_general);

  qbl_general->addWidget(myview);
  this->adjustSize();

}

void MainWindow::slot_startButton(){
  myscene->startup(tickSlider->value());
}

void MainWindow::slot_exitButton(){
  QApplication::quit();
}

void MainWindow::slot_fullscreenCheckBox(bool state) {
  if (state) {
    //set fullscreen
    this->showFullScreen();
  }else{
    //set windowed
    // this->showNormal();
    this->showMaximized();
  }
}

MainWindow::~MainWindow() {
}
