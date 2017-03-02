//
//  RFITransaction.cpp
//  RKTransaction
//
//  Created by Matthew Shehan on 2/23/17.
//  Copyright © 2017 Matthew Shehan. All rights reserved.
//


#include "RFITransaction.h"

RFITransaction::RFITransaction(){

}
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
  std::string fact_name;
  std::vector<std::string> tokens = facts;
  for (std::vector<std::string>::iterator it = tokens.begin();it!= tokens.end(); it++){
    concat_string += *it;
  }
  tokens = split(concat_string, '(');
  fact_name = tokens[0];
  tokens = split(tokens[1],')');
  tokens = split(tokens[0],',');
  tokens.push_back(fact_name);
  // for(int i=0; i < tokens.size(); i++)std::cout<<"tokens[" << i << "]" << tokens[i] << " ";
  // // debugger
  // std::cout << "\n";
  return tokens;
}

std::vector<std::string> RFITransaction::parseRule(std::vector<std::string> &rules){

  std::vector<std::string> tokens = rules;

  char lose[] = ":-";
  removeCharsFromString(tokens[0],lose);
  auto temp = tokens[0];
  std::vector<std::string>::iterator it = tokens.begin();
  tokens.erase(it);
  tokens.push_back(temp);
  return tokens;
}
std::vector<std::string> RFITransaction::parseInference(std::vector<std::string> queries){
  std::vector<std::string> tokens = parseFact(queries);
  return tokens;
}

void RFITransaction::FACT(std::string fact_string){
  std::vector<std::string> facts;
  facts.push_back(fact_string);
  std::vector<std::string>tokens = parseFact(facts);
  krbase.addFact(tokens);
}

void RFITransaction::RULE(std::string rule_string) {
  std::vector<std::string> rules;
  rule_string.erase(0,5); // erases 'RULE'
  rules.push_back(rule_string);
  std::vector<std::string>tokens = parseRule(rules);
  std::vector<std::string> temp_vect = split(tokens[0],' ');
  std::string temp = tokens[1];
  tokens = temp_vect;
  tokens.push_back(temp);
  for(int i = 0; i < tokens.size(); i++){
    //std::cout << tokens[i] << "\n";
  }
  krbase.addRule(tokens);
}

std::vector<std::string> RFITransaction::INFERENCE(std::vector<std::string> &set_facts){
  std::vector<std::string> v;
  if(krbase.isKeyinR(set_facts[0])){
  v = krbase.queryRule(set_facts);
  std::map<std::string,int> rule_map;
  rule_map["OR"]= 1;
  switch(rule_map[v[0]]) {
    case 1:
      for(int i = 1; i < v.size(); i++) {
        std::vector<std::string> temp;
        temp.push_back(v[i]);
        INFERENCE(temp);
      }
    };
  }
  v = parseFact(set_facts);
  if(krbase.isKeyinF(v.back())){
    krbase.queryFacts(v);
  }
  return v;
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
        //std::cout << items.size() << '\n';
      }

      switch(parser_map[flag]){
        case 1:
          items = parseFact(items);
          krbase.addFact(items);
          break;
        case 2:
          items = parseRule(items);
          krbase.addRule(items);
          break;

        case 3:
          //items = parseInference(items);
          //items = krbase.queryFacts(items);
          INFERENCE(items);
          // add parsedRule to KB
          break;

        default:
          throw "error, that command was not found";
          break;
      }

    }

  }else{
    throw "Error could not open file";
  }

}
void RFITransaction::DROP(){
  krbase.deleteAllFacts();
  krbase.deleteAllRules();
}

void RFITransaction::DUMP(std::string file_name) {
  std::ofstream dump_file;
  std::vector<std::string> rules;
  rules = krbase.getRules();
  dump_file.open("output.sri");
  for(int i = 0; i < rules.size(); i++) {
    dump_file << rules[i] << std::endl;
  }
  dump_file.close();
}
