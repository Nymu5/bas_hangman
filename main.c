#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include "database.h"
#include "main.h"

int amount = 40;
char *words[40] = {"Exotisch", "Ewig", "Eier", "Verstanden", "Gruender", "Vorhang", "Abhaengen", "Faelscher", "Schmuggler", "Gazelle", "Raupe", "Vorsichtig", "Muster", "Selektiv", "Wirtschaft", "Naehren", "Verkleinert", "Femur", "Phobisch", "Abschnitt", "Huegel", "Fangen", "Krachmacher", "Kroete", "Gewinnbringend", "Schiff", "Blinzeln", "Inflation", "Stehend", "Atemlos", "Wuenschen", "Ablehnen", "Evakuieren", "Vorhersage", "Voraussagen", "Bleistift", "Brennen", "Bruellen", "Geben", "Melodie"};

char* getRandomWord(void) {
    srand(time(NULL));
    return words[rand() % amount];
}

char input(void) {
    char input;
    printf("Naechster Buchstabe: ");
    fflush(stdin);
    scanf(" %c", &input);
    return input;
}

int output(int length, int wrongs) {
    int i;
    for (i = 0; i < length; i++) {
        printf("%c", get(i)->c);
    }
    printf(" (Falsche Buchstaben: %d) - ", wrongs);
    return 0;
}

int play(char* randomWord) {
    int length, guessed, wrong, i, temp_guess;
    char guess;
    guessed = wrong = 0;

    for (length = 0; randomWord[length]; length++) {
        set(length, '_');
    }
    output(length, wrong);
    do {
        temp_guess = guessed;
        guess = input();
        for (i = 0; i < length; i++) {
            if (tolower(randomWord[i]) == tolower(guess) && tolower(get(i)->c) != tolower(guess)) {
                set(i, randomWord[i]);
                guessed++;
            }
        }
        if (temp_guess == guessed) wrong++;
        output(length, wrong);
    } while (guessed != length);
    printf("Herzlichen Glueckwunsch! Fehlerhafte Buchstaben: %d", wrong);



    return 0;
}

int main(void) {
    char* randomWord;
    randomWord = getRandomWord();
    play(randomWord);

    return 0;
}



