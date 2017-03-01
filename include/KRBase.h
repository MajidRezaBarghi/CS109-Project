#ifndef KRBASE_H
#define KRBASE_H
#include "project_include.h"

namespace unlock{
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
   public:
      KRBase();
      void addRule(std::vector<std::string>& rules);
      void deleteAllFacts();
      void addFact(std::vector<std::string>& facts);
      bool isKeyinF(std::string key);
      bool isKeyinR(std::string key);

      void deleteAllRules();
      std::vector<std::string> getFacts();
      std::vector<std::string> queryFacts(const std::vector<std::string>& query);
      std::vector<std::string> queryRule(const std::vector<std::string>& query);
      std::vector<std::string> getRules();
};

#endif
