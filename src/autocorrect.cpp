#include <iostream>
#include <cstring>
#include <fstream>
#include <filesystem>
#include <sstream>

#include "autocorrectlib.cpp"

using namespace std;

// Function signatures
void printVector(vector<string> vectorToPrint, int colourCode);
void inputGUI();
void getStatus();
void makeSuggestions(string word);
bool readFile(string filePath);
void readInput( int argc, char **argv);

enum Color { black, red, green, yellow, blue, magenta, cyan, white };

static AutoCorrect autocorrect;
static vector<string> incorrectWords;
static vector<string> suggestions;

int main(int argc, char **argv) {
  // Initiates the words in the dictionary
  autocorrect.buildDictionary("files/wordslist.txt");

  if (argc == 3 && strcmp(argv[1], "-f") == 0) {
    // If the user wants to use a file input
    string filePath = argv[2];

    if (!readFile(filePath)){
      return 0;
    }

  } else if (argc>= 3 && strcmp(argv[1], "-c") == 0) {
    // if the user wants a command line input
    readInput(argc, argv);

  } else {
    cout << "Invalid Input!" << endl;
    return 0;
  }


  getStatus();

  inputGUI();

  return 0;
}

/**
 * Reads the file from input.
 * @param filePath the path to the file.
 */
bool readFile(string filePath){
  vector<string> contents;
  string word;

  ifstream ifile (filePath);
  if (ifile.is_open()) {
    while (ifile >> word) {
      contents.push_back(word);
    }
    ifile.close();
    autocorrect.setContents(contents);
    return true;
  }
  else {
    cout << "Unable to open the file" << endl;
    return false;
  }
}

/**
 * Reads the sentence from input.
 * @param argv the input arguments.
 */
void readInput(int argc, char **argv){
  vector<string> contents;

  for (int i = 2; i < argc; i++) {
    contents.push_back((string)argv[i]);
  }
  autocorrect.setContents(contents);
}

/**
 * The main gui for the program.
 */
void inputGUI(){
  string input = "";
  bool running = true;

  while (running){
    cout << "(autocorrect) ";
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
      getStatus();
    } else if (command = 2) {
      makeSuggestions(wordChoose);
    } else {
      cout << "Invalid Command" << endl;
    }
  }
}

/**
 * Prints the status of the text (the list of a incorrect words).
 */
void getStatus(){
  incorrectWords = autocorrect.checkSpelling();
  if (incorrectWords.size()!=0){
    printVector(incorrectWords, red);
  } else {
    cout << "Everything looks good!" << endl;
  }
}

/**
 * Gives suggestions for a given word.
 * @param word the word to give suggestions for.
 */
void makeSuggestions(string word){
  if (find(incorrectWords.begin(), incorrectWords.end(), word)!= incorrectWords.end()){
    suggestions = autocorrect.makeSuggestions(word);
    printVector(suggestions, blue);
  } else {
    cout << "The word that you entered is not one of the incorrect words" << endl;
  }
}

/**
 * Prints a given vector to the screen in a given colour.
 * @param vectorToPrint the vector to print to the screen.
 * @param colourCode the colour to print the vector in.
 */
void printVector(vector<string> vectorToPrint, int colourCode){
  cout << "\033[1;" << 30 + colourCode << "m";
  for (int i = 0; i < vectorToPrint.size(); i++){
    cout << vectorToPrint[i] << " ";
  }
  cout << "\033[0m\n";
}
