#include "Dictionary.h"
#include<string>
#include <fstream>
#include<vector>
#include<algorithm>

using namespace std;

Dictionary::Dictionary() 
{
	cout << "Dictionary is being created..." << endl;
}

Dictionary::~Dictionary() 
{
	cout << "Dictionary is closing..." << endl;
}

//Load and Parse Dictionary Function
//This function will load the information from the dictionary.txt file, create a new instance of a Word struct and add it to the Dictionary vector
//Input: string filename
//Output: new instances in the dictionary vector of words
//Written by: Nicholas Foti
//Date Created 25/03/2023
void Dictionary::loadDictionary()
{
	string filename;
	string record;

	cout << "Enter the name of the file or type default to use the default file name (dictionary_2023S1.txt)";
	cin >> filename;

	//Set the file name if user requests default
	if (filename == "default")
	{
		filename = "dictionary_2023S1.txt";
		cout << "Attempting to read file...\n";
	}
	else
	{
		cout << "Attempting to read file...:\n";
	}

	//Open the file
	ifstream myfile(filename);

	if (!myfile.is_open())
	{
		cout << "Could not open the file..." << endl;
		return;
	}

	//Create an instance of Words to store the word information from .txt file
	Word word;

	//Until the end of the file the program will keep getting the records from each line.
	//If the line is <word> it will enter the if statement and add the name, type and definition to the dictionary vector.
	while (!myfile.eof())
	{
		getline(myfile, record);
		if (record == "<word>")
		{
			getline(myfile, record);
			word.setName(record);
			getline(myfile, record);
			word.setDefinition(record);
			getline(myfile, record);
			word.setType(record);
			dictionary.push_back(word);
		}
	}

	//Close the file
	myfile.close();
	cout << "Dictionary loaded successfully." << endl;
}

//Search for a word in the dictionary Function
//This function will take the users input and loop through the dictionary vector to see if the name exists. If it does the program will print the name, type, and definition of the word
//Input: a string taken from the user stored in the wordName variable
//Output: dictionary.name, dictionary.type, dictionary.definition
//Written By: Nicholas Foti
//Date Created: 29/03/2023
void Dictionary::searchWord() const
{
	if (dictionary.empty())
	{
		cout << "No dictionary loaded" << endl;
		return;
	}

	else
	{
		string wordName;
		cout << "Enter a word to search for: ";
		cin >> wordName;

		//Transform the users entry to lowercase
		transform(wordName.begin(), wordName.end(), wordName.begin(), ::tolower);

		//Set a variable to keep track of whether or not the word has been found
		bool foundWord = false;

		//Loop through the dictionary, if the string wordName matches dictionary.name continue and print the type and definition of the word on the following lines
		for (int i = 0; i < dictionary.size(); i++)
		{
			if (dictionary[i].getName() == wordName)
			{
				foundWord = true;
				dictionary[i].printDefinition();
				return;
			}
		}

		//If foundWord is still false at the end of the dictionary, print word not found.
		if (foundWord == false)
		{
			cout << "Word not found" << endl;
		}
	}
}

//Find all words with more than three z characters function
//This function will loop through all words in the dictionary vector and locate any that contain more than 3 z's and print it to console
//Input: N/A
//Output: dictionary.name
//Written by: Nicholas Foti
//Date Created: 29/03/2023
void Dictionary::findZWords() const
{
	//Print a message if the dictionary has not yet been loaded and parsed
	if (dictionary.empty())
	{
		cout << "No dictionary loaded" << endl;
		return;
	}

	//Set a variable to keep track of whether or not the word has been found
	bool foundWord = false;

	//Loop through each word in the dictionary vector to see if the word name contains more than three z
	for (int i = 0; i < dictionary.size(); i++)
	{
		string name = dictionary[i].getName();
		if (count(name.begin(), name.end(), 'z') > 3)
		{
			foundWord = true;
			cout << name << endl;
			continue;
		}
	}

	//If there is no words with more than three z characters print a message
	if (foundWord == false)
	{
		cout << "No words contain more than three 'z' characters" << endl;
		return;
	}
}

//Add a word to the dictionary and save as new dictionary function
//This function will add a new word to the dictionary and allow the user to save it under a custom .txt
//Input: New word instance
//Output: A new instance in the dictionary vector & .txt file
//Written By: Nicholas Foti
//Date Created: 30/03/2023 
void Dictionary::addWord()
{
	//Print a message if the dictionary has not yet been loaded and parsed
	if (dictionary.empty())
	{
		cout << "No dictionary loaded" << endl;
		return;
	}

	Word word;
	string wordName;
	string wordType;
	string wordDefinition;

	//Enter the new word name and check if it already exists
	cout << "Enter the new word name: " << endl;
	cin >> wordName;
	word.setName(wordName);
	for (int i = 0; i < dictionary.size(); i++)
	{
		if (dictionary[i].getName() == word.getName())
		{
			cout << "Error: word exists, elevated privileges required to edit existing words." << endl;
			return;
		}
	}

	cout << "Enter the type of the word (n, v, adv, adj, prep, pn, n_and_v, misc): " << endl;
	cin >> wordType;
	word.setType(wordType);

	//Check if the word type has been entered correctly and prompt user to re-enter
	while (word.getType() != "n" && word.getType() != "v" && word.getType() != "adv" && word.getType() != "adj" && word.getType() != "prep" && word.getType() != "pn" && word.getType() != "n_and_v" && word.getType() != "misc")
	{
		cout << "Invalid word type entered. Please re-enter a valid type" << endl;
		cin >> wordType;
	}

	//Enter the definition and push the new word into the dictionary vector
	cout << "Enter the definition of the word: " << endl;
	cin.ignore();
	getline(cin, wordDefinition);
	word.setDefinition(wordDefinition);
	dictionary.push_back(word);
	cout << "Word added successfully" << endl;

	string filename;
	cout << "Enter the file name to save the dictionary under: (.txt file)" << endl;
	cin >> filename;

	//Open the newly created file and write the dictionary in the same format as the original
	ofstream myfile(filename);
	if (myfile.is_open())
	{
		for (Word word : dictionary)
		{
			myfile << "<word>\n" << word.getName() << "\n" << word.getDefinition() << "\n" << word.getType() << "\n" << "</word>" << endl;
		}
		myfile.close();
		cout << "Dictionary saved successfully to file." << endl;
	}
	else
	{
		cout << "Error: Unable to open file for writing." << endl;
	}
}