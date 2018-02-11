#include <iostream>
#include <vector>
using namespace std;
class Animal {
public:
  // Animal();
  Animal(int initx = 0, int inity=0, int initEnergie=100);
  ~Animal();
  int getx() const;
  int gety() const;
  int getEnergie() const;
  void setx(const int xset);
  void sety(const int yset);
  void setEnergie(const int enerset);
  void afficher();
  static int getNbAnimaux();
private:
  static int nbAnimaux;
  int x,y, energie;
};
