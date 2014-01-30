/*
 * trieTable.cpp
 * Implements an associative trie in which each word is a key for
 * the number of times it has been inserted from the input source.
 *  Created on: Feb 2, 2013
 *      Author: Jordan
 */

#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include "trieTable.h"

using namespace std;

/*
 * TTNode is always initialized in Leaf state.
 */
TTNode::TTNode(const char* suf) : leafCount(1), endWordCount(0), size(0), capacity(0) {
	letters = new char[strlen(suf)+1];
	branches = 0;
	if (letters == 0) {
		cerr << "Out of space!";
		exit(-1);
	}
	strcpy(letters, suf);
}

TrieTable::TrieTable() : notFound(-1) {
	root = 0;
}

/*
 * Performs a depth-first traversal from the current node by first checking for words in
 * all subtries and then for a word that ends at the current node.
 */
void TrieTable::traverse(TTNode *node, string sofar = "") {
	if (strlen(node->letters) == 0) {
		cout << sofar << " " << node->leafCount << endl;
	}
	else if (node->leafCount > 0) {
		cout << sofar + node->letters << " " << node->leafCount << endl;
	}
	else {
		for(int i = node->size-1; i >= 0; i--){
			traverse(node->branches[i], sofar + node->letters[i]);
		}
	}
	if (node->endWordCount > 0){
		cout << sofar << " " << node->endWordCount << endl;
	}
}

/*
 * Performs output for the SpaceX coding test
 */
void TrieTable::printTable() {
	TTNode *node = root;
	if(node == 0){
		return;
	}
	traverse(node);
}

/*
 * Determines the index of a character if it exists among letters in
 * the given node. If not, returns -1.
 */
int TrieTable::getPosition(TTNode *node, char ch) {
	int pos;
	for (pos = 0; pos < node->size && node->letters[pos] != ch; pos++);
	if (pos < node->size)
		return pos;
	else return notFound;
}

/*
 * Adds a character to the given node's array of letters. The character
 * is inserted at the position pos. If the array is at capacity, it is
 * reallocated and its elements are copied. letters are maintained in
 * alphabetical order.
 */
void TrieTable::pushCell(char ch, TTNode *node, int pos) {
	if(node->size < node->capacity-1){
		for(int i = node->size; i > pos; i--){
			node->letters[i] = node->letters[i-1];
			node->branches[i] = node->branches[i-1];
		}
		node->letters[pos] = ch;
		node->branches[pos] = 0;
		node->size++;
	}
	else{
		char *tempL = node->letters;
		TTNode **tempB = node->branches;
		size_t newcap = node->capacity*2;
		node->letters = new char[newcap];
		node->branches = new TTNode*[newcap-1];
		if(node->letters == 0 || node->branches == 0) {
			//TODO: exit the program or raise error
		}
		node->capacity = newcap;
		for (int i = 0; i < pos; i++){
			node->letters[i] = tempL[i];
			node->branches[i] = tempB[i];
		}
		node->letters[pos] = ch;
		node->branches[pos] = 0;
		for(int i = pos; i < node->size; i++){
			node->letters[i+1] = tempL[i];
			node->branches[i+1] = tempB[i];
		}
		for(int i = ++(node->size); i < node->capacity; i++ )
			node->letters[i] = '\0';
		delete [] tempL;
		delete [] tempB;
	}
}

/*
 * Attaches a leaf as a new child of the node, pointed to from the position
 * of ch.
 */
void TrieTable::addLeaf(char ch, const char *suf, TTNode *node){
	int pos = getPosition(node,ch);
	if (pos == notFound) {
		for (pos = 0; pos < node->size && node->letters[pos] < ch; pos++);
		pushCell(ch,node,pos);
	}
	node->branches[pos] = new TTNode(suf);
}

/*
 * Transforms a leaf node into a non-leaf by pushing all letters except the first into
 * a leaf, pointed two by the first letter.
 */
void TrieTable::extendLeaf(TTNode* node){
	if(node->leafCount == 0){
		cerr << "Attempt to extend nonleaf containing letters: " << node->letters << endl;
	}
	char* s = node->letters;
	node->letters = new char[1];
	node->size = 0;
	node->capacity = 1;
	*(node->letters) = '\0';
	addLeaf(*s, s+1, node);
	node->branches[0]->leafCount = node->leafCount;
	node->leafCount = 0;
	delete [] s;
}

/*
 * Recursively follows the path representing the given suffix. If a leaf is reached before
 * the end of the suffix, extends the trie as much as necessary until all common prefixes
 * diverge.
 */
void TrieTable::pushSuffix(TTNode* node, const char *suf){
	if(*suf == '\0'){
		if(strlen(node->letters) == 0)
			node->leafCount++;
		else
			node->endWordCount++;
		return;
	}
	if(node->leafCount > 0){
		if(strlen(node->letters) == 0){
			node->endWordCount = node->leafCount;
			node->leafCount = 1;
			delete [] node->letters;
			node->letters = new char[strlen(suf)+1];
			if(node->letters == 0){
				cerr << "Out of memory." << endl;
				exit(1);
			}
			strcpy(node->letters, suf);
			return;
		}
		if(strcmp(node->letters, suf) == 0){
			node->leafCount++;
			return;
		}
		extendLeaf(node);
		if (*suf == *(node->letters)) {
			pushSuffix(node->branches[0], suf+1);
		}
		else{
			addLeaf(*suf, suf+1, node);
		}
		return;
	}
	else {
		int pos = getPosition(node,*suf);
		if (pos == notFound) {
			addLeaf(*suf, suf+1, node);
		}
		else {
			pushSuffix(node->branches[pos], suf+1);
		}
	}
}

void TrieTable::insert(const string &word){
	if(root == 0)
		root = new TTNode(word.c_str());
	else
		pushSuffix(root, word.c_str());
}




