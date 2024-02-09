#include <sstream>
#include <iomanip>
#include "book.h"
#include "util.h"

using namespace std;


Book::Book(const std::string category, const std::string name, double price, int qty, const std::string ISBN, const std::string author) :
    Product(category, name, price, qty),  
    ISBN_(ISBN), 
    author_(author)
{

}

std::string Book::getAuthor() const {
  return author_;
}
      
std::string Book::getISBN() const {
  return ISBN_; 
}

std::set<std::string> Book::keywords() const  {

  std::set<std::string> keyWords = parseStringToWords(this->getName() + " " + this->getAuthor()); 
  keyWords.insert(this->getISBN()); 
  return keyWords; 

}



std::string Book::displayString() const {
  return getName() + "\nAuthor: " + getAuthor() + " ISBN: " + getISBN() + "\n" + to_string(getPrice()) + " " + to_string(getQty()) + " left.\n"; 
}

void Book::dump(std::ostream& os) const {
  Product::dump(os); 
  os << ISBN_ << "\n" << author_ << "\n"; 
}