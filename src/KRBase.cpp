#include "KRBase.h"


KRBase::KRBase(){

}

bool KRBase::isKeyinF(std::string key){
  return FactBase.count(key)>.0;
}

bool KRBase::isKeyinR(std::string key){
  return RuleBase.count(key)>0;
}

/*
  This function takes in a vector of strings and adds it to the Fact Database
  which is a map<string, map<string, vector<vector <string>>>>.
*/
void KRBase::addFact(std::vector<std::string> &facts){
  //Get name of the Fact which is the last element of the vector
  std::string fact_key = facts.back();
  facts.pop_back();
  FactBase[fact_key][args_key].push_back(facts);
  TotFacts++;
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
  //std::cout << facts[0].front() << '\n';
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
  return result;
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

/* This function is similr to addFact, except this one adds a Rule to the
  Rule Database which is represented as a map<string, vector<string>>. The
  key value is the name of the rule we want to add and the vaue is a string of
  vectors that contain the parameters that satisfy that rule.
*/
void KRBase::addRule(std::vector<std::string>& rules){
  std::vector<std::string>& v = rules;
  std::cout << "Adding Rule: ";
  for(int i = 0; i < v.size(); i++) {
    std::cout << v[i] << " ";
  }
  std::cout << "\n";
  /* The last element contains the name of the rule. We need it in order to know
   where on the map we should save the Rule */
  std::string rule_key = rules.back();
  rules.pop_back();
  RuleBase[rule_key] = rules;
}

void KRBase::deleteAllRules(){
  RuleBase.erase(RuleBase.begin(),RuleBase.end());
}
void KRBase::deleteAllFacts(){
  FactBase.erase(FactBase.begin(),FactBase.end());
 }
