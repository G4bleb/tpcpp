#include <iostream>
using namespace std;
class Point {
public:
  Point();
  Point(double initx, double inity);
  ~Point(){
    nbpoints--;
    cout << "destroyed" << '\n';
  }
  void afficher();
  double getx();
  double gety();
  void setx(double xset);
  void sety(double yset);
  static int nbpoints;
private:
  double x,y;
};
