#include "KRBase.h"


KRBase::KRBase(){

}

bool KRBase::isKeyinF(std::string key){
  return FactBase.count(key)>.0;
}

bool KRBase::isKeyinR(std::string key){
  return NewRuleBase.count(key)>0;
}
int KRBase::numOfArgs(std::string key){
  int args_key = 0;
  std::smatch sm;
  std::regex keysearch("\\w+");
  std::regex_search(key,sm,keysearch);
  key = sm.suffix();
  keysearch = "(\\$\\w+)|(\\w+)";
  while (std::regex_search(key,sm,keysearch)) {
    //std::cout <<"Check point 1" <<sm[0] << '\n';
    args_key++;
    key = sm.suffix();
  }
  return args_key;
}
std::vector<std::string> KRBase::getArgs(std::string args){
  std::vector<std::string> arguments;
  std::smatch sm;
  std::regex keysearch("\\$\\w+");
  while (std::regex_search(args,sm,keysearch)) {
    arguments.push_back(sm[0]);
    args = sm.suffix();
  }
  return arguments;
};
std::vector<std::string> KRBase::parseRule(std::vector<std::string> v,std::vector<std::string> args){
  std::vector<std::string> args1 = getArgs(v.back());
  v.pop_back();
  while (args.size()!=0) {
    args1.back() = "\\"+args1.back();
    std::regex rep (args1.back());
    for(int i=1; i < v.size(); i++){
          v[i] = std::regex_replace(v[i],rep,args.back());
          //std::cout << v[i] << '\n';
    }
    args.pop_back();
    args1.pop_back();
  }
  return v;
}
/*
  This function takes in a vector of strings and adds it to the Fact Database
  which is a map<string, map<string, vector<vector <string>>>>.
*/
void KRBase::addFact(std::vector<std::string> &facts){
  //Get name of the Fact which is the last element of the vector
  std::string fact_key = facts.back();
  facts.pop_back();
  FactBase[fact_key][facts.size()].push_back(facts);
  TotFacts++;
}


std::vector<std::vector<std::string>> KRBase::queryRule(const std::string query,int args_key){
  return NewRuleBase[query][args_key];
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
      //facts[i].erase(facts[i].begin());
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
      for(int i = 0; i < comp.size(); i++){
        temp += facts[i];
        temp += ":";
        temp +=comp[i];
        if (i != comp.size()-1) temp += ", ";
      };
    }
    if (temp.length()){
    //std::cout <<temp << '\n';
    result.push_back(temp);
    }
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
      fact_vects = FactBase[key_factnames[i]][key_argcount[j]];
      for(int k = 0; k < fact_vects.size(); k++){
        for(int t =0;t< fact_vects[k].size();t++){
        fact_string += fact_vects[k][t];
        fact_string += (1 < (fact_vects[k].size()-t))?",":"";
        }
        facts.push_back(fact_string);
        fact_string = "";
      }
    }
    for(int j = 0; j < facts.size(); j++){
      fact_string += "FACT ";
      fact_string += key_factnames[i];
      fact_string += "(";
      fact_string += facts[j];
      fact_string += ")";
      alternative_facts.push_back(fact_string);
      fact_string = std::string();
    }
    facts = std::vector<std::string>();
  }
  return alternative_facts;
}

std::vector<std::string> KRBase::getRules(){
  std::vector<std::string> rules;
  std::vector<std::string> alternative_rules;
  std::vector<std::vector<std::string>> rule_vects;
  //key_factnames are all the names of the facts
  std::vector<std::string> key_rulenames = unlock::extract_keys(NewRuleBase);
  std::vector<std::size_t> key_argcount;
  std::string rule_string = std::string();
  for(int i = 0; i < key_rulenames.size(); i++){
    key_argcount = unlock::extract_keys(NewRuleBase[key_rulenames[i]]);
    std::vector<std::string> args;
    for(int j = 0; j < key_argcount.size(); j++){
      rule_vects = NewRuleBase[key_rulenames[i]][key_argcount[j]];
      std::vector<std::string> tempargs;
      for(int k = 0; k < rule_vects.size(); k++){
        tempargs = getArgs(rule_vects[k].back());
        rule_vects[k].pop_back();
        std::string TEMP;
        for(int t = 0;t<tempargs.size();t++){
          TEMP += tempargs[t];
          TEMP += (1 < (tempargs.size()-t))?",":"";
        }
        args.push_back(TEMP);
        TEMP = "";
        for(int t = 0; t < rule_vects[k].size(); t++){
          rule_string += rule_vects[k][t];
          rule_string += (1 < (rule_vects[k].size()-t))?" ":"";
        }
        rules.push_back(rule_string);
        rule_string = "";
      }
    }
    for(int j=0; j< rules.size();j++){
      rule_string += "RULE ";
      rule_string += key_rulenames[i];
      rule_string += "(";
      rule_string += args[j];
      rule_string += ")";
      rule_string += ":-";
      rule_string += rules[j];
      alternative_rules.push_back(rule_string);
      rule_string = std::string();
    };
    rules = std::vector<std::string>();
  }

  return alternative_rules;

}

/* This function is similr to addFact, except this one adds a Rule to the
  Rule Database which is represented as a map<string, vector<string>>. The
  key value is the name of the rule we want to add and the vaue is a string of
  vectors that contain the parameters that satisfy that rule.
*/
void KRBase::addRule(std::vector<std::string>& rules){
  std::vector<std::string>& v = rules;
  /* The last element contains the name of the rule. We need it in order to know
   where on the map we should save the Rule */
  int args_key = 0;
  std::string args = "";
  std::regex keysearch ("\\w+");
  std::smatch sm;
  std::regex_search(rules.back(),sm,keysearch);
  std::string rule_key = sm[0];
  rules.back() = sm.suffix();
  keysearch = "(\\$\\w+)";
  while (std::regex_search(rules.back(),sm,keysearch)) {
    args +=sm[0];
    args_key++;
    rules.back() = sm.suffix();
  }
  rules.pop_back();
  rules.push_back(args);
  NewRuleBase[rule_key][args_key].push_back(rules);
}
void KRBase::deleteAllRules(){
  RuleBase.erase(RuleBase.begin(),RuleBase.end());
}
void KRBase::deleteAllFacts(){
  FactBase.erase(FactBase.begin(),FactBase.end());
 }
