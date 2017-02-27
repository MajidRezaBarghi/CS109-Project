#include "project_include.h"

class KRBase {
   private:
      void addFact(std::vector<std::string>& facts);
      void addRule(std::vector<std::string>& rules);
      std::vector<std::string> filterInference(const std::string fact_name, std::string arg1, ...);
      std::vector<std::string> queryFacts(const std::vector<std::string>& query);

   public:   
      std::map<std::string,std::map<std::size_t,std::vector<std::vector<std::string>>>> FactBase;
      std::map<std::string,std::vector<std::string>> RuleBase;
}
