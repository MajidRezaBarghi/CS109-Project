#ifndef KRBASE_H
#define KRBASE_H
#include "project_include.h"
/*
This class helps to store all rule and facts that are parsed inside of
 RFITransaction. Both of these classes work in union to store and create
 new facts/rules, return query results, and manipulate information.
*/
namespace unlock{
  //this function was taken from the internet to unlock our maps
  template<typename TK, typename TV>
  std::vector<TK> extract_keys(std::map<TK, TV> const& input_map) {
    std::vector<TK> retval;
    for (auto const& element : input_map) {
      retval.push_back(element.first);
    }
    return retval;
  }
}


class KRBase
{
   private:
      std::vector<std::string> filterInference(const std::string fact_name, std::string arg1, ...);
      int TotFacts = 0;
      std::map<std::string,std::vector<std::string>> RuleBase;
      std::map<std::string,std::map<std::size_t,std::vector<std::vector<std::string>>>> FactBase;
      std::map<std::string,std::map<std::size_t,std::vector<std::vector<std::string>>>> NewRuleBase;
   public:
      KRBase();
      void addRule(std::vector<std::string>& rules);
      //void addNewRule(std::string newrule);
      void deleteAllFacts();
      void addFact(std::vector<std::string>& facts);
      bool isKeyinF(std::string key);
      bool isKeyinR(std::string key);
      int  numOfArgs(std::string key);

      void deleteAllRules();
      std::vector<std::string> getFacts();
      std::vector<std::string> queryFacts(const std::vector<std::string>& query);
      std::vector<std::vector<std::string>> queryRule(const std::string query, int args_key);
      std::vector<std::string> getRules();
      std::vector<std::string> getArgs(std::string args);
      std::vector<std::string> parseRule(std::vector<std::string> v,std::vector<std::string> args);
};

#endif
