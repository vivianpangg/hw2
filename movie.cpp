#include <sstream>
#include <iomanip>
#include "product.h"
#include "movie.h"
#include "util.h" 

using namespace std;

Movie::Movie(const string category, const string name, double price, int qty, string genre_, string rating_) : Product(category, name, price, qty), genre_(genre_), rating_(rating_) {}
Movie:: ~Movie(){}


string Movie::displayString() const{
  return name_ + "\n" + "Genre: " + genre_ + " Rating: " + rating_+ "\n"+
    to_string(price_)+ " "+ to_string(qty_) + " left.";
}

set<string> Movie::keywords() const{
  set<string> output1 = parseStringToWords(name_);
  set<string> output2 = parseStringToWords(genre_);

  output1.insert(output2.begin(), output2.end());

  return output1;
  
}

void Movie::dump(ostream& os) const{
  os << category_ << "\n" << name_ << "\n" << fixed << setprecision(2) << price_ << "\n" 
    << qty_ << "\n" << genre_ << "\n" << rating_ << endl;
}
  
