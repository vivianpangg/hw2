#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "product.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "MyDataStore.h"

using namespace std;
struct ProdNameSorter {
    bool operator()(Product* p1, Product* p2) {
        return (p1->getName() < p2->getName());
    }
};
void displayProducts(vector<Product*>& hits);

int main(int argc, char* argv[])
{
    if(argc < 2) {
        cerr << "Please specify a database file" << endl;
        return 1;
    }

    /****************
     * Declare your derived DataStore object here replacing
     *  DataStore type to your derived type
     ****************/
    MyDataStore ds;



    // Instantiate the individual section and product parsers we want
    ProductSectionParser* productSectionParser = new ProductSectionParser;
    productSectionParser->addProductParser(new ProductBookParser);
    productSectionParser->addProductParser(new ProductClothingParser);
    productSectionParser->addProductParser(new ProductMovieParser);
    UserSectionParser* userSectionParser = new UserSectionParser;

    // Instantiate the parser
    DBParser parser;
    parser.addSectionParser("products", productSectionParser);
    parser.addSectionParser("users", userSectionParser);

    // Now parse the database to populate the DataStore
    if( parser.parse(argv[1], ds) ) {
        cerr << "Error parsing!" << endl;
        return 1;
    }

    cout << "=====================================" << endl;
    cout << "Menu: " << endl;
    cout << "  AND term term ...                  " << endl;
    cout << "  OR term term ...                   " << endl;
    cout << "  ADD username search_hit_number     " << endl;
    cout << "  VIEWCART username                  " << endl;
    cout << "  BUYCART username                   " << endl;
    cout << "  QUIT new_db_filename               " << endl;
    cout << "====================================" << endl;

    vector<Product*> hits;

    bool done = false;
    while(!done) {
        cout << "\nEnter command: " << endl;
        string line;
        getline(cin,line);
        stringstream ss(line);
        string cmd;
        if((ss >> cmd)) {
            if( cmd == "AND") {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 0);
                displayProducts(hits);
            }
            else if ( cmd == "OR" ) {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 1);
                displayProducts(hits);
            }
            else if ( cmd == "QUIT") {
                string filename;
                if(ss >> filename) {
                    ofstream ofile(filename.c_str());
                    ds.dump(ofile);
                    ofile.close();
                }
                done = true;
            }else if(cmd == "ADD"){
              // string username;
              // vector<string> usernames;
              // username = convToLower(username);
              // while(ss>>username){
              //   usernames.push_back(username);
              // }

              // if(usernames.size()!=2){
              //   cout<<"invalid"<<endl;

              // }else{
              //   if(stoi(usernames[1]) >static_cast<int>(hits.size())){
              //     cout<<"invalid"<<endl;
              //   }else if(ds.getUserName(usernames[0]) == nullptr){
              //     cout<<"invalid"<<endl;
              //   }else{
              //     ds.addToCart(ds.getUserName(usernames[0]), hits[stoi(usernames[1])-1]);
              //   }
              // }
              string username;
              int hitIndex;
              if(!(ss>>username>>hitIndex)){
                cout<<"Invalid request"<<endl;
                continue;
              }
              User* user = ds.getUserName(username);
              if(user == nullptr ||hitIndex>static_cast<int>(hits.size())|| hitIndex<1){
                cout<<"Invalid request";
                
              }else{
                ds.addToCart(user, hits[hitIndex-1]);
              }

            }else if(cmd =="VIEWCART"){
              // string username;
              // vector<string> usernames;
              // username = convToLower(username);
              // while(ss>>username){
              //   usernames.push_back(username);
              // }

              // if(ds.getUserName(usernames[0]) ==nullptr){
              //   cout<<"Invalid"<<endl;

              // }else{
              //   User* currentUser = ds.getUserName(usernames[0]);

              //   queue<Product*> result1 = ds.viewCart(currentUser);

              //   vector<Product*> result2 = ds.viewCart(currentUser);


              //   while(!(result1.empty())){
              //     result2.push_back(result1.front());
              //     result1.pop();

              //   }

              //   int counter=1;
              //   for(vector<Product*>::iterator iter=result2.begin(); iter!=result2.end();iter++){
              //     cout<<"Item: "<<setw(2)<<counter<<endl;
              //     cout<<(*iter)->displayString()<<endl;
              //     cout<<endl;
              //     counter++;

              //   }

              // }

              string username;
              if(!(ss>>username)){
                cout<<"Invali username"<<endl;
                continue;
              }

              User* user = ds.getUserName(username);
              if(user==nullptr){
                cout<<"Invalid username"<<endl;
              }
                int counter = 1;
                queue<Product*> cartQueue = ds.viewCart(user);
                while(!(cartQueue.empty())){
                    Product* product = cartQueue.front();
                    cartQueue.pop();
                    cout<<"Item: " <<setw(3)<<counter<<endl;
                    cout<<product->displayString()<<endl;
                    cout<<endl;
                    counter++;
                }

            }else if(cmd =="BUYCART"){
              string username;
              if(!(ss>>username)){
                cout<<"Invalid Username"<<endl;
                continue;
              }

              User* user = ds.getUserName(username);
              if(user==nullptr){
                cout<<"Invalid Username"<<endl;
              }else{
                queue<Product*>userCart = ds.viewCart(user);
                queue<Product*> restOfCart;
                while(!userCart.empty()){
                  Product* product = userCart.front();
                  userCart.pop();
                  
                  if(product->getQty() > 0 && user->getBalance()>= product->getPrice()){
                    product->subtractQty(1);
                    user->deductAmount(product->getPrice());
                    
                    }else{
                      restOfCart.push(product);
                    }
                }
                ds.updateUserCart(user,restOfCart);
              }
              

            }
                // string element;
                // vector<string> listOfElements;

                // while(ss>>element){
                //   listOfElements.push_back(element);

                // // }
                // // if(!(ss>>username)){
                // //     cout<<"Invalid username"<<endl;
                // //     continue;
                // // }
                // // User* user = ds.getUser(username);
                // // if(user ==nullptr){
                // //     cout<<"Invalid username"<<endl;
                // //     continue;
                // // }

                // if(ds.getUser(listOfElements[0]) ==nullptr || listOfElements.size()!=1){
                //   cout<<"Invalid"<<endl;
                // }else{
                //   std::queue<Product*> userCart = ds.viewCart(user);
                //   std::queue<Product*> restOfCart;

                //   while(!userCart.empty()){
                //     Product* product = userCart.front();
                //     userCart.pop();

                //   if(product->getQty()&& user->getBalance() >= product->getPrice() ){
                //       product->subtractQty(1);
                //       user->deductAmount(product->getPrice());

                //   }else{
                //       restOfCart.push(product);
                //   }

                //   }

                // }

                
                // ds.updateUserCart(user, restOfCart);
                // cout<<"Purchase Done"<<endl;



            }
	    /* Add support for other commands here */




            else {
                cout << "Unknown command" << endl;
            }
        }

    return 0;
}

void displayProducts(vector<Product*>& hits)
{
    int resultNo = 1;
    if (hits.begin() == hits.end()) {
    	cout << "No results found!" << endl;
    	return;
    }
    std::sort(hits.begin(), hits.end(), ProdNameSorter());
    for(vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it) {
        cout << "Hit " << setw(3) << resultNo << endl;
        cout << (*it)->displayString() << endl;
        cout << endl;
        resultNo++;
    }
}
