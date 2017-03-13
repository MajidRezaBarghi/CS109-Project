
#include "RFITransaction.h"

static std::vector<std::string> default_vector;

RFITransaction::RFITransaction(){

}
void RFITransaction:: removeCharsFromString( std::string &str, char* charsToRemove ) {
  for ( unsigned int i = 0; i < strlen(charsToRemove); ++i ) {
    str.erase( remove(str.begin(), str.end(), charsToRemove[i]), str.end() );
  }
}
std::vector<std::string> RFITransaction:: split(const std::string &s, char delim) {
  std::stringstream ss(s);
  std::string item;
  std::vector<std::string> tokens;
  while (getline(ss, item, delim)) {
    tokens.push_back(item);
  }
  return tokens;
}



std::vector<std::string> RFITransaction::parseFact(std::vector<std::string>& facts){
  std::string concat_string = "";
  std::string fact_name;
  std::vector<std::string> tokens = facts;
  for (std::vector<std::string>::iterator it = tokens.begin();it!= tokens.end(); it++){
    concat_string += *it;
  }
  tokens = split(concat_string, '(');
  fact_name = tokens[0];
  tokens = split(tokens[1],')');
  tokens = split(tokens[0],',');
  tokens.push_back(fact_name);
  return tokens;
}

std::vector<std::string> RFITransaction::parseRule(std::vector<std::string> &rules){

  std::vector<std::string> tokens = rules;

  char lose[] = ":-";
  removeCharsFromString(tokens[0],lose);
  std::vector<std::string> temp;
  temp.push_back(tokens[0]);
  std::vector<std::string>::iterator it = tokens.begin();
  tokens.erase(it);
  tokens.push_back(temp[0]);

  return tokens;
}
std::vector<std::string> RFITransaction::parseInference(std::vector<std::string> queries){
  std::vector<std::string> tokens = parseFact(queries);
  return tokens;
}

void RFITransaction::FACT(std::string fact_string){
  std::vector<std::string> facts;
  facts.push_back(fact_string);
  std::vector<std::string>tokens = parseFact(facts);
  krbase.addFact(tokens);
}

void RFITransaction::RULE(std::string rule_string) {
  std::vector<std::string> rules;
  rule_string.erase(0,5); // erases 'RULE'
  rules.push_back(rule_string);
  std::vector<std::string>tokens = parseRule(rules);
  std::vector<std::string> temp_vect = split(tokens[0],' ');
  std::string temp = tokens[1];
  tokens = temp_vect;
  tokens.push_back(temp);
  for(int i = 0; i < tokens.size(); i++){
  }
  krbase.addRule(tokens);
}

std::vector<std::string> RFITransaction::INFERENCE(std::vector<std::string> &set_facts,bool t = true){
  std::vector<std::vector<std::string>> vrules;
  std::vector<std::string> vQ;
  std::vector<std::string> rules;
  std::vector<std::string> replacements;
  std::vector<std::string> resultsA;
  int number  = krbase.numOfArgs(set_facts[0]);
  vQ = parseFact(set_facts);
  if(krbase.isKeyinR(vQ.back())){
    vrules = krbase.queryRule(vQ.back(),number);
    std::map<std::string,int> rule_map;
    while(vrules.size()!=0){
      rules = vrules.back();
      replacements = vQ;
      replacements.pop_back();
      rules = krbase.parseRule(rules,replacements);

      vrules.pop_back();
      rule_map["OR"]= 1;
      rule_map["AND"] =2;
      switch(rule_map[rules[0]]) {
        case 1:
          for(int i = 1; i < rules.size(); i++) {
            std::vector<std::string> temp;
            temp.push_back(rules[i]);
            temp = INFERENCE(temp,false);
            resultsA.insert(resultsA.end(),temp.begin(),temp.end());
          }
          break;
        case 2:
          std::vector<std::string> temp;
          std::vector<std::string> results;
          std::vector<std::string> tempargs;
          temp.push_back(rules[1]);
          results = INFERENCE(temp,false);
          temp.pop_back();
          tempargs = krbase.getArgs(rules[2]);
          for(int j = 0; j <results.size();j++){
            std::string save = rules[2];
            for (int i = 0;i<tempargs.size();i++){
              std::string s = "\\";
              std::string p = "\\"+tempargs[i];
              std::regex rep (p);
              s +=tempargs[i];
              s = "("+s;
              s +="):(\\w+)";
              std::regex e (s);
              std::smatch sm;
              std::regex_search(results[j],sm,e);
              if (sm[2].length()){
                std::string repThis = static_cast<std::string>(sm[2]);
                save = std::regex_replace(save,rep,repThis);
              }
            }
            temp.push_back(save);
            auto a = INFERENCE(temp,false);
            temp.pop_back();
            if (a.size()){
              for(int t=0; t<a.size();t++){
                std::regex remove ("[^\\$]\\w+:\\w+");
                a[t] = std::regex_replace(a[t],remove,"");
                std::string res = results[j] + a[t];
                resultsA.push_back(res);
              }
            }
          }
          break;
      }
    }
  }
  if(krbase.isKeyinF(vQ.back())){
    return krbase.queryFacts(vQ);
  }
  return resultsA;
}
void RFITransaction::LOAD(std::string file_name){
  std::vector<std::string> qres;
  std::ifstream in_file;
  in_file.open(file_name, std::ios_base::in);

  if(in_file.is_open()){

    std::string line;
    std::map<std::string,int> parser_map;

    parser_map["FACT"] = 1;
    parser_map["RULE"] = 2;
    parser_map["INFERENCE"] = 3;

    while(std::getline(in_file,line)){
      // flag tells us if rule,inference,fact
      std::string flag;

      std::vector<std::string> items;
      std::string next;
      // string to input stream
      std::istringstream iss(line);

      // tokenize the string and parse
      iss >> flag;
      while(iss >> next){
        items.push_back(next);
      }

      switch(parser_map[flag]){
        case 1:
          items = parseFact(items);
          krbase.addFact(items);
          break;
        case 2:
          items = parseRule(items);
          krbase.addRule(items);
          break;

        case 3:
          std::cout << items[0] << '\n';
          qres = INFERENCE(items);
          for (int l=0; l<qres.size();l++){
            std::vector<std::string> tempargs = krbase.getArgs(items[0]);
            for(int k=0;k<tempargs.size();k++){
              std::string s = "\\";
              s +=tempargs[k];
              s = "("+s;
              s +="):(\\w+)";
              std::regex e (s);
              std::smatch sm;
              std::regex_search(qres[l],sm,e);
              std::string suptemp = static_cast<std::string>(sm[0]);
              suptemp.erase(suptemp.begin());
              std::cout << suptemp<<" ";
            }
            std::cout <<'\n';
          }
          std::cout <<'\n';
          // add parsedRule to KB
          break;

        default:
          throw "error, that command was not found";
          break;
      }

    }

  }else{
    throw "Error could not open file";
  }

}
void RFITransaction::DROP(){
  krbase.deleteAllFacts();
  krbase.deleteAllRules();
}

void RFITransaction::DUMP(std::string file_name) {
  std::ofstream dump_file;
  std::vector<std::string> rules;
  std::vector<std::string> facts;
  rules = krbase.getRules();
  facts = krbase.getFacts();
  dump_file.open(file_name);
  if(dump_file.is_open()){
    for(int i = 0; i < facts.size(); i++){
      dump_file << facts[i] << std::endl;
    }
    for(int i = 0; i < rules.size(); i++) {
      dump_file << rules[i] << std::endl;
    }
  }else{
    throw "FILE ERROR: File could not open";
  }
  dump_file.close();
}
