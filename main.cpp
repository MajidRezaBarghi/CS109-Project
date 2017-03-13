
#include <iostream>
#include "RFITransaction.h"
#include "KRBase.h"
#include <regex>

int main(int argc, const char * argv[]) {
  RFITransaction RFI;
  try{
    RFI.LOAD("File");
    RFI.FACT("bah(a6,a6,a3)");
    RFI.DUMP("stuff.sri");
    RFI.DROP();
    RFI.LOAD("stuff.sri");
  }
  catch(const char* error){
    std::cout << error;
  }

  return 0;
}
