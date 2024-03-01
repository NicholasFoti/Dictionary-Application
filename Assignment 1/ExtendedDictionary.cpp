#include "ExtendedDictionary.h"
#include<sstream>
#include<ctime>
#include<algorithm>
#include<vector>


using namespace std;

ExtendedDictionary::ExtendedDictionary() : Dictionary() 
{
    cout << "ExtendedDictionary is being created..." << endl;
    loadHighScore();
}

ExtendedDictionary::~ExtendedDictionary() 
{
    cout << "ExtendedDictionary is closing..." << endl;
    saveHighScore();
}

//List all palindromes in the dictionary file
//This function will loop through the dictionary and check if the word is a palindrom
//It will reverse the word and check if the reversed word equals the original word
//Input: N/A
//Output: All words that are palindromes (name variable)
//Written by: Nicholas Foti
//Date created: 10/05/2023
void ExtendedDictionary::listPalindromes() 
{
    if (dictionary.empty())
    {
        cout << "No dictionary loaded" << endl;
        return;
    }

    // Loop through the dictionary
    for (Word word : dictionary) 
    {
        string name;
        name = word.getName();
        string rev = name;
        reverse(rev.begin(), rev.end());
        // Check if the word is a palindrome
        if (name == rev) 
        {
            cout << name << endl;
        }
    }
}

//List all rhyming words in the dictionary file
//This function will prompt the user to enter a word and print any words in the dictionary that rhyme
//It will loop through the dictionary file and display any words that end in the same last 3 characters as the given word
//Input: String taken from the user and stored in the inputWord variable
//Output: All words in the dictionary that end in the same last 3 characters (name variable)
//Written by: Nicholas Foti
//Date created: 10/05/2023
void ExtendedDictionary::listRhymingWords()
{
    if (dictionary.empty())
    {
        cout << "No dictionary loaded" << endl;
        return;
    }

    string inputWord;
    cout << "Enter a word: ";
    cin >> inputWord;

    if (inputWord.size() < 3) 
    {
        cout << "Word should be at least 3 characters long." << endl;
        return;
    }

    string endOfWord;
    endOfWord = inputWord.substr(inputWord.size() - 3);

    // Loop through the dictionary
    for (Word word : dictionary) 
    {
        string name;
        name = word.getName();
        // Check if the last three letters of the word match the input
        if (name.size() >= 3 && name.substr(name.size() - 3) == endOfWord) 
        {
            cout << name << endl;
        }
    }
}

//Load high score function
//This function aids the guessing game function by loading the users high score from previous attempts
//This opens the highscore text file and takes the data and stores it in the highscore variable
//Input: N/A
//Output: highScore varible with up to date data
//Written by: Nicholas Foti
//Date created 11/05/2023
void ExtendedDictionary::loadHighScore()
{
    ifstream highScoreFile("highscore.txt");
    if (highScoreFile.is_open())
    {
        highScoreFile >> highScore;
        highScoreFile.close();
    }
    else
    {
        highScore = 0;
    }
}

//Save high score function
//This function aids the guessing game function by saving the users high score when their score is greater than the highScore variable
//It will open the highscore text file and store the current score in there
//Input: N/A
//Output: Updates highscore file with new highscore
//Written by: Nicholas Foti
//Date created: 11/05/2023
void ExtendedDictionary::saveHighScore()
{
    ofstream highScoreFile("highscore.txt");
    if (highScoreFile.is_open())
    {
        highScoreFile << highScore;
        highScoreFile.close();
    }
}

