#include <iostream>
#include <cstring>
#include <fstream>
#include <filesystem>
#include <sstream>

#include "autocorrectlib.cpp"

using namespace std;

// Function definitions
void printVector(vector<string> vectorToPrint, int colourCode);

enum Color { black, red, green, yellow, blue, magenta, cyan, white };

int main(int argc, char **argv) {
  vector<string> contents;
  AutoCorrect autocorrect;

  // Initiates the words in the dictionary
  autocorrect.buildDictionary("sources/wordslist.txt");

  // If the user wants to use a file input
  if (argc == 3 && strcmp(argv[1], "-f") == 0) {
    string filename = argv[2];
    string word;

    ifstream ifile (filename);
    if (ifile.is_open()) {
      while (ifile >> word) {
        contents.push_back(word);
      }
      ifile.close();
      autocorrect.setContents(contents);
    }
    else {
      cout << "Unable to open the file" << endl;
      return 0;
    }
  } else if (argc>= 3 && strcmp(argv[1], "-c") == 0) {
    // if the user wants a command line input
    for (int i = 2; i < argc; i++) {
      contents.push_back((string)argv[i]);
    }
    autocorrect.setContents(contents);
  } else {
    cout << "Invalid Input!" << endl;
    return 0;
  }


  vector<string> incorrectWords = autocorrect.checkSpelling();
  printVector(incorrectWords, red);

  string input = "";
  bool running = true;

  while (running){
    getline(cin,input);

    istringstream ss(input);

    string word;
    string wordChoose = "";

    int command = -1;

    while (ss >> word){
        if (word == "quit" || word == "q"){
          command = 0;
        } else if (word == "status") {
          command = 1;
        } else if (word == "suggest") {
          command = 2;

          if (ss >> word) {
            wordChoose = word;
          } else {
            command = -1;
          }
        }
    }

    if (command == 0){
      cout << "Goodbye!" << endl;
      running = false;
    } else if (command == 1){
      printVector(incorrectWords, red);
    } else if (command = 2) {
      vector<string> suggestedWords = autocorrect.makeSuggestions(wordChoose);
      printVector(suggestedWords, green);
    } else {
      cout << "Invalid Command" << endl;
    }
  }

  cout<<autocorrect.makeSoundex("wappy");
  return 0;
}

void printVector(vector<string> vectorToPrint, int colourCode){
  cout << "\033[1;" << 30 + colourCode << "m";
  for (int i = 0; i < vectorToPrint.size(); i++){
    cout << vectorToPrint[i] << " ";
  }
  cout << "\033[0m\n";
}
