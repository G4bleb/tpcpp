/*

Programme produit le 10/11/17 par Gabriel LEBIS
*/
#include "Point.hpp"
using namespace std;
const int TAILLE=100;
int main(){

  // Point unPoint;
  // Point unAutrePoint(12,5);
  //
  // unPoint.afficher();
  // unAutrePoint.afficher();
  //
  // Point *unPointeurDePoint = nullptr;
  // unPointeurDePoint = new Point;
  //
  // Point *unAutrePointeurDePoint = new Point(24,10);
  //
  // unPointeurDePoint->afficher();
  // unAutrePointeurDePoint->afficher();
  //
  // delete unPointeurDePoint;
  // delete unAutrePointeurDePoint;
  cout << "------------TABLEAU_1-------------" << '\n';
  Point tab_point[TAILLE];

  // tab_point[2].setx(42);
  // tab_point[2].sety(9);
  // tab_point[2].afficher();
  for (size_t i = 0; i < TAILLE; i++) {
    tab_point[i].afficher();
  }
  cout << "------------FINTABLEAU_1-------------" << '\n';
  getchar();
  cout << "------------TABLEAU_2-------------" << '\n';
  Point *tab_point2 = nullptr;
  tab_point2 = new Point[TAILLE];
  for (size_t i = 0; i < TAILLE; i++) {
    tab_point2[i].afficher();
  }
  delete[] tab_point2;
  cout << Point::nbpoints << '\n';
  cout << "------------FINTABLEAU_2-------------" << '\n';
  getchar();
  cout << "------------TABLEAU_3-------------" << '\n';
  Point *tab_point3[TAILLE];
  for (size_t i = 0; i < TAILLE; i++) {
    tab_point3[i] = new Point;
  }
  for (size_t i = 0; i < TAILLE; i++) {
    tab_point3[i]->afficher();
  }
  for (size_t i = 0; i < TAILLE; i++) {
    delete tab_point3[i];
  }
  cout << "------------FINTABLEAU_3-------------" << '\n';
  getchar();
  cout << "------------TABLEAU_4-------------" << '\n';

  Point **tab_point4 = nullptr;
  tab_point4 = new Point*[TAILLE];
  for (size_t i = 0; i < TAILLE; i++) {
    tab_point4[i]=new Point;
  }
  for (size_t i = 0; i < TAILLE; i++) {
    tab_point4[i]->afficher();
  }
  for (size_t i = 0; i < TAILLE; i++) {
    delete tab_point4[i];
  }
  delete tab_point4;

  cout << "------------FINTABLEAU_4-------------" << '\n';
  getchar();
  // Point **tab_pt = nullptr;
  // for (auto &element:tab_pt) {
  //   element=new Point;
  //   element->afficher();
  // }
  return 0;
}
