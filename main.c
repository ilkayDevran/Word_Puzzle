/* 
 * File:   main.c
 * Author: ilkay
 *
 * Created on October 9, 2017, 10:29 AM
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "puzzle.h"
#include "trie.h"

struct trienode *trieHead = NULL;

void readFromFile(const char *filename);
void play();
void clearAll();
void search4Prefix();

int main() {
    trieHead = newnode();
    if (isempty(trieHead))//Check whether trieHead is empty or not
        printf("\n-Trie is empty. This is a test message for isempty() method-\n");

    play(); //creates puzzle, puzzlewords linked list, trietree and searches matching words and prints them out

    printf("\nWould you like to print all words in Trietree? (Y/N)\n");
    char decision;
    scanf("%c", &decision);
    decision = toupper(decision);
    if (decision == 'Y') {
        printTree(trieHead, "");
    }
    clearAll(); //remove all nodes of trietree and clear the memory 


    return 0;
}

void readFromFile(const char *filename) { //readFromFile("/Users/ilkay/Desktop/test.txt", "r+");
    FILE *fp = NULL;
    char word[512];
    if ((fp = fopen("TurkishWords.txt", "r")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }
    while (fgets(word, 512, fp)) {
        int length = (int) strlen(word);
        char* line = malloc(sizeof (char)*(length));
        strncpy(line, word, length);
        add(trieHead, line);
    }
    fclose(fp);
}

void play() {

    readFromFile("TurkishWords.txt"); //Read From TurkishWords.txt and add words into trietree

    //create two puzzlewords nodes headOFPWs and tempHead to 
    struct puzzlewords * headOfPWs = newPuzzleWords();
    struct puzzlewords * tempHead = newPuzzleWords();

    headOfPWs = GetAllWords(); //keep head of puzzlewords list
    tempHead = headOfPWs;

    //start from head of wordpuzzles list and search matching words with TurkishWords.txt 
    while (headOfPWs->next != NULL) {
        if (Search(trieHead, headOfPWs->next->word) == true) //return into true valid of a word if it matches with a word from Turkishword.txt
            headOfPWs->next->valid = 1;
        headOfPWs = headOfPWs->next;
    }
    //print all matched words which their valid is true
    int count = 0;
    printf("*************************\n* LIST OF MATCHED WORDS *\n");
    while (tempHead ->next != NULL) {
        if (tempHead->next->valid == 1)
            printf("* %d. word = %s\t* \n", count, tempHead->next->word);
        tempHead = tempHead->next;
        count++;
    }
    printf("*************************\n");
}

void clearAll() {
    printf("\n-----------------------------------\nSize of Trietree: %d\n", size(trieHead));
    removeall(trieHead);
    removedCount(trieHead); // my own method which helps me to compare size of tree with removed node count
    printf("-----------------------------------\n");
}

void search4Prefix() {
    printf("\nDo you want to check for any words starts with a prefix you want? (Y/N)\n");
    char decision;
    char prefix[20];
    int x;
    scanf("%c", &decision);
    decision = toupper(decision);
    if (decision == 'Y') {
        printf("Then please type the prefix you search\n");
        scanf("%s", prefix);
        printf("Amount of words start with '%s': %d\n", prefix, countwordswithprefix(trieHead, prefix));


    }
}