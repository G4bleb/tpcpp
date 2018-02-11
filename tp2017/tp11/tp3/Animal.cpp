#include "Animal.hpp"
using namespace std;
int Animal::nbAnimaux=0;

Animal::Animal(int initx, int inity, int initEnergie){
  x=initx;
  y=inity;
  energie=initEnergie;
  nbAnimaux++;
}

Animal::~Animal(){
  nbAnimaux--;
}

int Animal::getx() const{return x;}
int Animal::gety() const{return y;}
int Animal::getEnergie() const{return energie;}

void Animal::setx(const int xset){x=xset;}
void Animal::sety(const int yset){y=yset;}
void Animal::setEnergie(const int enerset){energie=enerset;}

void Animal::afficher(){
  cout << "Position : x = " << x << ", y = " << y << "; energie = " << energie << endl;
}

int Animal::getNbAnimaux(){
  return nbAnimaux;
}
