#include "inc/autocorrectlib.h"

AutoCorrect::AutoCorrect(){
    contents = vector<string>();
    dictionary = map<string,vector<string>>();
}

void AutoCorrect::setContents (vector<string> contents){
  this->contents = contents;
}

void AutoCorrect::addToDictionary (string word){
  string key = makeSoundex(word);
  dictionary[key].push_back(word);
}

bool AutoCorrect::removeFromDictionary (string word){
  string key = makeSoundex(word);
  if (dictionary.find(key) != dictionary.end()){
    auto index =  find(dictionary[key].begin(), dictionary[key].end(), word);

    if (index == dictionary[key].end()){
      return false;
    }
    else {
      dictionary[key].erase(index);
      return true;
    }
  }
  return false;
}

void AutoCorrect::buildDictionary (string fileName){
  ifstream ifile (fileName);
  string word;

  if (ifile.is_open()) {
    while (ifile >> word) {
      addToDictionary(word);
    }
    ifile.close();
  }
  else {
    cout << "Unable to open the file" << endl;
  }
}

bool AutoCorrect::isInDictionary (string word){
  string key = makeSoundex(word);

  if (dictionary.find(key) != dictionary.end()){
    auto index =  find(dictionary[key].begin(), dictionary[key].end(), word);

    if (index == dictionary[key].end()){
      return false;
    }
    else {
      return true;
    }
  }
  return false;
}

vector<string> AutoCorrect::checkSpelling (){
  vector<string> incorrectWords;

  for (int i = 0; i < contents.size(); i++){
    if (!isInDictionary(contents[i])){
      incorrectWords.push_back(contents[i]);
    }
  }
  return incorrectWords;
}

int AutoCorrect::charCode (char c){
  c = toupper(c);
  if (c == 'A' || c == 'E'|| c == 'I' || c == 'O' ||
      c == 'U' || c == 'H' || c == 'W' || c == 'Y') {
      return '0';
  } else if (c == 'B' || c == 'F' || c == 'P' || c == 'V') {
      return '1';
  } else if (c == 'C' || c == 'G' || c == 'J' || c == 'K' ||
      c == 'Q' || c == 'S' || c == 'X' || c == 'Z') {
      return '2';
  } else if (c == 'D' || c == 'T') {
      return '3';
  } else if (c == 'M' || c == 'N') {
      return '4';
  } else if (c == 'L') {
      return '5';
  } else {
      return '6';
  }
}

string AutoCorrect::makeSoundex (string word){
  string soundexCode = "";
  char sameLetter = '\0';
  for (int i = 0; i < word.length(); i++){
    if (i == 0){
      soundexCode += word[0];
    } else {
      char soundexChar = charCode((char)word[i]);

      if (soundexChar != sameLetter && soundexChar != '0'){
        soundexCode += soundexChar;
        sameLetter = soundexChar;
      }
    }
  }

  if (soundexCode.length() > 4){
    return soundexCode.substr(0,4);
  } else if (soundexCode.length() < 4) {
    for (int i = soundexCode.length(); i<4; i++){
      soundexCode += '0';
    }
  }

  return soundexCode;
}

vector<string> AutoCorrect::makeSuggestions (string word){
  string key = makeSoundex(word);
  vector<string> suggestions = vector<string>();

  if (dictionary.find(key) != dictionary.end()){
    for (int i = 0; i < dictionary[key].size(); i++){
      if (abs((int)(dictionary[key][i].length() - word.length())) <= 1){
        suggestions.push_back(dictionary[key][i]);
      }
    }
  }

  return suggestions;
}
