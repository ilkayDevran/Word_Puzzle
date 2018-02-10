/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   puzzle.h
 * Author: ilkay
 *
 * Created on October 14, 2017, 3:30 PM
 */

#ifndef PUZZLE_H
#define PUZZLE_H

struct puzzlewords {
    char word [6];
    int valid;
    struct puzzlewords *next;
    struct puzzlewords *backward;
};
struct puzzlewords * GetAllWords();
void findPossibleWords(int x, int y, char *str, int depth, int prev[5]);
char *Append(char *str,char c);
void AddNewWord(char str[6]);
void PrintAllWords();
void fill_arr(char arr[][6]);
void print_arr(char arr[][6]);
struct puzzlewords *newPuzzleWords();

#endif /* PUZZLE_H */

