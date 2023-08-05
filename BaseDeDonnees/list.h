#ifndef LIST_H
#define LIST_H

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "../Cryptographie/crypto.h"
#include "../DeclarationsSecurisees/declsec.h"

typedef struct cellKey {
    Key* data ;
    struct cellKey * next ;
} CellKey ;

typedef struct cellProtected {
    Protected * data ;
    struct cellProtected * next ;
} CellProtected ;

/*
    Exercice 5 : Lecture et stockage des données dans des listes chainées
*/

/*
    Question 5.1
*/

CellKey* create_cell_key(Key* key);

/*
    Question 5.2
*/

void add_key(CellKey** list, Key* key);

/*
    Question 5.3
*/

CellKey* read_public_keys(char * file_name);

/*
    Question 5.4
*/

void print_list_keys(CellKey* LCK);

/*
    Question 5.5
*/

void delete_cell_key(CellKey* c);
void delete_list_keys(CellKey* LCK);

/*
    Question 5.6
*/

CellProtected* create_cell_protected(Protected* pr);

/*
    Question 5.7
*/

void add_protected(CellProtected** list, Protected* pr);

/*
    Question 5.8
*/

CellProtected* read_protected(char * file);

/*
    Question 5.9
*/

void print_list_protected(CellProtected* LCP);

/*
    Question 5.10
*/

void delete_cell_protected(CellProtected* c);
void delete_list_protected(CellProtected* LCP);

/*
    Question 6.1
*/

void delete_invalid_protected(CellProtected ** list);

#endif