#include "autocorrectlib.h"

AutoCorrect::AutoCorrect(){
    contents = "";
    dictionary = std::vector<std::string>();
}

void AutoCorrect::setContents (std::string contents){
  this->contents = contents;
}

void AutoCorrect::addToDictionary (std::string word){
  dictionary.push_back(word);
  std::cout<<dictionary.front() << std::endl;
}

bool AutoCorrect::removeFromDictionary (std::string word){
  auto index =  std::find(dictionary.begin(), dictionary.end(), word);

  if (index == dictionary.end()){
    return false;
  }
  else {
    dictionary.erase(index);
    return true;
  }
}

std::vector<std::string> AutoCorrect::checkSpelling (){
  
}

/*
std::string AutoCorrect::makeSoundex (std::string word);




std::vector<std::string> AutoCorrect::makeSuggestions (std::vector<std::string> wrongWords);


void AutoCorrect::buildDictionary (std::string fileName);*/
