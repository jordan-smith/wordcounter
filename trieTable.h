#ifndef GUARD_trieTable_h
#define GUARD_trieTable_h

#include <string>
#include <cstring>

class TrieTable;
/*
 * TTNodes (TrieTable Nodes) operate as both leaf and non-leaf nodes.
 * leafCount holds the number of appearances of the word whose suffix is stored.
 * If leafCount == 0 then the TTNode is a non-leaf. In a non-leaf state,
 * letters points to the next possible characters in existing prefixes,
 * and branches points to the other nodes accessible from this.
 *
 * if leafCount > 0  <---> leaf
 * if leafCount == 0 <--->  non-leaf
 * if endWordCount > 0 <---> end of word
 */
class TTNode {
public:
	TTNode() {}
	TTNode(const char*);
private:
	char* letters;
	int leafCount, endWordCount;
	int size;
	int capacity;
	TTNode** branches;
	friend class TrieTable;
};

/*
 * TrieTable implements an abstract trie with the modification that nodes
 * contain counters for occurrences of words read from an input text file.
 * Node association (branching) is maintained by arrays that are occasionally
 * expanded/reallocated by pushCell().
 */
class TrieTable {
public:
	TrieTable();
	void printTable();
	void insert(const std::string&);
private:
	TTNode *root;
	const int notFound;
	int getPosition(TTNode*, char);
	void pushCell(char,TTNode*,int);
	void pushSuffix(TTNode*, const char*);
	void extendLeaf(TTNode*);
	void addLeaf(char,const char*,TTNode*);
	void traverse(TTNode*,std::string);
};

#endif
