#include "KRBase.h"
#include "RFITransaction.h"

void KRBase::addFact(std::vector<std::string> &facts){
         std::string fact_key = facts.back();
         std::size_t args_key = facts.size();

         FactBase[fact_key][args_key].push_back(facts);
         TotFacts++;
         return;
}

// std::vector<std::string> kRBase::parseFact(std::vector<std::string>& facts)
// :parseFact()

std::vector<std::string> KRBase::queryFacts(const std::vector<std::string>& query){
  std::vector<std::string> facts = query;
  std::vector<int> search;
  std::string arg;
  char* var;
  facts =RFITransaction::parseFact(facts);
  for(int i = 0; i < facts.size()-1; i++){
    arg = facts[i];
    std::cout << arg.front() << '\n';
    const char* var = "$";
    if (arg.front() != *var){
    search.push_back(i);
    std::cout << "got one" << '\n';
  }
  }
  // if (FactBase.find(facts.back()) != FactBase.end()){
  //   std::cout << "Found it" << '\n';
  // }
  std::vector<std::string> comp;
  int counter = 0;
  std::cout <<  facts.back() << '\n';
  for(int t = 0; t < FactBase[facts.back()][facts.size()-1].size();t++){
  comp = FactBase[facts.back()][facts.size()][t];
  counter = 0;
  std::cout << "here" << '\n';
  for(int j = 0; j < search.size();j++){
    std::cout << search[j] << '\n';
    if( comp[search[j]] == facts[search[j]]) std::cout << counter++ << '\n';
  }
  if(counter == search.size()) std::cout << "you foud one " << '\n';
};
  //for(int i = 0; i < search.size(); i++) std::cout << search[i] << '\n';
  std::vector<std::string> args;
  std::cout << facts[0] << '\n';
  return facts;
}


void KRBase::addRule(std::vector<std::string>& rules){
         std::string rule_key = rules.back();
         rules.pop_back();
         RuleBase[rule_key] = rules;
}
