#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>

#include "autocorrectlib.cpp"

using namespace std;

// Function signatures
// Input functions.
bool readFile(string filePath);
void readInput(int argc, char **argv);

void initializeSuggestions();

// UI and Commands
void inputUI();
void getStatus();
void makeSuggestions(string word);
void applySuggestion(string word, string suggestion);
void addToDictionary(string word);
void removeFromDictionary(string word);
void saveDictionary();
void switchDictionary();
void help();

// Print Functions
void printVector(vector<string> vectorToPrint, int colourCode);
void printMap(map<string, string> mapToPrint, int colour1, int colour2);

enum Color { black, red, green, yellow, blue, magenta, cyan, white };

static AutoCorrectContext ac;
static map<string, string> incorrectWords;
static map<string, vector<string>> suggestions;

int main(int argc, char **argv) {
  // Initiates the words in the dictionary
  ac.buildDictionary("files/wordslist.txt");

  if (argc == 3 && strcmp(argv[1], "-f") == 0) {
    // If the user wants to use a file input
    string filePath = argv[2];

    if (!readFile(filePath)) {
      return 0;
    }

  } else if (argc >= 3 && strcmp(argv[1], "-c") == 0) {
    // if the user wants a command line input
    readInput(argc, argv);

  } else {
    cout << "Invalid Input!" << endl;
    return 0;
  }

  cout << "\033[1;" << 30 + yellow << "m";
  cout << "AutoCorrect version 1.0.0" << endl;
  cout << "To get a list of commands enter 'help' or 'h'" << endl;
  cout << "\033[0m\n";

  // Gets the status of the input with the incorrect words.
  incorrectWords = ac.checkSpelling();

  // Creates a set of suggestions for all the incorrect words.
  initializeSuggestions();

  // Gets the inital status of the program.
  getStatus();

  // Calls the UI to ask the user for input.
  inputUI();

  return 0;
}

/**
 * Reads the file from input.
 * @param filePath the path to the file.
 */
bool readFile(string filePath) {
  vector<string> contents;
  string word;

  ifstream ifile(filePath);
  if (ifile.is_open()) {
    while (ifile >> word) {
      if (word[word.length() - 1] == '.' || word[word.length() - 1] == ',' ||
          word[word.length() - 1] == ';') {
        contents.push_back(word.substr(0, word.length() - 1));
      } else {
        contents.push_back(word);
      }
    }
    ifile.close();
    ac.setContents(contents);
    return true;
  } else {
    cout << "Unable to open the file" << endl;
    return false;
  }
}

/**
 * Reads the sentence from input.
 * @param argv the input arguments.
 */
void readInput(int argc, char **argv) {
  vector<string> contents;

  for (int i = 2; i < argc; i++) {
    string word = argv[i];
    if (word[word.length() - 1] == '.' || word[word.length() - 1] == ',' ||
        word[word.length() - 1] == ';') {
      contents.push_back(word.substr(0, word.length() - 1));
    } else {
      contents.push_back(word);
    }
  }
  ac.setContents(contents);
}

/**
 * Initiates the suggestions map for all the words.
 */
void initializeSuggestions() {
  for (auto const &it : incorrectWords) {
    string word = it.first;
    suggestions[word] = ac.makeSuggestions(word);
  }
}

/**
 * The main ui for the program.
 */
void inputUI() {
  string input = "";
  bool running = true;

  while (running) {
    cout << "\033[1;" << 30 + cyan << "m";
    cout << endl << "(autocorrect) ";
    getline(cin, input);
    cout << "\033[0m\n";

    istringstream ss(input);

    string word;
    string word1 = "";
    string word2 = "";

    int command = -1;

    while (ss >> word) {
      if (word == "quit" || word == "q") {
        command = 0;
      } else if (word == "status") {
        command = 1;
      } else if (word == "suggest") {
        command = 2;

        if (ss >> word) {
          word1 = word;
        } else {
          command = -1;
        }
      } else if (word == "apply") {
        command = 3;
        if (ss >> word) {
          word1 = word;
        } else {
          command = -1;
        }
        if (ss >> word) {
          word2 = word;
        } else {
          command = -1;
        }
      } else if (word == "add") {
        command = 4;
        if (ss >> word) {
          word1 = word;
        } else {
          command = -1;
        }
      } else if (word == "remove") {
        command = 5;
        if (ss >> word) {
          word1 = word;
        } else {
          command = -1;
        }
      } else if (word == "save") {
        command = 6;
      } else if (word == "switch") {
        command = 7;
      } else if (word == "help" || word == "h") {
        command = 8;
      }
    }

    if (command == 0) {
      cout << "Goodbye!" << endl;
      running = false;
    } else if (command == 1) {
      getStatus();
    } else if (command == 2) {
      makeSuggestions(word1);
    } else if (command == 3) {
      applySuggestion(word1, word2);
    } else if (command == 4) {
      addToDictionary(word1);
    } else if (command == 5) {
      removeFromDictionary(word1);
    } else if (command == 6) {
      saveDictionary();
    } else if (command == 7) {
      switchDictionary();
    } else if (command == 8) {
      help();
    } else {
      cout << "Invalid Command" << endl;
    }
  }
}

/**
 * Prints the status of the text (the list of a incorrect words).
 */
void getStatus() {
  if (incorrectWords.size() != 0) {
    printMap(incorrectWords, red, green);
  } else {
    cout << "Everything looks good!" << endl;
  }
}

