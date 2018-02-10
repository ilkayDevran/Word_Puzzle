
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "trie.h"

#define alphabetsize 23
int c = 0;
int removedCounter = 0;
int amountOfWordsWithPrefix = 0;

struct trienode *newnode() { //returns the address of an empty trie node
    struct trienode *node = NULL;
    node = (struct trienode *) malloc(sizeof (struct trienode));
    node -> aword = false;
    node -> numofchildren = 0;
    for (int i = 0; i < alphabetsize; i++)
        node->children[i] = NULL;
    c++;
    return node;
}


void add(struct trienode *rootnode, char *word) { //inserts the word into the trie if not already present
    int i, j;
    for (i = 0; i < strlen(word)-1 ; i++) {
        if (rootnode -> numofchildren == 0) {
            struct trienode *newNode = newnode();
            newNode ->key = word[i];
            rootnode -> children[rootnode->numofchildren] = newNode;
            rootnode->numofchildren++;
            rootnode = newNode;
        } else {
            for (j = 0; j < rootnode->numofchildren; j++) {
                if (rootnode->children[j]->key != word[i]) {
                    if (j == rootnode->numofchildren - 1) {
                        struct trienode * newNode = newnode();
                        newNode -> key = word[i];
                        rootnode -> children[rootnode -> numofchildren] = newNode;
                        rootnode ->numofchildren++;
                        rootnode = newNode;
                    }
                    continue;
                } else
                    rootnode = rootnode->children[j];
            }//for end
        }//else end
    }//for end
    rootnode->aword = true;
}

void removeall(struct trienode * rootnode) {
    if (rootnode->numofchildren == 0) {
        free(rootnode);
        removedCounter++;
    } else {
        struct trienode * currentnode;
        currentnode = rootnode;
        struct trienode * next;
        int i;
        for (i = 0; i < currentnode->numofchildren; i++) {
            next = currentnode->children[i];
            removeall(next);
            if (i == currentnode->numofchildren - 1) {
                free(currentnode);
                removedCounter++;
            }
        }
    }
}


int size(struct trienode * rootnode) {
    return c;
}

bool isempty(struct trienode * rootnode) {
    if (rootnode == NULL || rootnode->numofchildren == 0)
        return true;
    return false;
}

bool Search(struct trienode *root, char *word) {
    //printf("Search...len = %d\n word: %s\n",(int)strlen(word),word);
    int i, j;
    for (i = 0; i < strlen(word); i++)
        for (j = 0; j < root->numofchildren; j++) {
            if (word[i] == root->children[j]->key) {
                root = root->children[j];
                if ((i == strlen(word) - 1) && root ->aword == true) {
                    return true;
                }
                continue;
            }
            if (j == (root ->numofchildren) - 1) {
                return false;
            }
        }
    return false;
}

int countwordswithprefix(struct trienode *root, char *prefix) {
    int i = 0, j;
    for (i = 0; i < strlen(prefix); i++)
        for (j = 0; j < root->numofchildren; j++)
            if (root->children[j]->key == prefix[i]) {
                printf("node key %c\n ", root->key);
                root = root->children[j];
            }

    return amountOfWordsWithPrefix;
}

void printwordswithprefix(struct trienode *root, char *prefix) {

}

void removedCount(struct trienode * rootnode) {
    printf("Amount of removed trienodes: %d\n", removedCounter);
}

void printTree(struct trienode *rootnode, char* rootchar) { //I used printTree() instead of print() 
    if (rootnode -> numofchildren > 0) {
        if (rootnode->key != '\0')
            rootchar = AppendStringbyChar(rootchar, rootnode ->key);
        printf("Word: %s\n", rootchar);
        for (int i = 0; i < rootnode -> numofchildren; i++) {
            struct trienode *rootchild = rootnode -> children[i];
            printTree(rootchild, rootchar);
        }
    }
    else {
        if (rootnode->key != '\0')
            rootchar = AppendStringbyChar(rootchar, rootnode ->key);
        printf("Word: %s\n", rootchar);
    }
}

char *AppendStringbyChar(char *string, char c) {

    //Adding a character in a string
    size_t len = strlen(string);
    char *appended = malloc(len + 2);
    strcpy(appended, string);
    appended[len] = c;
    appended[len + 1] = '\0';

    return appended;
}
