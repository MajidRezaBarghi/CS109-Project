//
//  main.cpp
//  RKTransaction
//
//  Created by Matthew Shehan on 2/23/17.
//  Copyright © 2017 Matthew Shehan. All rights reserved.
//

#include <iostream>
#include "RFITransaction.h"

int main(int argc, const char * argv[]) {

  try{
    RFITransaction::LOAD("File");
  }

  catch(const char* error){
    std::cout << error;
  }
  return 0;
}
