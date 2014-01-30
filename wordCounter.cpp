/*
 * wordCounter.cpp
 * Reads the file from input, inserting each word into the TrieTable. Then prints the
 * contents of the TrieTable as a list of (word -> count) pairs in reverse alphabetical
 * order.
 *
 *  Created on: Feb 2, 2013
 *      Author: Jordan Smith
 */
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cctype>
#include <cstdlib>
#include "trieTable.h"

using namespace std;
/*
 * Trim trailing punctuation
 */
void trimPunc(char *s){
	for(int i = strlen(s)-1; ispunct(s[i]) || s[i] == '\"' || s[i] == '\''; i--){
		s[i] = '\0';
	}
}

int main(int argc, char* argv[]) {
	string filename;
	if (argc != 2) {
		cout << "Enter the file name: ";
		cin >> filename;
	}
	else
		filename = string(argv[1]);
	ifstream inputFile(filename.c_str());
	if (!inputFile.is_open()) {
		cout << "Cannot open " << filename << endl;
		exit(-1);
	}
	TrieTable trieCounter;
	string word;
	while(inputFile.good()){
		inputFile >> word;
		if(inputFile.fail())
			break;
		trieCounter.insert(word);
	}
	trieCounter.printTable();
	inputFile.close();
	return 0;
}
