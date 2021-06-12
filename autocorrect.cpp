#include<iostream>

#include "autocorrectlib.cpp"

// Function signatures
std::string makeSoundex (std::string word);

int main() {
    std::cout<<"hello world" << std::endl;
    AutoCorrect autocorrect;

    autocorrect.addToDictionary("hello");

    autocorrect.setContents("hello world");
    std::cout<<autocorrect.removeFromDictionary("hello")<<std::endl;

}
