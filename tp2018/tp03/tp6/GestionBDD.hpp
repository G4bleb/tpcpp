using namespace std;

class GestionBDD {
private:
  sql::Connection *con;
  vector<ElementBDD> inventory;

public:
  GestionBDD(const string ip = "tcp://192.168.2.5:3306", const string login = "guest", const string password = "guest"){
    /* Create a connection */
    sql::Driver *driver;
    driver = get_driver_instance();
    con = driver->connect(ip, login, password);
  }
  ~GestionBDD(){
    delete con;
  }
  void listerArticles(){

    sql::Statement *stmt;
    sql::ResultSet *res;
    /* Connect to the MySQL test database */
    con->setSchema("inventaire");
    stmt = con->createStatement();
    res = stmt->executeQuery("SELECT * FROM articles");
    while (res->next()) {
      inventory.push_back(ElementBDD(res->getInt(3), res->getString(2)));
    }
    std::cout << "size : "+inventory.size() << '\n';
    for(unsigned int i = 0; i < inventory.size(); i++)
    {
      // cout << "\t... MySQL replies: " << endl;
      cout << inventory[i].getName() << endl;
      cout << "quantite : " << inventory[i].getQuantity() << endl;
    }
    delete res;
    delete stmt;

  }
  void ajouterArticle(const string table, const string article, const string quantity){
    // inventory.push_back(ElementBDD(stoi(quantity), article));
    sql::Statement *stmt;
    /* Connect to the MySQL test database */
    con->setSchema(table);
    stmt = con->createStatement();
    stmt->execute("INSERT INTO articles(nom, quantite) VALUES('"+article+"', '"+quantity+"')");
    delete stmt;
  }
  void retirerArticle(const string table, const string article){
    sql::Statement *stmt;
    /* Connect to the MySQL test database */
    con->setSchema(table);
    stmt = con->createStatement();
    stmt->execute("DELETE FROM articles WHERE(nom = '"+article+"')");
    delete stmt;
  }
};
