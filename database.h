/*
 * Created by Niko Klemm
 * Created 2022-12-01
 * Version 1.0
 * Modified 2022-12-01
 */

#ifndef MINIDATABASE_DATABASE_H
#define MINIDATABASE_DATABASE_H

typedef struct M_Item {
    struct M_Item *prev;
    struct M_Item *next;
    char c;
} Item;

void error(char *, int);

int add(char);

struct M_Item *last(void);

struct M_Item *first(void);

struct M_Item *get(int);

int set(int, char);

int rem(int);

#endif /* MINIDATABASE_DATABASE_H */
