#include<iostream>
#include<string>
#include <fstream>
#include<vector>
#include<stdio.h>
#include"Words.h"
#include"Dictionary.h"
#include"ExtendedDictionary.h"


using namespace std;

int main()
{

	ExtendedDictionary myDictionary;

	while (true)
	{
		cout << "Choose a task:\n1. Load and parse the dictionary file\n2. Search for a word\n3. Find words with more than three 'z' characters\n4. Add a word to the dictionary\n5. List Palindromes\n6. List Rhyming Words\n7. Guessing Game\n8. Cheat at Searchdle\n9. Exit Application & Save highscores" << endl;
		char choice;
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice)
		{
		case '1':
			myDictionary.loadDictionary();
			break;
		case '2':
			myDictionary.searchWord();
			break;
		case '3':
			myDictionary.findZWords();
			break;
		case '4':
			myDictionary.addWord();
			break;
		case '5':
			myDictionary.listPalindromes();
			break;
		case '6':
			myDictionary.listRhymingWords();
			break;
		case '7':
			myDictionary.guessingGame();
			break;
		case'8':
			myDictionary.searchdle();
			break;
		case '9':
			cout << "Closing Applicaiton" << endl;
			return 0;
		default:
			cout << "Invalid input. Please try again." << endl;
			//Ignore any remaining characters so the loop will not repeat itself x amount of times
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		}
	}
}