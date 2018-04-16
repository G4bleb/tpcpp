/*

Programme démarré le 03/4/2018 par Gabriel LEBIS
*/

#include "mainwindow.hpp"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  MainWindow window;
  window.show();
  return app.exec();
}
