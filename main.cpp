//
//  main.cpp
//  RKTransaction
//
//  Created by Matthew Shehan on 2/23/17.
//  Copyright © 2017 Matthew Shehan. All rights reserved.
//

#include <iostream>
#include "RFITransaction.h"
#include "KRBase.h"

int main(int argc, const char * argv[]) {

  try{
    RFITransaction::LOAD("File");
  }
  catch(const char* error){
    std::cout << error;
  }
  KRBase test;
  std::vector<std::string> v;
    std::vector<std::string> v1;
      std::vector<std::string> v2;
  v.push_back("Fact(a5,a2,a4)");
  v1.push_back("Fact(a5,a3,a6)");
  v2.push_back("Fact(a5,a7,a8)");
  test.addFact(v);
  test.addFact(v1);
  test.addFact(v2);
  test.queryFacts(v);
  return 0;
}
