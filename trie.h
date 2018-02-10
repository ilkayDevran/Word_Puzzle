/* 
 * File:   trie.h
 * Author: ilkay
 *
 * Created on October 14, 2017, 3:48 PM
 */

#ifndef TRIE_H
#define TRIE_H

#include <stdbool.h>
#define alphabetsize 23

struct trienode {
    char key; //the character that it stores
    struct trienode *children[alphabetsize]; //an array that keeps the children of the node
    //aword==false means that all chars from the root up to this doesn’t form a word (default)
    //aword==true means that all chars from the root up to this forms a word 
    bool aword;
    int numofchildren; //the number of children that are already inserted <=alphabetsize 
};


struct trienode *newnode(); //returns the address of an empty trie node +
void add(struct trienode *rootnode, char *word); //inserts the word into the trie if not already present +
//void Remove(struct trienode *rootnode, char *word); // removes the word from the trie if present ------
void removeall(struct trienode *rootnode); // removes all words from the trie +
//void print(struct trienode *rootnode); // prints the trie structure in the format shown below -------
int size(struct trienode *rootnode); // returns the number of trie nodes +
bool isempty(struct trienode *rootnode); // returns whether the trie structure is empty or not +
bool Search(struct trienode *root, char *word); // explores whether the word appears in the trie or not +
int countwordswithprefix(struct trienode *root, char *prefix); // returns the number of words that have the given prefix
//void printwordswithprefix(struct trienode *root, char *prefix);// ------


void removedCount(struct trienode *rootnode);
void printTree(struct trienode *rootnode, char* rootchar);
char *AppendStringbyChar(char *string, char c);
bool isChild(struct trienode *rootnode, struct trienode *node);
int childno(struct trienode *rootnode, struct trienode *node);
struct trienode *charnode(struct trienode *rootnode, char *ch);
#endif /* TRIE_H */

