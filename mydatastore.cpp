#include <string>
#include <set>
#include <vector>
#include <iostream>
#include "mydatastore.h"

MyDataStore::~MyDataStore() {
  // delete users
  std::map<std::string, User*>::iterator it; 
  for(it = users_.begin(); it != users_.end(); ++it)
    delete (it->second); 
  
  // delete products
  std::set<Product*>::iterator it2;
  for(it2 = products_.begin(); it2 != products_.end(); ++it2)
    delete *it2; 
}

void MyDataStore::addUser(User* u) {
  if(users_.find(u->getName()) != users_.end()) return; 
  users_[u->getName()] = u; 
  carts_[u->getName()] = std::deque<Product*>(); 
}

void MyDataStore::addProduct(Product* p) {
  if(products_.find(p) != products_.end()) return; 
  products_.insert(p); 
  
  // add all keywords of product 
  // if keyword doesn't already exist, create a new pair(keyword, empty set)
  // else add product to existing keyword's set
  std::set<std::string> newProductKeywords = p->keywords(); 

  for(std::string keyword : newProductKeywords) {
    if(keywords_.find(keyword) == keywords_.end()) 
      keywords_[keyword] = std::set<Product*>(); 
    keywords_[keyword].insert(p); 
  }
}

void MyDataStore::dump(std::ostream& ofile) {
  ofile << "<products>\n"; 
  for(Product* p : products_) {
    p->dump(ofile); 
  }
  ofile << "</products>\n<users>\n"; 
  std::map<std::string, User*>::iterator it; 
  for(it = users_.begin(); it != users_.end(); ++it)
    it->second->dump(ofile);
	ofile << "</users>";
}


std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {

  // print out keywords
  /*
  std::map<std::string, std::set<Product*>>::iterator it; 
  for(it = keywords_.begin(); it != keywords_.end(); ++it) {
    std::cout << "keyword: " << it->first << std::endl;
    for(Product* p : it->second) 
      std::cout << p->getName() << " "; 
    std::cout << std::endl;
  }
  */

  if(terms.size() == 0) return std::vector<Product*>(); 

  // AND SEARCH
  if(type == 0) {
    std::set<Product*> intersection = keywords_[terms[0]]; 
    for(std::string term : terms) 
      intersection = setIntersection(intersection, keywords_[term]); 
    std::vector<Product*> ans(intersection.size()); 
    copy(intersection.begin(), intersection.end(), ans.begin());
    return ans; 
  }
  // OR SEARCH
  else {
    std::set<Product*> unionSet; 
    for(std::string term : terms) 
      unionSet = setUnion(unionSet, keywords_[term]); 
    std::vector<Product*> ans(unionSet.size()); 
    copy(unionSet.begin(), unionSet.end(), ans.begin());

    // std::cout << "in or search" << std::endl;
    // std::cout << ans.size() << std::endl;

    return ans; 
  }

}

void MyDataStore::viewCart(std::string username) {

  // checks if the username is valid
  if(users_.find(username) == users_.end()) {
    std::cout << "Invalid username" << std::endl; 
    return;
  }

  // loops through every product in the user's cart
  int prodNum = 1; 
  for(Product* p : carts_[username])
    std::cout << "Item " << prodNum++ << "\n" << p->displayString(); 

}


void MyDataStore::buyCart(std::string username) {

  // checks if the username is valid
  if(users_.find(username) == users_.end()) {
    std::cout << "Invalid username" << std::endl; 
    return;
  }

  User* user = users_[username]; 
  std::deque<Product*> cart = carts_[username]; 
  std::deque<Product*> unBoughtCart; 
  
  // loops through every product in the cart
  for(Product* p : cart) {
    // check if product is in stock and user has enough money
    if(p->getQty() && user->getBalance() >= p->getPrice()) { 
      p->subtractQty(1); 
      user->deductAmount(p->getPrice()); 
    } else 
      unBoughtCart.push_back(p); 
  }

  carts_[username] = unBoughtCart; 

}

void MyDataStore::addItemToCart(std::string username, std::vector<Product*> &hits, int hitNumber) {
  // checks if the username is valid
  if(users_.find(username) == users_.end()) {
    std::cout << "Invalid request" << std::endl; 
    return;
  } 
  if(hitNumber < 1 || hitNumber > hits.size()) {
    std::cout << "Invalid request" << std::endl; 
    return;
  }

  Product* newProduct = hits[hitNumber - 1]; 
  carts_[username].push_back(newProduct); 
}