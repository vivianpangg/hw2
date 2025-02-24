#include "book.h"
#include "util.h" 
#include "product.h"

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, std::string author_, std::string isbn_) : Product(category, name, price, qty), author_(author_), isbn_(isbn_) {} 


Book::~Book(){}

std::string Book::displayString() const {
  std::string result = name_ + "\n" + "Author: " + author_ + " ISBN:" + isbn_ + "\n" +
           std::to_string(price_) + " " + std::to_string(qty_) + " left.";
  return result;
}

std::set<std::string> Book::keywords() const {
    std::set<std::string> output1 = parseStringToWords(name_);
    std::set<std::string> output2 = parseStringToWords(author_);
  
    output1.insert(output2.begin(), output2.end());
    output1.insert(isbn_);
    
    return output1;
}

void Book::dump(std::ostream& os) const {
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << endl;

}



