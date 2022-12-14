/* Created by Niko Klemm on 29.11.22. */

#ifndef HANGMAN_MAIN_H
#define HANGMAN_MAIN_H
#include "database.h"

int main(void);
char* getRandomWord(void);
int play(char*);
char input(void);
int output(int, int);

#endif /* HANGMAN_MAIN_H */
