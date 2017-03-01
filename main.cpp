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
  RFITransaction RFI;
  try{
    RFI.LOAD("File");
    RFI.FACT("bah(a6,$a6,$a3)");
  }
  catch(const char* error){
    std::cout << error;
  }
  // std::vector<std::string> v;
  // std::vector<std::string> v1;
  // std::vector<std::string> v2;
  // v.push_back("Fact(a5,a2,a4)");
  // std::vector<std::string> v3;
  // v3.push_back("Fact($a5,$a2,$a4)");
  // v1.push_back("Fact(a56,jfkdla;fkdla,a6)");
  // v2.push_back("Fact(a5,a7,a8)");
  // v = RFITransaction::parseFact(v);
  // v1 = RFITransaction::parseFact(v1);
  // v2 = RFITransaction::parseFact(v2);
  // test.addFact(v);
  // test.addFact(v1);
  // test.addFact(v2);
  // test.queryFacts(RFITransaction::parseFact(v3));

  // test.deleteFact(v);
  return 0;
}
