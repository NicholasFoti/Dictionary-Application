#pragma once
#include<string>
#include<iostream>

using namespace std;

//Word class
//This class replaced the word struct from assignment 1
//It encapsulates the functionality of a word and includes the getters, setters and constructos
//It also includes the printDefinition method which is used to print the name, type and definition that is used when searching for a word
//Created by: Nicholas Foti
//Date created: 09/05/2023
class Word {
private:
    string name;
    string type;
    string definition;

public:
    // Constructor
    Word(const string& name = "", const string& type = "", const string& definition = "")
        : name(name), type(type), definition(definition) {}

    // Getters
    string getName() const { return name; }
    string getType() const { return type; }
    string getDefinition() const { return definition; }

    // Setters
    void setName(const string& name) { this->name = name; }
    void setType(const string& type) { this->type = type; }
    void setDefinition(const string& definition) { this->definition = definition; }

    // Print word definition function
    void printDefinition() const 
    {
        cout << "Name: " << name << "\n";
        string type_name;
        if (type == "n") type_name = "[noun]";
        else if (type == "v") type_name = "[verb]";
        else if (type == "adv") type_name = "[adverb]";
        else if (type == "adj") type_name = "[adjective]";
        else if (type == "prep") type_name = "[preposition]";
        else if (type == "pn") type_name = "[proper noun]";
        else if (type == "n_and_v") type_name = "[noun and verb]";
        else if (type == "misc") type_name = "[miscellaneous]";
        cout << "Type: " << type_name << "\n";
        cout << "Definition: " << definition << "\n";
    }
};