//Guessing game function
//This function acts as a game for the user to play where the function will choose a random word form the dictionary and make sure it has more than 4 words in the definition
//It will then replace the fourth word with _'s and ask the user to try and guess what the word is
//If the user guesses correctly it will add 10 points to their score and ultimately update their highscore using the load and save highscore functions
//Input: Users guess (guess variable)
//Output: Either the correct word (hiddenWord variable) if the guess is incorrect of a congratulaion message and score += 10 
//Written by: Nicholas Foti
//Date created: 11/05/2023
void ExtendedDictionary::guessingGame()
{
    if (dictionary.empty())
    {
        cout << "No dictionary loaded" << endl;
        return;
    }

    srand(time(NULL)); // seed random number generator
    int score = 0;
    string guess;

    cout << "Welcome to the Guessing game! Current High Score: " << highScore << endl;

    while (true)
    {
        // Choose a random word from the dictionary
        int randomWord = rand() % dictionary.size();
        Word word = dictionary[randomWord];

        //Split the definition
        istringstream iss(word.getDefinition());
        vector<string> definitionWords((istream_iterator<string>(iss)), istream_iterator<string>());

        //Check the definition has at least 4 words
        if (definitionWords.size() < 4)
            continue;

        //Replace the fourth word with _'s
        string hiddenWord;
        hiddenWord = definitionWords[3];
        definitionWords[3] = string(hiddenWord.size(), '_');

        //Present the word and definition to the player
        cout << "Word: " << word.getName() << endl;
        cout << "Definition: ";
        for (const string& defWord : definitionWords)
            cout << defWord << " ";
        cout << "\n";

        //Ask the player to guess the fourth word
        cout << "Guess the fourth word: ";
        cin >> guess;

        //Check the guess
        if (guess == hiddenWord)
        {
            cout << "Congratulations!\n";
            score += 10;
            if (score > highScore)
            {
                highScore = score;
                cout << "New high score: " << highScore << "!" << endl;
            }
        }
        else
        {
            cout << "Incorrect. The fourth word was: " << hiddenWord << "\n";
            cout << "Your score: " << score << "\n";
            break;
        }
    }
}

//Cheat at searchdle function
//This funciton asks the user to enter criteria such as the length of the mystery word, grey letters, yellow and green letters and their positions
//The function will take these inputs and search through the dictionary to find words that match these criteria
//The function will find any words matching the criteria and push them onto the matchingWords vector which will be presented to the user
//Input: Users entered criteria
//Output: Vector of matching words (vector<string> matchingWords) where the word name is printed to the user
//Created by: Nicholas Foti
//Date created: 13/05/2023
void ExtendedDictionary::searchdle()
{
    if (dictionary.empty())
    {
        cout << "No dictionary loaded" << endl;
        return;
    }

    cout << "Welcome to the searchdle cheater!\nTo take full effect of this function please take a few guesses and get rid of as many letters as possible" << endl;
    int mysteryWordLength;
    cout << "Enter the length of the mystery word: ";
    cin >> mysteryWordLength;

    string excludedLetters;
    cout << "Enter the grey letters (no spaces between letters e.g. abcd, press enter if unknown) : ";
    cin.ignore();
    getline(cin, excludedLetters);

    string requiredLetters;
    cout << "Enter the yellow and green letters (no spaces between letters e.g. abcd, press enter if unknown) : ";
    getline(cin, requiredLetters);

    string letterPositions;
    cout << "Enter the green letter positions (Format: letter-number e.g a1p3, press enter if unknown): ";
    getline(cin, letterPositions);

    // Convert all input to lowercase for case-insensitive matching
    transform(excludedLetters.begin(), excludedLetters.end(), excludedLetters.begin(), ::tolower);
    transform(requiredLetters.begin(), requiredLetters.end(), requiredLetters.begin(), ::tolower);

    vector<string> matchingWords;

    for (Word word : dictionary)
    {
        string currentWord;
        currentWord = word.getName();
        // Convert each word to lowercase for case-insensitive matching
        transform(currentWord.begin(), currentWord.end(), currentWord.begin(), ::tolower);

        bool match = true;

        // Check if the word has the same number of letters as the 'mystery' word
        if (currentWord.length() != mysteryWordLength)
            match = false;

        // Check if the word contains any excluded letters
        for (char letter : excludedLetters)
        {
            if (currentWord.find(letter) != string::npos)
            {
                match = false;
                break;
            }
        }

        // Check if the word contains all the required letters anywhere in the word
        for (char letter : requiredLetters)
        {
            if (currentWord.find(letter) == string::npos)
            {
                match = false;
                break;
            }
        }

        // Check if the word contains the required letters at the specified positions
        for (int i = 0; i < letterPositions.length(); i += 2)
        {
            char letter = letterPositions[i];
            int position = letterPositions[i + 1] - '0';  // Convert the position character to an integer

            if (currentWord.length() < position || currentWord[position - 1] != letter)
            {
                match = false;
                break;
            }
        }

        if (match)
            matchingWords.push_back(word.getName());
    }

    if (matchingWords.empty())
        cout << "No words found matching the criteria." << endl;
    else
    {
        cout << "Possible Answers with given criteria: " << endl;
        for (string& word : matchingWords)
        {
            cout << word << endl;
        }
    }
}