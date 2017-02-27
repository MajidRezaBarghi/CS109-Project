#include "project_include.h"

class KRBase {
   private:
      void KRBase::addFact(std::vector<std::string> &facts){
         std::string fact_key = facts.back();
         std::size_t args_key = facts.size();
  
         FactBase[fact_key][args_key].push_back(facts);
         return;
      } 


      void KRBase::addRule(std::vector<std::string>& rules){
         std::string rule_key = rules.back();
         rules.pop_back();
         RuleBase[rule_key] = rules; 
      }

   public:   

}
