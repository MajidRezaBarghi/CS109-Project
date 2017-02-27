//
//  KRBase.hpp
//  RKTransaction
//
//  Created by Matthew Shehan on 2/26/17.
//  Copyright © 2017 Matthew Shehan. All rights reserved.
//

#ifndef KRBase_hpp
#define KRBase_hpp

#include "project_include.h"
class KRBase{
public:
  
  void addFact(std::vector<std::string>& facts);
  void addRule(std::vector<std::string>& rules);
  std::vector<std::string> filterInference(const std::string fact_name, std::string arg1, ...);
  std::vector<std::string> queryFacts(const std::vector<std::string>& query);
  

private:
  
  std::map<std::string,std::map<std::size_t,std::vector<std::vector<std::string>>>> FactBase;
  std::map<std::string,std::vector<std::string>> RuleBase;
  
};
#endif /* KRBase_hpp */
