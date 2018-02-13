/*

Programme produit le  par Gabriel LEBIS
*/
#include "Monde.hpp"

int main(){
  srand(static_cast<unsigned int>(time(NULL)));
  Monde leMonde(100);
  leMonde.peuplement();

  for (; true;) {
    leMonde.afficher();
    if(!leMonde.passeuntour()){
      // leMonde.afficher();
      return 0;
    }
  }
  // Lion un_lion;
  // Gazelle une_gazelle;
  // un_lion.afficher();
  // une_gazelle.afficher();
  return 0;
}
