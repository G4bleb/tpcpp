#include "mainwindow.hpp"

MainWindow::MainWindow() : QMainWindow() {
  this->setWindowTitle("TP7");
  this->setMinimumWidth(500);

  action_addtext = new QAction(tr("&Add text"), this);
  connect(action_addtext, SIGNAL(triggered()), this, SLOT(slot_addtext()));

  fileMenu = menuBar()->addMenu(tr("&File"));
  fileMenu->addAction(action_addtext);

  action_addtext->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));

  QWidget * widget_buttons = new QWidget;//A widget containing buttons
  QVBoxLayout * vLayout = new QVBoxLayout;//A VLayout
  widget_buttons->setLayout(vLayout);//The layout of widget_buttons is vLayout
  bouton1 = new QPushButton("You know I had to do it to em");
  bouton2 = new QPushButton("ColorStuff");
  textedit = new QTextEdit();
  vLayout->addWidget(bouton1);
  vLayout->addWidget(bouton2);
  vLayout->addWidget(textedit);
  connect(bouton1, SIGNAL(clicked()), this, SLOT(slot_bouton1()));
  connect(bouton2, SIGNAL(clicked()), this, SLOT(slot_bouton2()));
  this->setCentralWidget(widget_buttons);
}

MainWindow::~MainWindow() {
}

void MainWindow::slot_bouton1(){
  qDebug() << "bouton1 clicked";
  textedit->append("Got'em");
  // QMessageBox::information(this,"That's right","Got'em", QMessageBox::Ok);
}

void MainWindow::slot_bouton2(){
  qDebug() << "bouton2 clicked";
  QColor color = QColorDialog::getColor(Qt::green, this);
  if (color.isValid()) {
    textedit->setTextColor(color);
    qDebug() << "Couleur choisie : " << color;
  }
}

void MainWindow::slot_addtext(){
  textedit->append("The control point has been captured!");
}
