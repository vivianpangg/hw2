#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include "datastore.h"
#include "product.h"
#include "user.h"
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <string>

using namespace std;

class MyDataStore: public DataStore{
  public:
    virtual ~MyDataStore();

  // addProduct
  // addUser
  // search
  // dump


  /**
     * Adds a product to the data store
     */
    void addProduct(Product* p);

    /**
     * Adds a user to the data store
     */
    void addUser(User* u);

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    vector<Product*> search(vector<string>& terms, int type);

    /**
     * Reproduce the database file from the current Products and User values
     */
    void dump(ostream& ofile);

    User* getUserName(string name);
    void addToCart(User* user, Product* product);
    queue<Product*> viewCart(User* user);
    void updateUserCart(User* user, queue<Product*> nCart);

  private:
    vector<Product*> products_;
    vector<User*> users_;
    map<string, vector<Product*>> keywordProductMap_;
    map<User*, queue<Product*>> cart;

};



#endif