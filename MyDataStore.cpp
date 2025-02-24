#include <sstream>
#include <iomanip>
#include "MyDataStore.h"
#include "util.h"
#include "product.h"
using namespace std;

MyDataStore::~MyDataStore() { 
  for(size_t i=0; i < users_.size(); i++ ) {
    delete users_[i];
  }
  for(size_t i = 0; i<products_.size();i++ ) {
    delete products_[i];
  }
}

void MyDataStore::addToCart(User* user, Product* product) {
  map<User*, queue<Product*>>::iterator it = cart.find(user);
  if(it!=cart.end()) {
    it->second.push(product);
  }else{ 
    queue<Product*> newestCart;
    newestCart.push(product);
    cart[user] = newestCart;
  }
}

void MyDataStore::updateUserCart(User* user, queue<Product*> nCart) {
  cart[user] = nCart;
}

User* MyDataStore::getUserName(string name) {
  User* result = nullptr;
  for(size_t i= 0; i<users_.size();i++) {
    if( users_[i]->getName() == name ) {
      result = users_[i];
      break;
    }
  }
  return result;
}
void MyDataStore::addProduct(Product* p) {
  products_.push_back(p);
  set<string> keyWords = p->keywords();

  for(const string& keyWord:keyWords){
    string lowerKeyWord = convToLower(keyWord);

    keywordProductMap_[lowerKeyWord].push_back(p);

  }
}

void MyDataStore::addUser(User* u) {
  users_.push_back(u);
}

vector<Product*> MyDataStore::search(vector<string>& terms, int type) {
  vector<Product*> result;
  if(terms.empty()){
    return result;
  }

  if(type ==1){
    for(const string& term:terms){
      string lowerTerm = convToLower(term);
      if(keywordProductMap_.find(lowerTerm)!=keywordProductMap_.end()){
        vector<Product*>& products = keywordProductMap_[lowerTerm];
        result.insert(result.end(),products.begin(),products.end());
      }
    }

    }else{
      string firstTerm = convToLower(terms[0]);
      if(keywordProductMap_.find(firstTerm)!=keywordProductMap_.end()){
        result = keywordProductMap_[firstTerm];
      }else{
        return result;
      }


      for(size_t i =1;i<terms.size();i++){
        string lowerTerm = convToLower(terms[i]);
        if(keywordProductMap_.find(lowerTerm) != keywordProductMap_.end()){
          const vector<Product*>& currentProducts = keywordProductMap_[lowerTerm];

          set<Product*> set1(result.begin(), result.end());
          set<Product*> set2(currentProducts.begin(), currentProducts.end());

          set<Product*> intersectionSet = setIntersection(set1, set2);

          vector<Product*> intersectionVector(intersectionSet.begin(), intersectionSet.end());
          result = intersectionVector;
        }else{
          return vector<Product*>();
        }
      }
    }
    return result;
}
queue<Product*> MyDataStore::viewCart(User* user) {
  queue<Product*> results = cart[user];
  return results;
}

void MyDataStore::dump(ostream& os) {
  os << "<products>" << endl;
  for(size_t i = 0; i< products_.size();i++) {
    Product* product = products_[i];
    product->dump(os);
  }
  os << "</products>\n<users>" << endl;
  for(size_t i = 0; i < users_.size(); i++ ) {
    User* user = users_[i];
    user->dump(os);
  }
  os << "</users>" << endl; 
////DatabaseReadback.Book
}