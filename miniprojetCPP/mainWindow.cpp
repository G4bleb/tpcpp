#include "mainWindow.hpp"
MainWindow::MainWindow() : QMainWindow() {
  this->setWindowTitle(tr("Lions et gazelles"));
  myscene=NULL;
  mainWidget = new QWidget;
  mainLayout = new QVBoxLayout;
  formLayout = new QFormLayout;
  secondLayout = new QVBoxLayout;
  tickSliderLayout = new QHBoxLayout;
  mainWidget->setLayout(mainLayout);
  this->setCentralWidget(mainWidget);
  //Construction : Slider
  tickSlider = new QSlider(Qt::Horizontal);
  tickSlider->setMinimum(1);
  tickSlider->setMaximum(750);
  tickSlider->setValue(200);
  tickSliderLabel = new QLabel(tr("Délai entre chaque tour : ")+QString::number(tickSlider->value()));
  tickSliderLayout->addWidget(tickSliderLabel);
  tickSliderLayout->addWidget(tickSlider);
  //Construction : Boutons Start/Quit, case plein écran
  startButton = new QPushButton(tr("Début"));
  exitButton = new QPushButton(tr("Quitter"));
  fullscreenCheckBox = new QCheckBox(tr("Plein écran"));
  //Contruction SpinBoxes
  nbAnimSpinBox = new QSpinBox();
  nbAnimSpinBox->setMinimum(1);
  nbAnimSpinBox->setMaximum(2147483647);//Si les QSpinBoxes pouvaient contenir des entiers non signés, on aurait pu avoir un maximum de 4294967295
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
  lionRateSpinBox->setSuffix(tr(" lion pour"));
  gazelleRateSpinBox = new QSpinBox();
  gazelleRateSpinBox->setMinimum(0);
  gazelleRateSpinBox->setMaximum(2147483647);
  gazelleRateSpinBox->setValue(1);
  gazelleRateSpinBox->setSuffix(tr(" gazelle"));

  lifeSpinBox = new QSpinBox();
  lifeSpinBox->setMinimum(0);
  lifeSpinBox->setMaximum(2147483647);
  lifeSpinBox->setValue(100);
  healthThresholdSpinBox = new QSpinBox();
  healthThresholdSpinBox->setMinimum(0);
  healthThresholdSpinBox->setMaximum(100);
  healthThresholdSpinBox->setValue(25);
  healthThresholdSpinBox->setSuffix(" %");
  birthHealthSpinBox = new QSpinBox();
  birthHealthSpinBox->setMinimum(0);
  birthHealthSpinBox->setMaximum(100);
  birthHealthSpinBox->setValue(50);
  birthHealthSpinBox->setSuffix(" %");
  birthCostSpinBox = new QSpinBox();
  birthCostSpinBox->setMinimum(0);
  birthCostSpinBox->setMaximum(healthThresholdSpinBox->value());//Un animal se reproduisant ne peut pas perdre plus de santé qu'il n'en faut pour se reproduire
  birthCostSpinBox->setValue(20);
  birthCostSpinBox->setSuffix(" %");

  formLayout->addRow(tr("Nombre d'animaux : "),nbAnimSpinBox);
  formLayout->addRow(tr("Taille du monde en X :"),worldXSpinBox);
  formLayout->addRow(tr("Taille du monde en Y :"),worldYSpinBox);
  formLayout->addRow(tr("Ratio de Lions :"), lionRateSpinBox);
  formLayout->addRow(tr("Ratio de Gazelles :"), gazelleRateSpinBox);
  formLayout->addRow(tr("Energie initiale :"), lifeSpinBox);
  formLayout->addRow(tr("Seuil de bonne santé :"), healthThresholdSpinBox);
  formLayout->addRow(tr("Santé du nouveau-né :"), birthHealthSpinBox);
  formLayout->addRow(tr("Cout en santé de la reproduction :"), birthCostSpinBox);

  formLayout->addRow(startButton);

  secondLayout->addLayout(formLayout);
  secondLayout->addLayout(tickSliderLayout);
  secondLayout->addWidget(fullscreenCheckBox);
  secondLayout->addWidget(exitButton);

  mainLayout->addLayout(secondLayout, 2);

  connect(startButton, SIGNAL(clicked()), this, SLOT(slot_startButton()));
  connect(exitButton, SIGNAL(clicked()), this, SLOT(slot_exitButton()));
  connect(tickSlider, SIGNAL(valueChanged(int)),this, SLOT(slot_tickSlider(int)));
  connect(fullscreenCheckBox, SIGNAL(clicked(bool)), this, SLOT(slot_fullscreenCheckBox(bool)));
  connect(healthThresholdSpinBox, SIGNAL(valueChanged(int)), this, SLOT(slot_healthThresholdSpinBox(int)));
}

//==============================================================================
// Fonction : MainWindow::slot_startButton()
// Rôle : Fonction déclenchée par l'appui sur le bouton début, créant la scène
// Entrée : non
// Entrée/sortie : non
// Sortie : non
// Return : non
//==============================================================================

void MainWindow::slot_startButton(){
  //On remplit le tableau de paramètres pour scene
  int signedParameters[] = {nbAnimSpinBox->value(), worldXSpinBox->value(), worldYSpinBox->value(), lionRateSpinBox->value(), gazelleRateSpinBox->value(), lifeSpinBox->value(), healthThresholdSpinBox->value(), birthHealthSpinBox->value(), birthCostSpinBox->value()};
  unsigned int nbParameters = sizeof(signedParameters)/sizeof(int);
  unsigned int parameters[nbParameters];
  for (unsigned int i = 0; i < nbParameters; i++) {
    parameters[i] = static_cast<unsigned int>(signedParameters[i]); //Conversion des entiers provenant des QSpinBoxes en entiers non signés
  }
  myscene = new Scene(this, parameters);
  myview = new QGraphicsView(myscene, this);
  mainLayout->addWidget(myview);
  this->showMaximized();//Pour rendre l'affichage plus confortable, agrandissement de la fenêtre
  myscene->startup(tickSlider->value());//Démarrage de la boucle
  while (formLayout->rowCount()) {//Effacement du formulaire de paramètres pour la simulation
    formLayout->removeRow(0);//Fonction introduite dans Qt 5.8
  }
}

void MainWindow::slot_exitButton(){
  QApplication::quit();
}

void MainWindow::slot_tickSlider(int value) {
  tickSliderLabel->setText(tr("Délai entre chaque tour : ")+QString::number(tickSlider->value()));
  if (myscene) {
    myscene->setTimerInterval(value);
  }
}

void MainWindow::slot_fullscreenCheckBox(bool state) {
  if (state) {//Vrai si coché, faux sinon
    //Plein écran
    this->showFullScreen();
  }else{
    //Fenêtré
    this->showMaximized();
  }
}

void MainWindow::slot_healthThresholdSpinBox(int value) {
  birthCostSpinBox->setMaximum(value);//Un animal se reproduisant ne peut pas perdre plus de santé qu'il n'en faut pour se reproduire
}
