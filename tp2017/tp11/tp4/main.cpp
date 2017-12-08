/*

Programme produit le  par Gabriel LEBIS
*/
#include "Monde.h"

int main(){
  srand(static_cast<unsigned int>(time(NULL)));
  Monde leMonde(10);
  leMonde.peuplement();

  for (size_t i = 1; i > 0; i++) {
    if(!leMonde.passeuntour()){
      leMonde.afficher();
      return 0;
    }
    leMonde.afficher();
  }
  return 0;
}
