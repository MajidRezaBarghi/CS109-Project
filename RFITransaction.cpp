//
//  RFITransaction.cpp
//  RKTransaction
//
//  Created by Matthew Shehan on 2/23/17.
//  Copyright © 2017 Matthew Shehan. All rights reserved.
//


#include "RFITransaction.h"
void RFITransaction:: removeCharsFromString( std::string &str, char* charsToRemove ) {
  for ( unsigned int i = 0; i < strlen(charsToRemove); ++i ) {
    str.erase( remove(str.begin(), str.end(), charsToRemove[i]), str.end() );
  }
}
std::vector<std::string> RFITransaction:: split(const std::string &s, char delim) {
  std::stringstream ss(s);
  std::string item;
  std::vector<std::string> tokens;
  while (getline(ss, item, delim)) {
    tokens.push_back(item);
  }
  return tokens;
}

std::vector<std::string> RFITransaction::parseFact(std::vector<std::string>& facts){
  std::string concat_string = "";
  std::vector<std::string> tokens = facts;
  for (std::vector<std::string>::iterator it = tokens.begin();
    it!= tokens.end(); it++){
    concat_string += *it;
  }
  tokens = split(concat_string, '(');
  tokens = split(tokens[1],')');
  tokens = split(tokens[0],',');
  return tokens;
}

std::vector<std::string> RFITransaction::parseRule(std::vector<std::string> &rules){

  std::vector<std::string> tokens = rules;

  char lose[] = ":-";
  removeCharsFromString(tokens[0],lose);
  std::cout << "RULES: ";
  for(int i = 0; i < tokens.size(); i++)std::cout << tokens[i] << "\n";
  return tokens;
}
void RFITransaction::FACT(std::string fact_string){
  std::vector<std::string> facts;
  facts.push_back(fact_string);
  facts = parseFact(facts);

  // add parsed fact to KB
}
void RFITransaction::LOAD(std::string file_name){
  std::ifstream in_file;
  in_file.open(file_name, std::ios_base::in);

  if(in_file.is_open()){
    std::string line;
    std::map<std::string,int> parser_map;
    parser_map["FACT"] = 1;
    parser_map["RULE"] = 2;
    parser_map["INFERENCE"] = 3;

    while(std::getline(in_file,line)){
      // flag tells us if rule,inference,fact
      std::string flag;

      std::vector<std::string> items;
      std::string next;
      // string to input stream
      std::istringstream iss(line);

      // tokenize the string and parse
      iss >> flag;
      while(iss >> next){
        items.push_back(next);
      }
      switch(parser_map[flag]){
        case 1:
          parseFact(items);
          // add parsedFact to KB
          break;
        case 2:
          parseRule(items);
          // add parsedRule to KB
          break;
        /*case 3:
          parseInference(the_rest);
          break;*/
        default:
          throw "error, that command was not found";
          break;
      }

    }

  }else{
    throw "Error could not open file";
  }

}
