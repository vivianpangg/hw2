#ifndef CLOTHING_H
#define CLOTHING_H

#include "product.h"

#include <iostream>
#include <string>
#include <set>

#include <vector>
#include <algorithm>

using namespace std;

class Clothing: public Product{

  public:
  Clothing(const string category, const string name, double price, int qty, string size_, string brand_);
  virtual ~Clothing();

  set<string> keywords() const;
  string displayString() const;
  void dump(ostream& os) const;

  protected:
    string size_;
    string brand_;
   
};

#endif