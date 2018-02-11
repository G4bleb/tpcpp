#include "Monde.hpp"
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <string>
Monde::Monde(int nbAnim){
  nbAnimaux=nbAnim;
  for (size_t j = 0; j < MAX_Y; j++) {
    for (size_t i = 0; i < MAX_X; i++) {
      tabMonde[i][j] = ' ';
    }
  }
}

int Monde::getMAX_X()const{
  return MAX_X;
}

int Monde::getMAX_Y()const{
  return MAX_Y;
}

void Monde::peuplement(){
  vecteurAnimaux.resize(nbAnimaux);
  for (int i = 0; i < nbAnimaux; i++) {
    vecteurAnimaux[i].setX(rand()%MAX_X);
    vecteurAnimaux[i].setY(rand()%MAX_Y);
    vecteurAnimaux[i].setEnergie(rand()%100);
    tabMonde[vecteurAnimaux[i].getX()][vecteurAnimaux[i].getY()] = 'A';
  }
}

void Monde::afficher(){
  system("clear");
  system("clear");
  char color[8];
  std::string red("\033[1;31m");
  std::string yellow ("\033[1;33m");

  for (size_t j = 0; j < MAX_Y; j++) {
    for (size_t i = 0; i < MAX_X; i++){

      if (tabMonde[i][j] == 'A') {
        red.copy(color, 8);
      }
      if (tabMonde[i][j] == 'X') {
        yellow.copy(color, 8);
      }

      std::cout << color << tabMonde[i][j];
    }
    std::cout << '\n';
  }
  usleep(100000);
}

void Monde::bouge(int i){
  vecteurAnimaux[i].setEnergie(vecteurAnimaux[i].getEnergie()-1);
  switch (rand()%4) {
    case 0: //Z
    if (vecteurAnimaux[i].getY()!=0) {
      tabMonde[vecteurAnimaux[i].getX()][vecteurAnimaux[i].getY()] = ' ';
      vecteurAnimaux[i].setY(vecteurAnimaux[i].getY()-1);
      tabMonde[vecteurAnimaux[i].getX()][vecteurAnimaux[i].getY()] = 'A';
    }
    break;
    case 1: //Q
    if (vecteurAnimaux[i].getX()!=0) {
      tabMonde[vecteurAnimaux[i].getX()][vecteurAnimaux[i].getY()] = ' ';
      vecteurAnimaux[i].setX(vecteurAnimaux[i].getX()-1);
      tabMonde[vecteurAnimaux[i].getX()][vecteurAnimaux[i].getY()] = 'A';
    }
    break;
    case 2: //S
    if (vecteurAnimaux[i].getY()!=MAX_Y-1) {
      tabMonde[vecteurAnimaux[i].getX()][vecteurAnimaux[i].getY()] = ' ';
      vecteurAnimaux[i].setY(vecteurAnimaux[i].getY()+1);
      tabMonde[vecteurAnimaux[i].getX()][vecteurAnimaux[i].getY()] = 'A';
    }
    break;
    case 3: //D
    if (vecteurAnimaux[i].getX()!=MAX_X-1) {
      tabMonde[vecteurAnimaux[i].getX()][vecteurAnimaux[i].getY()] = ' ';
      vecteurAnimaux[i].setX(vecteurAnimaux[i].getX()+1);
      tabMonde[vecteurAnimaux[i].getX()][vecteurAnimaux[i].getY()] = 'A';
    }
    break;
  }
}

int Monde::passeuntour(){
  for (int i = 0; i < nbAnimaux; i++) {
    bouge(i);
    if (vecteurAnimaux[i].getEnergie()<=0) {
      mort(i);
      i--;
    }
  }

  if (!nbAnimaux) {
    return 0;
  }
  return 1;
}

void Monde::mort(int i){
  tabMonde[vecteurAnimaux[i].getX()][vecteurAnimaux[i].getY()] = 'X';
  vecteurAnimaux.erase(vecteurAnimaux.begin()+i);
  nbAnimaux = static_cast<int>(vecteurAnimaux.size());
}
