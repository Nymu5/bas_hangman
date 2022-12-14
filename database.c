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
    return dll_end;
}

Item* first(void) {
    return dll_start;
}

Item* get(int index) {
    int i;
    if (!(index < length)) {
        error("Index out of bounds", -3);
        return NULL;
    }
    dll_current = dll_start;
    for (i = 0; i < index; i++) {
         dll_current = dll_current->next;
    }
    return dll_current;
}

int set(int index, char c) {
    int i;
    while (!(index < length)) {
        add('0');
    }
    dll_current = dll_start;
    for (i = 0; i < index; i++) {
        dll_current = dll_current->next;
    }
    dll_current->c = c;
    return 0;
}

int rem(int index) {
    if (!(index < length)) {
        error("Index out of bounds", -3);
        return -1;
    }
    if (index == 0) {
        dll_start = dll_start->next;
        length--;
        return 0;
    }
    dll_current = get(index);
    if (index == length-1) {
        dll_end = dll_current->prev;
        dll_current->prev->next = NULL;
        length--;
        return 0;
    }
    dll_current->prev->next = dll_current->next;
    dll_current->next->prev = dll_current->prev;
    length--;
    return 0;
}

