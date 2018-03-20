using namespace std;

class ElementBDD {

private:
  int quantity;
  string name;

public:
  ElementBDD(const int _quantity, const string _name){
    quantity = _quantity;
    name = _name;
  }
  ~ElementBDD(){}
  int getQuantity(){
    return quantity;
  }
  string getName(){
    return name;
  }
};
