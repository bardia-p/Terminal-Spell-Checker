#include "inc/autocorrectlib.h"

AutoCorrectContext::AutoCorrectContext() {
  contents = vector<string>();
  dictionary = map<string, vector<string>>();
}

void AutoCorrectContext::setContents(vector<string> contents) {
  this->contents = contents;
}

void AutoCorrectContext::addToDictionary(string word) {
  string key = makeSoundex(word);
  dictionary[key].push_back(word);
}

bool AutoCorrectContext::removeFromDictionary(string word) {
  string key = makeSoundex(word);
  if (dictionary.find(key) != dictionary.end()) {
    auto index = find(dictionary[key].begin(), dictionary[key].end(), word);

    if (index == dictionary[key].end()) {
      return false;
    } else {
      dictionary[key].erase(index);
      return true;
    }
  }
  return false;
}

bool AutoCorrectContext::buildDictionary(string fileName) {
  ifstream ifile(fileName);
  string word;

  if (ifile.is_open()) {
    while (ifile >> word) {
      addToDictionary(word);
    }
    ifile.close();
    return true;
  } else {
    cout << "Unable to open the file" << endl;
    return false;
  }
}

bool AutoCorrectContext::isInDictionary(string word) {
  string key = makeSoundex(word);

  if (dictionary.find(key) != dictionary.end()) {
    auto index = find(dictionary[key].begin(), dictionary[key].end(), word);

    if (index == dictionary[key].end()) {
      return false;
    } else {
      return true;
    }
  }
  return false;
}

map<string, string> AutoCorrectContext::checkSpelling() {
  map<string, string> incorrectWords;

  for (int i = 0; i < contents.size(); i++) {
    if (!isInDictionary(contents[i])) {
      incorrectWords[contents[i]] = "";
    }
  }
  return incorrectWords;
}

int AutoCorrectContext::charCode(char c) {
  c = toupper(c);
  if (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U' || c == 'H' ||
      c == 'W' || c == 'Y') {
    return '0';
  } else if (c == 'B' || c == 'F' || c == 'P' || c == 'V') {
    return '1';
  } else if (c == 'C' || c == 'G' || c == 'J' || c == 'K' || c == 'Q' ||
             c == 'S' || c == 'X' || c == 'Z') {
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

string AutoCorrectContext::makeSoundex(string word) {
  string soundexCode = "";
  char sameLetter = '\0';
  for (int i = 0; i < word.length(); i++) {
    if (i == 0) {
      soundexCode += word[0];
    } else {
      char soundexChar = charCode((char)word[i]);

      if (soundexChar != sameLetter && soundexChar != '0') {
        soundexCode += soundexChar;
        sameLetter = soundexChar;
      }
    }
  }

  if (soundexCode.length() > 4) {
    return soundexCode.substr(0, 4);
  } else if (soundexCode.length() < 4) {
    for (int i = soundexCode.length(); i < 4; i++) {
      soundexCode += '0';
    }
  }

  return soundexCode;
}

vector<string> AutoCorrectContext::makeSuggestions(string word) {
  string key = makeSoundex(word);
  vector<string> suggestions = vector<string>();

  if (dictionary.find(key) != dictionary.end()) {
    for (int i = 0; i < dictionary[key].size(); i++) {
      if (abs((int)(dictionary[key][i].length() - word.length())) <= 2) {
        suggestions.push_back(dictionary[key][i]);
      }
    }
  }

  return suggestions;
}

vector<string> AutoCorrectContext::getDictionary() {
  vector<string> dictionaryVector;

  for (auto const &it : dictionary) {
    for (int i = 0; i < it.second.size(); i++) {
      dictionaryVector.push_back(it.second[i]);
    }
  }

  return dictionaryVector;
}
