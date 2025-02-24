#include <sstream>
#include <iomanip>
#include "book.h"
#include "util.h"
#include "product.h"

using namespace std;

// Book::Book();

Book::Book(const string category, const string name, double price, int qty, string author_, string isbn_) : Product(category, name, price, qty), author_(author_), isbn_(isbn_) {} 

Book::~Book(){}

string Book::displayString() const {
  string result = name_ + "\n" + "Author: " + author_ + " ISBN: " + isbn_ + "\n" +
    to_string(price_) + " " + to_string(qty_) + " left.";
  return result;
}

set<string> Book::keywords() const {
    set<string> output1 = parseStringToWords(name_);
    set<string> output2 = parseStringToWords(author_);
  
    output1.insert(output2.begin(), output2.end());
    output1.insert(isbn_);
    
    return output1;
}

void Book::dump(ostream& os) const {
  // os<<"book"<<endl;
  // os<<getName()<<endl;
  // os<<fixed << setprecision(2)<<getPrice()<<endl;
  // os<<getQty()<<endl;
  // os<<getISBN()<<endl;
  // os<<getAuthor()<<endl;
  
  os << category_ << "\n" << name_ << "\n" << fixed<<setprecision(2)<<
    price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << endl;

}



