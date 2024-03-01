#pragma once
#include"Dictionary.h"
#include<fstream>

//Extended Dictionary class
//This class is an extension of the dictionary class that adds additional funcitonality
//This class provides methods to list palindromes, find rhyming words, guess the definition game, and cheat at searchdle
//Created by: Nicholas Foti
//Date created: 9/05/2023
class ExtendedDictionary : public Dictionary
{
private:
    int highScore;

public:
    ExtendedDictionary();
    ~ExtendedDictionary();


    // Define any additional functions for ExtendedDictionary here
    void listPalindromes();
    void listRhymingWords();
    void guessingGame();
    void loadHighScore();
    void saveHighScore();
    void searchdle();
};
