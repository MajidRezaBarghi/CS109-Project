#ifndef KRBASE_H
#define KRBASE_H
#include "project_include.h"



class KRBase
{
   private:
      std::vector<std::string> filterInference(const std::string fact_name, std::string arg1, ...);
      int TotFacts = 0;
      std::map<std::string,std::vector<std::string>> RuleBase;
      std::map<std::string,std::map<std::size_t,std::vector<std::vector<std::string>>>> FactBase;
   public:
      KRBase();
      void addRule(std::vector<std::string>& rules);
      void deleteFact(std::vector<std::string>& facts);
      void addFact(std::vector<std::string>& facts);
      bool isKeyinF(std::string key);
      bool isKeyinR(std::string key);
      void deleteRule(std::vector<std::string>& rules);
      std::vector<std::string> queryFacts(const std::vector<std::string>& query);
      std::vector<std::string> queryRule(const std::string query);
      //std::map<std::string,std::map<std::size_t,std::vector<std::vector<std::string>>>> FactBase;
      //std::map<std::string,std::list<std::string>> NewRuleBase;
      std::map<std::string,std::map<std::size_t,std::list<std::vector<std::string>>>> NewFactBase;
};

#endif
