#include <sstream>
#include <iomanip>
#include "movie.h"
#include "util.h"

using namespace std;


Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating) :
    Product(category, name, price, qty), 
    genre_(genre), 
    rating_(rating)
{

}

std::string Movie::getGenre() const {
  return genre_;
}
      
std::string Movie::getRating() const {
  return rating_; 
}

std::set<std::string> Movie::keywords() const  {

  std::set<std::string> keyWords = parseStringToWords(this->getName() + " " + this->getGenre()); 
  return keyWords; 

}

std::string Movie::displayString() const {
  return getName() + "\nGenre: " + getGenre() + " Rating: " + getRating() + "\n" + to_string(getPrice()) + " " + to_string(getQty()) + " left.\n"; 
}

void Movie::dump(std::ostream& os) const {
  Product::dump(os); 
  os << genre_ << "\n" << rating_ << "\n"; 
}