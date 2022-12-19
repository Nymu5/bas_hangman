/*
 * Created by Niko Klemm
 * Created 2022-12-01
 * Version 1.0
 * Modified 2022-12-01
 */
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "database.h"

int length = 0;

Item *dll_start = NULL;
Item *dll_end = NULL;
Item *dll_current = NULL;
Item *dll_temp = NULL;

void error(char* message, int code) {
    printf("Error %d: %s\n", code, message);
    return;
}

int add(char c) {
    if (!(dll_current = (Item *) malloc(sizeof(Item)))) { /* checks if dll_current is empty */
        error("creation failed", -2);
        return -2;
    }

    dll_current->next = NULL; /* define new element - no next since adding adding at the end */
    dll_current->prev = dll_end; /* define new element - old last is new previous */
    dll_current->c = c;

    if (dll_start == NULL) { /* if database is empty */
        dll_start = dll_current; /* new item is first item of database */
    } else { /* if database not empty */
        dll_end->next = dll_current; /* old last linked to new last */
    }
    dll_end = dll_current; /* setting end to new item */

    length++;
    return 0;
}

Item* last(void) {
    return dll_end; /* return address of last item */
}

Item* first(void) {
    return dll_start; /* return address of first item */
}

Item* get(int index) {
    int i;
    /* check if requested index is out of bounds */
    if (!(index < length)) {
        error("Index out of bounds", -3);
        return NULL;
    }
    /* count entries from the beginning */
    dll_current = dll_start;
    for (i = 0; i < index; i++) {
         dll_current = dll_current->next;
    }
    /* return address of struct with given index */
    return dll_current;
}

int set(int index, char c) {
    int i;
    /* add items until index is reached and fill with 0s */
    while (!(index < length)) {
        add('0');
    }
    dll_current = dll_start;
    /* count entries from the beginning */
    for (i = 0; i < index; i++) {
        dll_current = dll_current->next;
    }
    /* insert given character at given index */
    dll_current->c = c;
    return 0;
}

int insert(int index, char c) {
    int i;
    /* check if requested index is out of bounds */
    if (!(index < length)) {
        error("Index out of bounds", -3);
        return NULL;
    }
    /* count entries from the beginning */
    dll_temp = dll_start;
    for (i = 0; i < index; i++) {
        dll_temp = dll_temp->next;
    }
    /* create new structure to add */
    dll_current = NULL;
    if (!(dll_current = (Item *) malloc(sizeof(Item)))) { /* checks if dll_current is empty */
        error("creation failed", -2);
        return -2;
    }
    /* reorganize pointers to add new struct at given index */
    dll_temp->prev->next = dll_current;
    dll_temp->prev = dll_current;
    dll_current->prev = dll_temp->prev;
    dll_current->next = dll_temp;
    dll_current->c = c;
    length++;
    dll_temp = NULL;

    return 0;
}

int rem(int index) {
    /* check if requested index is out of bounds */
    if (!(index < length)) {
        error("Index out of bounds", -3);
        return -1;
    }
    /* if first item -> set new start address */
    if (index == 0) {
        dll_start = dll_start->next;
        length--;
        return 0;
    }
    /* get item at index */
    dll_current = get(index);
    /* if index last item -> overwrite last element address */
    if (index == length-1) {
        dll_end = dll_current->prev;
        dll_current->prev->next = NULL;
        length--;
        return 0;
    }
    /* reorganize pointers to skip removed element */
    dll_current->prev->next = dll_current->next;
    dll_current->next->prev = dll_current->prev;
    length--;
    return 0;
}

