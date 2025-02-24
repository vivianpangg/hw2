#ifndef MOVIE_H
#define MOVIE_H

#include "product.h"

#include <iostream>
#include <string>
#include <set>

class Movie: public Product{
  public:

  Movie(const std::string category, std::string name, double price, int qty, std::string genre, std::string rating);
  virtual ~Movie();
  std::set<std::string> keywords() const;
  std::string displayString() const;
  void dump(std::ostream& os) const;

  protected:
    std::string genre_;
    std::string rating_;


};

#endif