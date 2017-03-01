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
  facts.pop_back();
  std::size_t args_key = facts.size() -1 ;
  FactBase[fact_key][args_key].push_back(facts);
  TotFacts++;
}



void KRBase::deleteFact(std::vector<std::string> &facts) {

void KRBase::deleteAllFacts(std::vector<std::string> &facts) {

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
>>>>>>> b58e760cc07218d3cc250e340185129efd7f69b7

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
std::vector<std::string> KRBase:: getFacts(){
  std::vector<std::string> facts;
  std::vector<std::string> alternative_facts;
  std::vector<std::vector<std::string>> fact_vects;
  //key_factnames are all the names of the facts
  std::vector<std::string> key_factnames = unlock::extract_keys(FactBase);
  std::vector<std::size_t> key_argcount;
  std::string fact_string = std::string();

  for(int i = 0; i < key_factnames.size(); i++){
    key_argcount = unlock::extract_keys(FactBase[key_factnames[i]]);
    for(int j = 0; j < key_argcount.size(); j++){
      for(int k = 0; k < FactBase[key_factnames[i]][key_argcount[j]].size(); i++){
        fact_vects.push_back(FactBase[key_factnames[i]][key_argcount[j]][k]);
      }
    }
  }

  for(int i = 0; i < fact_vects.size(); i++){
    for(int j = 0; j < fact_vects[i].size(); j++){
      fact_string += fact_vects[i][j];
      fact_string += (0 < (fact_vects.size()-j))?",":"";
    }
    facts.push_back(fact_string);
    fact_string = "";
  }
  fact_string = std::string();

  for(int i = 0; i < key_factnames.size(); i++){
    fact_string += "FACT ";
    fact_string += key_factnames[i];
    fact_string += "(";
    fact_string += facts[i];
    fact_string += ")";
    alternative_facts.push_back(fact_string);
    fact_string = std::string();
  }

  return alternative_facts;
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
