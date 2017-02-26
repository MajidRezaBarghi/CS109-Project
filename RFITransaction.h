//
//  RFITransaction.hpp
//  RKTransaction
//
//  Created by Matthew Shehan on 2/23/17.
//  Copyright © 2017 Matthew Shehan. All rights reserved.
//

/********************************************************************
 private:

 //void removeCharsFromString(std::string &str, char* charsToRemove)
 o this functions removes particular set of characters from a string
 o the string is passed by referenced gets changed

 std::vector<std::string> split(const std::string& s, char delim);
 o returns a vector of strings split on all occurences of a char delimiter

 std::vector<std::string> parseFact(std::vector<std::string>& facts);
 o this parses facts into a usable set of strings

 std::vector<std::string> parseRule(std::vector<std::string>& rules);
 o parses rules into a usable set of strings

 std::vector<std::string> parseInference(std::vector<std::string> queries);
 o parses inferences into a useble query
 public:

 void LOAD(std::string file_name);
 o takes in a file as an argument
 o this file is open and loaded. The file is parsed and facts, rules, inferences are added to the knowledgeBase

 bool DUMP(std::string file_name);
 o takes in a filename as an argument. This dumps the entire Knowledge base
   into a usable file

 void FACT(std::string fact_string);
 o allows a user to create a FACT and add it to the knowledgeBase using proper syntax

 void RULE(std::string rule_string);
 o allows a user to create a RULE and add it to the knowledgeBase using proper syntax
 ********************************************************************/
#ifndef RFITransaction_hpp
#define RFITransaction_hpp
#include "project_include.h"
class RFITransaction{
private:
  static void removeCharsFromString(std::string &str, char* charsToRemove);
  static std::vector<std::string> split(const std::string& s, char delim);
  static std::vector<std::string> parseFact(std::vector<std::string>& facts);
  static std::vector<std::string> parseRule(std::vector<std::string>& rules);
  static std::vector<std::string> parseInference(std::vector<std::string> queries);

public:
  static void LOAD(std::string file_name);
  static void DUMP(std::string file_name);
  static void FACT(std::string fact_string);
  static void RULE(std::string rule_string);
  // INFERENCE();

};

#endif /* RFITransaction_hpp */
