#ifndef BOOK_H
#define BOOK_H

#include "product.h"

#include <iostream>
#include <string>
#include <set>

using namespace std;

class Book : public Product {
public:
  // Book();
    Book(const string category, const string name, double price, int qty, string author_, string isbn_);
    virtual ~Book();
    set<string> keywords() const;
    string displayString() const;

    void dump(ostream& os) const;
protected:
    string author_;
    string isbn_;
};

#endif