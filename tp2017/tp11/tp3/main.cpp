/*

Programme produit le  par Gabriel LEBIS
*/
#include "Animal.h"
using namespace std;

int main(){
  static Animal animal1;
  Animal *animal2 = new Animal;

  animal1.setx(2);
  animal1.sety(4);
  animal1.setEnergie(35);
  animal1.afficher();

  animal2->setx(5);
  animal2->sety(9);
  animal2->setEnergie(15);
  animal2->afficher();

  vector<Animal> farm;
  farm.push_back(animal1); //Copie, puis destruction de la copie
  farm.push_back(*animal2); //Copie, puis destruction de la copie
  farm.push_back(Animal());

  farm[0].afficher();
  farm[2].afficher();
  // farm.pop_back();
  // farm.pop_back();
  // farm.pop_back();

  // farm.erase(farm.begin());

  // for(auto anim:farm){
  //   anim.afficher();
  // }
  cout << animal1.getNbAnimaux() << '\n';
  return 0;
}