/**
 * Gives suggestions for a given word.
 * @param word the word to give suggestions for.
 */
void makeSuggestions(string word) {
  if (incorrectWords.find(word) != incorrectWords.end()) {
    printVector(suggestions[word], blue);
  } else {
    cout << "The word that you entered is not one of the incorrect words"
         << endl;
  }
}

/**
 * Applies the suggestion for the given word.
 * @param word the word to change.
 * @param suggestion the suggestion to apply.
 */
void applySuggestion(string word, string suggestion) {
  if (incorrectWords.find(word) != incorrectWords.end()) {
    vector<string> suggestedWords = suggestions[word];
    auto index = find(suggestedWords.begin(), suggestedWords.end(), suggestion);
    if (index != suggestedWords.end()) {
      incorrectWords[word] = suggestion;
    } else {
      cout << "The suggestion is not among the list of the given suggestions"
           << endl;
    }
  } else {
    cout << "The word that you entered is not one of the incorrect words"
         << endl;
  }
}

/*
 * Adds a given word to the dictionary.
 * @parram the word to add to the dictionary.
 */
void addToDictionary(string word) {
  if (incorrectWords.find(word) != incorrectWords.end()) {
    incorrectWords[word] = word;
    ac.addToDictionary(word);
    initializeSuggestions();
  } else {
    cout << "The word that you entered is not one of the incorrect words"
         << endl;
  }
}

/*
 * Remove a given word from the dictionary.
 * @parram the word to remove from the dictionary.
 */
void removeFromDictionary(string word) {
  if (ac.removeFromDictionary(word)) {
    incorrectWords[word] = "";
    initializeSuggestions();
  } else {
    cout << "Could not find the word in the dictionary" << endl;
  }
}

/**
 * Saves the current version of the dictionary.
 */
void saveDictionary() {
  string filePath;

  cout << "Enter the path to save the dictionary in: ";
  getline(cin, filePath);

  ofstream newDictionary(filePath);

  vector<string> dictionary = ac.getDictionary();

  if (newDictionary.is_open()) {

    for (string word : dictionary) {
      newDictionary << word << endl;
    }

    newDictionary.close();
  } else {
    cout << "Could not find the path" << endl;
  }
}

/**
 * Changes the dictionary to the given one.
 */
void switchDictionary() {
  string filePath;

  cout << "Enter the path to the dictionary file: ";
  getline(cin, filePath);

  if (ac.buildDictionary(filePath)) {
    incorrectWords = ac.checkSpelling();
    initializeSuggestions();
    getStatus();
  }
}

/**
 * Gives a list of all the available commands.
 */
void help() {
  cout << "\033[1;" << 30 + magenta << "m";

  cout << "Here is a list of all the available commands:" << endl;

  cout << endl
       << "Use 'status' to get the current status of the program" << endl;
  cout << "-> Incorrect words are marked with red and all the corrections are "
          "marked with green."
       << endl;

  cout
      << endl
      << "Use 'suggest <word>' to get a list of suggestions for the given word."
      << endl;
  cout << "-> Note that the word you enter should be among the list of the "
          "incorrect words."
       << endl;

  cout << endl
       << "Use 'apply <word> <suggestion>' to replace the word with the "
          "suggestion."
       << endl;
  cout << "-> Note that the word you enter must be among the list of the "
          "incorrect words and the suggestion should be in the list of the "
          "suggestions for that word."
       << endl;

  cout << endl
       << "Use 'add <word>' to add a given word to the dictionary that the "
          "program uses."
       << endl;

  cout << endl
       << "Use 'remove <word>' to remove a given word from the dictionary that "
          "the program uses."
       << endl;

  cout << endl
       << "Use 'save' to save the current version of the dictionary "
          "that the program uses."
       << endl;
  cout << "-> You will be then prompted to enter the path to save the "
          "dictionary to."
       << endl;

  cout << endl
       << "Use 'switch' to switch the dictionary of the program to "
          "a new one."
       << endl;
  cout << "-> You will be then prompted to enter the path to load the "
          "dictionary from."
       << endl;

  cout << "\033[0m\n";
}

/**
 * Prints a given vector to the screen in a given colour.
 * @param vectorToPrint the vector to print to the screen.
 * @param colourCode the colour to print the vector in.
 */
void printVector(vector<string> vectorToPrint, int colourCode) {
  cout << "\033[1;" << 30 + colourCode << "m";
  for (int i = 0; i < vectorToPrint.size(); i++) {
    cout << vectorToPrint[i] << " ";
  }
  cout << "\033[0m\n";
}

/**
 * Prints a given map to the screen in a given colour.
 * @param mapToPrint the map to print to the screen.
 * @param colour1 the colour for the incorrect words.
 * @param colour2 the colour for the correct words.
 */
void printMap(map<string, string> mapToPrint, int colour1, int colour2) {
  vector<string> incorrect;
  vector<string> correct;

  for (auto const &it : mapToPrint) {
    if (it.second == "") {
      incorrect.push_back(it.first);
    } else {
      if (it.first == it.second) {
        correct.push_back("(added) " + it.first + " -> " + it.second + "\n");
      } else {
        correct.push_back(it.first + " -> " + it.second + "\n");
      }
    }
  }

  if (incorrect.size() > 0) {
    cout << "Incorrect words" << endl;
    printVector(incorrect, red);
  }

  if (correct.size() > 0) {
    cout << endl << "Corrections: " << endl;
    printVector(correct, green);
  }
}
