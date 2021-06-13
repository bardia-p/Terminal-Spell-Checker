#ifndef AUTOCORRECT_LIB_H
#define AUTOCORRECT_LIB_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <fstream>

using namespace std;

class AutoCorrect {
  public:
    /**
     * The default constructor for the AutoCorrect class.
     */
    AutoCorrect();

    /**
     * Finds the soundex code for the given word.
     * @param word the word to generate soundex for.
     */
    string makeSoundex (string word);

    /**
     * Checks the spelling of all the words in the contents of the class and returns a list of words with incorrect spelling.
     * @return a list of words with incorrect spelling.
     */
    vector<string> checkSpelling ();

    /**
     * Gives a list of suggestions for the word with incorrect spelling.
     * @param wrongWords the list of the words that were marked as incorrect.
     * @return a list of suggestions for the word with incorrect spelling.
     */
    vector<string> makeSuggestions (string wrongWords);

    /**
     * Builds the dictionary from a given text file.
     */
    void buildDictionary (string fileName);

    /**
     * Adds a given word to the dictionary.
     * @param word is the word that needs to be added to the dictionary.
     */
    void addToDictionary (string word);

    /**
     * Removes a given word from the dictionary.
     * @param word is the word that needs to be removed from the dictionary.
     */
    bool removeFromDictionary (string word);

    /**
     * A setter for the contents attribute of the class.
     * @param contents for the contents of the class.
     */
    void setContents (vector<string> contents);
  private:
    /**
     * The contents that need to be spell checked.
     */
    vector<string> contents;

    /**
     * The dictionary that the program references for spell checking.
     */
    map<string, vector<string>> dictionary;

    /**
     * Returns the soundex code for the given character.
     */
    int charCode (char c);

    /**
     * Checks to see if a given word is in the dictionary.
     */
    bool isInDictionary (string word);
};

#endif
