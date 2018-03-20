#include <string>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include "ElementBDD.hpp"
#include "GestionBDD.hpp"
using namespace std;

int main() {
  try{
    GestionBDD bdd = GestionBDD();
    // bdd.listerArticles();
    bdd.ajouterArticle("inventaire", "Pelle", "1");
    bdd.ajouterArticle("inventaire", "Pioche", "2");
    bdd.ajouterArticle("inventaire", "La tête", "3");
    bdd.listerArticles();
    // bdd.retirerArticle("inventaire", "Martal");
  }catch (sql::SQLException &e) {
    cout << "# ERR: SQLException in " << __FILE__;
    cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
    cout << "# ERR: " << e.what();
    cout << " (MySQL error code: " << e.getErrorCode();
    cout << ", SQLState: " << e.getSQLState() << " )" << endl;
  }
  return EXIT_SUCCESS;
}
