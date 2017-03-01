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
    std::vector<std::string> v;
    std::istringstream iss("Parent($X,$Y):- OR Mother($X,$Y) Father($X,$Y)");
    std::string next;
    while(iss >> next){
      v.push_back(next);
      std::cout << v.size() << '\n';
    }
    //v = RFI.parseRule(v);
    //RFI.RULE(RFI.parseRule(v));
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

KRBase test;
std::vector<std::string> ruleTest = {"Parent($X, $Y)", "OR", "Father($X, $Y) Mother($X, $Y)"};
std::vector<std::string> ruleTest2 = {"Grandmother($X, $Y)", "AND", "Mother($X, $Z) Mother($Z, $Y)"};
std::vector<std::string> ruleTest3 = {"GrandFather($X, $Y)", "AND", "Father($X, $Z) Parent($Z, $Y)"};
std::vector<std::string> ruleTest4 = {"Grandmother($X, $Y)", "AND", "Mother($X, $Z) Father($Z, $Y)"};

test.addRule(ruleTest);
test.addRule(ruleTest2);
test.addRule(ruleTest3);
test.addRule(ruleTest4);

test.deleteAllRules();

  return 0;
}
