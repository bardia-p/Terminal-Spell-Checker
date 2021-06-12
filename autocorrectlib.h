#ifndef AUTOCORRECT_LIB_H
#define AUTOCORRECT_LIB_H

#include <iostream>
#include <vector>
#include <algorithm>

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
    std::string makeSoundex (std::string word);

    /**
     * Checks the spelling of all the words in the contents of the class and returns a list of words with incorrect spelling.
     * @return a list of words with incorrect spelling.
     */
    std::vector<std::string> checkSpelling ();

    /**
     * Gives a list of suggestions for the word with incorrect spelling.
     * @param wrongWords the list of the words that were marked as incorrect.
     * @return a list of suggestions for the word with incorrect spelling.
     */
    std::vector<std::string> makeSuggestions (std::vector<std::string> wrongWords);

    /**
     * Builds the dictionary from a given text file.
     */
    void buildDictionary (std::string fileName);

    /**
     * Adds a given word to the dictionary.
     * @param word is the word that needs to be added to the dictionary.
     */
    void addToDictionary (std::string word);

    /**
     * Removes a given word from the dictionary.
     * @param word is the word that needs to be removed from the dictionary.
     */
    bool removeFromDictionary (std::string word);

    /**
     * A setter for the contents attribute of the class.
     * @param contents for the contents of the class.
     */
    void setContents (std::string contents);
  private:
    /**
     * The contents that need to be spell checked.
     */
    std::string contents;

    /**
     * The dictionary that the program references for spell checking.
     */
    std::vector<std::string> dictionary;
};

#endif
