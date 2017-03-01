#ifndef KRBASE_H
#define KRBASE_H
#include "RFITransaction.h"
#include "project_include.h"



class KRBase: public RFITransaction
{
   private:
      void addRule(std::vector<std::string>& rules);
      std::vector<std::string> filterInference(const std::string fact_name, std::string arg1, ...);
      int TotFacts = 0;
      std::map<std::string,std::map<std::size_t,std::vector<std::vector<std::string>>>> FactBase;
   public:
      void deleteFact(std::vector<std::string>& v);
      void addFact(std::vector<std::string>& facts);
      std::vector<std::string> queryFacts(const std::vector<std::string>& query);
      //std::map<std::string,std::map<std::size_t,std::vector<std::vector<std::string>>>> FactBase;
      std::map<std::string,std::vector<std::string>> RuleBase;
      //std::map<std::string,std::list<std::string>> NewRuleBase;
      std::map<std::string,std::map<std::size_t,std::list<std::vector<std::string>>>> NewFactBase;
};

#endif
