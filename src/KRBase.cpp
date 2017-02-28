#include "KRBase.h"
#include "RFITransaction.h"

void KRBase::addFact(std::vector<std::string> &facts){
         std::string fact_key = facts.back();
         std::size_t args_key = facts.size() -1 ;
         std::cout << args_key << '\n';
         FactBase[fact_key][args_key].push_back(facts);
         //std::cout << FactBase[fact_key][args_key].size() << '\n';
         TotFacts++;
}

void KRBase::deleteFact(std::vector<std::string> &facts) {
	 std::string fact_key = facts.back();
         std::size_t args_key = facts.size() - 1 ;
         std::cout << args_key << '\n';
         FactBase[fact_key][args_key].pop_back(facts);
         //std::cout << FactBase[fact_key][args_key].size() << '\n';
         TotFacts--;
}

// std::vector<std::string> kRBase::parseFact(std::vector<std::string>& facts)
// :parseFact()

std::vector<std::string> KRBase::queryFacts(const std::vector<std::string>& query){
  std::vector<std::string> facts = query;
  std::vector<int> search;
  // std::vector<std::string> v;
  // std::vector<std::string> v1;
  // std::vector<std::string> v2;
  // v.push_back("Fact(a5,a2,a4)");
  // v1.push_back("Fact(a5,a3,a6)");
  // v2.push_back("Fact(a5,a7,a8)");
  // addFact(v);
  // addFact(v1);
  // addFact(v2);
  std::string arg;
  //test.queryFacts(v);
  const char* var = "$";
  facts =RFITransaction::parseFact(facts);
  for(int i = 0; i < facts.size()-1; i++){
    arg = facts[i];
    std::cout << arg.front() << '\n';
    if (arg.front() != *var){
      search.push_back(i);
      std::cout << arg << '\n';
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
  comp = FactBase[facts.back()][facts.size()-1][t];
  counter = 0;
  std::cout << "here" << '\n';
  for(int j = 0; j < search.size();j++){
    std::cout<<"You are here!!" << search[j] << '\n';
    if( comp[search[j]] == facts[search[j]]) std::cout<<"THIS IS THE COUNTER" << counter++ << '\n';
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
