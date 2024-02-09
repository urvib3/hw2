#ifndef BOOK_H
#define BOOK_H
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include "product.h"

class Book : public Product {
    public:
      Book(const std::string category, const std::string name, double price, int qty, const std::string ISBN, const std::string author);

      std::string getAuthor() const; 
      std::string getISBN() const; 
      std::set<std::string> keywords() const;
      std::string displayString() const; 
      void dump(std::ostream& os) const;

    protected:
      std::string author_; 
      std::string ISBN_; 
};

#endif