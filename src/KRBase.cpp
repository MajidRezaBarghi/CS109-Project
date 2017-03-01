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

void KRBase::deleteAllFacts(std::vector<std::string> &facts) {
	 std::string fact_key = facts.back();
         std::size_t args_key = facts.size() - 1 ;
         //std::cout << args_key << '\n';
         FactBase[fact_key][args_key].pop_back();
         std::cout << FactBase[fact_key][args_key].size() << '\n';
         TotFacts--;
}

// std::vector<std::string> KRBase::queryRule(std::string query){
//   return RuleBase[query];
// }

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

std::vector<std::string> KRBase::getRules(){
  std::vector<std::string> rules;
  std::string ret_string = "";
  auto keys = unlock::extract_keys(RuleBase);
  for(int i=0;i < keys.size(); i++){
    ret_string += "RULE ";
    ret_string += std::string(keys[i]) + ":- ";
    for(int j = 0; j < RuleBase[keys[i]].size(); j++){
      ret_string += RuleBase[keys[i]][j];
      ret_string += (j == (RuleBase[keys[i]].size()-1))?" ":"";
    }
    rules.push_back(ret_string);
    rules.push_back(RuleBase[keys[i]].back());
    std::cout<<rules[i];
    ret_string = "";
  }

  return rules;
}

void KRBase::addRule(std::vector<std::string>& rules){
  std::vector<std::string>& v = rules;
  std::cout << "Adding Rule: ";
  for(int i = 0; i < v.size(); i++) {
    std::cout << v[i] << " ";
  }
  std::cout << "\n";
         std::string rule_key = rules.back();
         rules.pop_back();
         RuleBase[rule_key] = rules;
}

void KRBase::deleteAllRules(){
  auto ret_vector = unlock::extract_keys(RuleBase);
  for (int i = 0; i < RuleBase[ret_vector[i]].size(); i++){
    //std::cout << RuleBase[ret_vector[i]] << " ";
    //for(int j = ret_vector.begin(); j < ret_vector.size(); j++) {
        RuleBase[ret_vector[i]].erase(ret_vector.begin());
    //}
  }
}
