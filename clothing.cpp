#include <sstream>
#include <iomanip>
#include "product.h"
#include "clothing.h"
#include "util.h"

using namespace std;

Clothing::Clothing(const string category, const string name, double price, int qty, string size_, string brand_) : Product(category, name, price, qty), size_(size_), brand_(brand_) {}

Clothing::~Clothing(){}


string Clothing::displayString() const{
  return name_ + "\n" + "Size: " + size_ + " Brand: " + brand_+ "\n"+
    to_string(price_)+ " "+ to_string(qty_) + " left.";
}

set<string> Clothing::keywords() const{
  set<string> output1 = parseStringToWords(name_);
  set<string> output2 = parseStringToWords(size_);
  set<string> output3 = parseStringToWords(brand_);
  
  output1.insert(output2.begin(), output2.end());
  output1.insert(output3.begin(), output3.end());
  
  // output1.insert(isbn_); for book

  return output1;
}

void Clothing::dump(ostream& os) const{
  os << category_ << "\n" << name_ << "\n" << fixed<<setprecision(2)<<price_ << "\n" 
    << qty_ << "\n" << size_ << "\n" << brand_ << endl;

  
}