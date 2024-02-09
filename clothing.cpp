#include <sstream>
#include <iomanip>
#include "clothing.h"
#include "util.h"

using namespace std;


Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand) :
    Product(category, name, price, qty), 
    size_(size), 
    brand_(brand)
{

}

std::string Clothing::getSize() const {
  return size_;
}
      
std::string Clothing::getBrand() const {
  return brand_; 
}

std::set<std::string> Clothing::keywords() const  {

  std::set<std::string> keyWords = parseStringToWords(this->getName() + " " + this->getBrand()); 
  return keyWords; 

}

std::string Clothing::displayString() const {
  return getName() + "\nSize: " + getSize() + " Brand: " + getBrand() + "\n" + to_string(getPrice()) + " " + to_string(getQty()) + " left.\n";
}

void Clothing::dump(std::ostream& os) const {
  Product::dump(os); 
  os << size_ << "\n" << brand_ << "\n"; 
}