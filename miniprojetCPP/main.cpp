/*

Programme produit le  par Gabriel LEBIS
*/
#include "World.hpp"
#include "mainWindow.hpp"
#include "Scene.hpp"
#include <QApplication>
int main(int argc, char *argv[]) {
  srand(static_cast<unsigned int>(time(NULL)));
  QApplication app(argc, argv);
  MainWindow window;
  window.adjustSize();
	window.move(QApplication::desktop()->screen()->rect().center() - window.rect().center());
  window.show();

  return app.exec();

  // for (;;) {
  //   leMonde.display();
  //   if (!leMonde.passeuntour()) {
  //     leMonde.display();
  //     std::cout << "Victimes : "<< leMonde.getVictims() << std::endl;
  //     return 0;
  //   }
  // }
}
