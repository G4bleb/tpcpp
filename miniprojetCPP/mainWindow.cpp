#include "mainWindow.hpp"
MainWindow::MainWindow() : QMainWindow() {
  this->setWindowTitle(tr("Lions et gazelles"));
  myscene=NULL;
  // le widget dans lequel tout s'affiche
  widget_general = new QWidget;
  // widget_general->resize (1200, 700);
  mainLayout = new QVBoxLayout;
  formLayout = new QFormLayout;
  secondLayout = new QVBoxLayout;
  tickSliderLayout = new QHBoxLayout;
  widget_general->setLayout(mainLayout);
  this->setCentralWidget(widget_general);
  //Construction Slider
  tickSlider = new QSlider(Qt::Horizontal);
  // tickSlider->setTickInterval(1);
  tickSlider->setMinimum(1);
  tickSlider->setMaximum(750);
  tickSlider->setValue(200);
  tickSliderLabel = new QLabel(tr("Délai boucle : ")+QString::number(tickSlider->value()));
  tickSliderLayout->addWidget(tickSliderLabel);
  tickSliderLayout->addWidget(tickSlider);
  //Construction Boutons Start/Quit, case plein écran, Boite config
  startButton = new QPushButton(tr("Début"));
  exitButton = new QPushButton(tr("Quitter"));
  fullscreenCheckBox = new QCheckBox(tr("Plein écran"));
  // QGroupBox * groupBoxConfig = new QGroupBox(tr("Configuration"));

  nbAnimSpinBox = new QSpinBox();
  nbAnimSpinBox->setMinimum(1);
  nbAnimSpinBox->setMaximum(2147483647);//4294967295
  nbAnimSpinBox->setValue(30);
  worldXSpinBox = new QSpinBox();
  worldXSpinBox->setMinimum(1);
  worldXSpinBox->setMaximum(2147483647);
  worldXSpinBox->setValue(30);
  worldYSpinBox = new QSpinBox();
  worldYSpinBox->setMinimum(1);
  worldYSpinBox->setMaximum(2147483647);
  worldYSpinBox->setValue(20);

  lionRateSpinBox = new QSpinBox();
  lionRateSpinBox->setMinimum(0);
  lionRateSpinBox->setMaximum(2147483647);
  lionRateSpinBox->setValue(1);
  gazelleRateSpinBox = new QSpinBox();
  gazelleRateSpinBox->setMinimum(0);
  gazelleRateSpinBox->setMaximum(2147483647);
  gazelleRateSpinBox->setValue(1);
  lifeSpinBox = new QSpinBox();
  lifeSpinBox->setMinimum(0);
  lifeSpinBox->setMaximum(2147483647);
  lifeSpinBox->setValue(100);
  healthThresholdSpinBox = new QSpinBox();
  healthThresholdSpinBox->setMinimum(0);
  healthThresholdSpinBox->setMaximum(100);
  healthThresholdSpinBox->setValue(25);
  birthHealthSpinBox = new QSpinBox();
  birthHealthSpinBox->setMinimum(0);
  birthHealthSpinBox->setMaximum(100);
  birthHealthSpinBox->setValue(50);
  birthCostSpinBox = new QSpinBox();
  birthCostSpinBox->setMinimum(0);
  birthCostSpinBox->setMaximum(healthThresholdSpinBox->value());
  birthCostSpinBox->setValue(20);

  formLayout->addRow(tr("Nombre d'animaux"),nbAnimSpinBox);
  formLayout->addRow(tr("Taille du monde en X"),worldXSpinBox);
  formLayout->addRow(tr("Taille du monde en Y"),worldYSpinBox);
  formLayout->addRow(tr("Ratio de Lions :"), lionRateSpinBox);
  formLayout->addRow(tr("Ratio de Gazelles :"), gazelleRateSpinBox);
  formLayout->addRow(tr("Energie initiale :"), lifeSpinBox);
  formLayout->addRow(tr("Seuil de bonne santé (en %) :"), healthThresholdSpinBox);
  formLayout->addRow(tr("Santé du nouveau-né (en %) :"), birthHealthSpinBox);
  formLayout->addRow(tr("Cout en santé de la reproduction (en %) :"), birthCostSpinBox);
  // configLayout->addStretch(1);

  // groupBoxConfig->setLayout(configLayout);
  // secondLayout->addWidget(groupBoxConfig);

  formLayout->addRow(startButton);

  secondLayout->addLayout(formLayout);

  secondLayout->addLayout(tickSliderLayout);
  secondLayout->addWidget(fullscreenCheckBox);
  secondLayout->addWidget(exitButton);

  connect(startButton, SIGNAL(clicked()), this, SLOT(slot_startButton()));
  connect(exitButton, SIGNAL(clicked()), this, SLOT(slot_exitButton()));
  connect(tickSlider, SIGNAL(valueChanged(int)),this, SLOT(slot_tickSlider(int)));
  connect(fullscreenCheckBox, SIGNAL(clicked(bool)), this, SLOT(slot_fullscreenCheckBox(bool)));
  connect(healthThresholdSpinBox, SIGNAL(valueChanged(int)), this, SLOT(slot_healthThresholdSpinBox(int)));

  // myview->setFixedSize(800, 600);
  // myview->setSceneRect(0, 0, 1200, 700);
  // myview->fitInView(widget_general);

  mainLayout->addLayout(secondLayout, 2);
  // mainLayout->setStretchFactor(formLayout,5);
  // this->adjustSize();
}

void MainWindow::slot_startButton(){
  //TODO put it in an array
  int signedParameters[] = {nbAnimSpinBox->value(), worldXSpinBox->value(), worldYSpinBox->value(), lionRateSpinBox->value(), gazelleRateSpinBox->value(), lifeSpinBox->value(), healthThresholdSpinBox->value(), birthHealthSpinBox->value(), birthCostSpinBox->value()};
  unsigned int nbParameters = sizeof(signedParameters);
  unsigned int parameters[nbParameters];
  for (unsigned int i = 0; i < 9; i++) {
    parameters[i] = static_cast<unsigned int>(signedParameters[i]);
  }
  myscene = new Scene(this, parameters);
  myview = new QGraphicsView(myscene, this);
  mainLayout->addWidget(myview);
  this->showMaximized();
  myscene->startup(tickSlider->value());
  while (formLayout->rowCount()) {
    formLayout->removeRow(0);
  }
}

void MainWindow::slot_exitButton(){
  QApplication::quit();
}

void MainWindow::slot_tickSlider(int value) {
  tickSliderLabel->setText(tr("Délai boucle : ")+QString::number(tickSlider->value()));
  if (myscene) {
    myscene->setTimerInterval(value);
  }
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

void MainWindow::slot_healthThresholdSpinBox(int value) {
  birthCostSpinBox->setMaximum(value);
}
