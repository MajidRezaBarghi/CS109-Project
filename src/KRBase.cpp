#include "KRBase.h"


KRBase::KRBase(){

}

bool KRBase::isKeyinF(std::string key){
  return FactBase.count(key)>.0;
}

bool KRBase::isKeyinR(std::string key){
  return RuleBase.count(key)>0;
}

void KRBase::addFact(std::vector<std::string> &facts){
         std::string fact_key = facts.back();
         std::size_t args_key = facts.size() -1 ;
         FactBase[fact_key][args_key].push_back(facts);
         TotFacts++;
}

void KRBase::deleteFact(std::vector<std::string> &facts) {
	 std::string fact_key = facts.back();
         std::size_t args_key = facts.size() - 1 ;
         //std::cout << args_key << '\n';
         FactBase[fact_key][args_key].pop_back();
         std::cout << FactBase[fact_key][args_key].size() << '\n';
         TotFacts--;
}

std::vector<std::string> KRBase::queryRule(const std::vector<std::string>& query){
  return RuleBase[query[0]];
}

std::vector<std::string> KRBase::queryFacts(const std::vector<std::string>& query){
  std::vector<std::string> result;
  std::vector<std::string> facts = query;
  std::vector<int> search;
  std::vector<std::string> args;
  std::vector<std::string> comp;
  std::vector<int> search2;
  std::string temp ="";
  int counter = 0;
  const char* var = "$";
  for(int i = 0; i < facts.size()-1; i++){
    if (facts[i].front() != *var){
      search.push_back(i);
    }else{
      facts[i].erase(facts[i].begin());
      args.push_back(facts[i]);
      search2.push_back(i);
    }
  }
  for(int t = 0; t < FactBase[facts.back()][facts.size()-1].size();t++){
    comp = FactBase[facts.back()][facts.size()-1][t];
    counter = 0;
    for(int j = 0; j < search.size();j++){
      if( comp[search[j]] == facts[search[j]]) counter++;
    }
    if(counter == search.size()){
      for(int i = 0; i < search2.size(); i++){
        temp += args[i];
        temp += ":";
        temp +=comp[search2[i]];
        if (i != search2.size()-1) temp += ", ";
      };
    }
    std::cout <<temp << '\n';
    result.push_back(temp);
    temp = "";
  };
  return facts;
}

void KRBase::addRule(std::vector<std::string>& rules){
         std::string rule_key = rules.front();
         std::cout<<"HERE" <<rule_key << '\n';
         rules.pop_back();
         RuleBase[rule_key] = rules;
}

void KRBase::deleteRule(std::vector<std::string>& rules){
         std::string rule_key = rules.back();
         rules.pop_back();
         RuleBase[rule_key] = rules;
}
