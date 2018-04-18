/*

Programme démarré le 03/4/2018 par Gabriel LEBIS
*/

#include "fenetrePrincipale.hpp"
#include "MyScene.hpp"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  FenetrePrincipale window;
  window.adjustSize();
	window.move(QApplication::desktop()->screen()->rect().center() - window.rect().center());
  window.show();
  return app.exec();
}
