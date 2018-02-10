/* 
 * File:   main.c
 * Author: ilkay
 *
 * Created on October 9, 2017, 10:29 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "puzzle.h"
#define size 6

struct puzzlewords *head; //head of puzzlewords list
struct puzzlewords *currentNode;
char map[size][size];
int counter = 0;

struct puzzlewords * GetAllWords() {

    //Create and print the puzzle map
    fill_arr(map);
    print_arr(map);

    //Initialization of puzzlewords pointers
    head = newPuzzleWords();
    currentNode = newPuzzleWords();

    //create array with default variables "-1" to keep passed coordinates during search 
    int prev[size];
    for (int k = 0; k < 6; k++)
        prev[k] = -1;

    //call recursive function for all char in puzzle
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            findPossibleWords(i, j, "", 0, prev);

    //printf("TOTAL Counter: %d\n", counter);

    //print all found words which are in nodes of puzzlewords list 
    //PrintAllWords();

    return head;
}

void findPossibleWords(int x, int y, char *str, int depth, int prev[6]) {

    //Recursive Function to find all possible words in map
    int prevcpy[6];
    for (int k = 0; k < 6; k++)
        prevcpy[k] = prev[k];

    int current_x = x;
    int current_y = y;

    if (depth > 5)
        return;

    prevcpy[depth] = current_x * 10 + current_y;
    depth++;
    str = Append(str, map[current_x][current_y]);
    AddNewWord(str);

    int alreadyPassed;
    for (int i = -1; i < 2; i++)
        for (int j = -1; j < 2; j++) {
            current_x = x + i;
            current_y = y + j;

            alreadyPassed = 0;
            int prValue = current_x * 10 + current_y;
            for (int k = 0; k < 6; k++) { //k<size -1
                if (prevcpy[k] == prValue) {
                    alreadyPassed = 1;
                    //break;
                }
            }

            if (!(current_x < 0 || current_x > 5 || current_y < 0 || current_y > 5) && !(i == 0 && j == 0) && alreadyPassed == 0)
                findPossibleWords(current_x, current_y, str, depth, prevcpy);

        }
}

char *Append(char *str, char c) {

    //Adding a character in a string
    size_t len = strlen(str);
    char *str2 = malloc(len + 2);
    strcpy(str2, str);
    str2[len] = c;
    str2[len + 1] = '\0';

    return str2;
}

void AddNewWord(char str[6]) {

    //Add a new created word in a newpuzzleowrds node's char array and add the node end of the list
    struct puzzlewords *Words = newPuzzleWords();
    strncpy(Words->word, str, sizeof (Words->word));
    Words->valid = 0;
    counter++;
    if (counter == 1) {
        head -> next = Words;
        currentNode = Words;
    } else {
        currentNode ->next = Words;
        currentNode = Words;
    }
}

void PrintAllWords() {

    //Print words in nodes of puzzlewords list
    struct puzzlewords *cur;
    cur = head->next;
    while (cur != NULL) {
        printf("%s\t", cur->word);
        cur = cur->next;
    }
}

void fill_arr(char arr[][size]) {

    //Create 2D array of random characters
    char lower[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'r', 's', 't', 'u', 'v', 'y', 'z'};
    int length = sizeof (lower);
    srand(time(NULL));
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++) {
            arr[i][j] = lower[rand() % (length)];
        }
}

void print_arr(char arr[][size]) {
    //Print out 2D array of random characters
    printf(" ______________\n| WORD PUZZLE  |\n");
    for (int i = 0; i < size; i++) {
        printf("| ");
        for (int j = 0; j < size; j++) {
            printf("%c ", arr[i][j]);
            if (j + 1 == size) {
                printf(" |\n");
            }
        }
    }
    printf("|______________|\n\n");

}

struct puzzlewords *newPuzzleWords() {

    //Initialization of a new puzzlewords pointer
    struct puzzlewords *newPuzzleword = NULL;
    newPuzzleword = (struct puzzlewords *) malloc(sizeof (struct puzzlewords));
    //newPuzzleword-> word[0] = "";
    newPuzzleword -> valid = 0;
    newPuzzleword -> next = NULL;

    return newPuzzleword;
}