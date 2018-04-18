/*

Programme produit le  par Gabriel LEBIS
*/
#include "Monde.hpp"

int main() {
  srand(static_cast<unsigned int>(time(NULL)));
  Monde leMonde(100);
  leMonde.peuplement();

  for (;;) {
    leMonde.afficher();
    if (!leMonde.passeuntour()) {
      leMonde.afficher();
      std::cout << "Victimes : "<< leMonde.getVictimes() << std::endl;
      return 0;
    }
  }
  return 0;
}
