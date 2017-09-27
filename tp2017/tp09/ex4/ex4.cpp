/*

Programme produit le  par Gabriel LEBIS
*/
#include <iostream>
using namespace std;
namespace graph{
  struct Point{
    int x,y;
  };
  void affiche(Point a){
    cout << "x = " << a.x << " y = " << a.y << endl;
  }
  Point modif_point1(Point a){
    a.x = 1;
    a.y = 2;
    return a;
  }
std::cout << "/* message */" << '\n';
  void modif_point2(Point *a){
    a->x = 3;
    a->y = 4;
  }

  void modif_point3(Point &b){
    b.x = 5;
    b.y = 6;
  }
}
using namespace graph;
float rapport(const Point &p1){
  return static_cast<float>(p1.x)/p1.y;
}

int main(){
  Point p1 = {5,7};
  affiche(p1);
  cout << "rapport = " << rapport(p1) << endl;
  return 0;
}
