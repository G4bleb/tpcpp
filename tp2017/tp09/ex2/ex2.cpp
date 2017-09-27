/*

Programme produit le  par Gabriel LEBIS
*/
#include <iostream>
using namespace std;

struct Point{
  int x,y;
};

void affiche(Point a){
  cout << "x:" << a.x << "y" << a.y;
}

Point modif_point1(Point a){
  a.x = 1;
  a.y = 2;
  return a;
}

void modif_point2(Point *a){
  a->x = 3;
  a->y = 4;
}

void modif_point3(Point &b){
  b.x = 5;
  b.y = 6;
}

int main(){
  return 0;
}
