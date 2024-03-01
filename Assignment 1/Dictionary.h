#pragma once
#include <vector>
#include "Words.h"

using namespace std;

//Dictionary class
//This class contains methods that implement the functions required in assignment 1
//Created by: Nicholas Foti
//Date created: 09/05/2023
class Dictionary
{
protected:
    vector<Word> dictionary;

public:
    Dictionary(); // Constructor
    ~Dictionary(); // Destructor

    void loadDictionary();
    void searchWord() const;
    void findZWords() const;
    void addWord();
};