#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "../Cryptographie/crypto.h"
#include "../DeclarationsSecurisees/declsec.h"
#include "list.h"

/*
    Exercice 6 : Détermination du gagnant de l'élection
*/

typedef struct hashcell {
    Key* key;
    int val;
} HashCell ;

typedef struct hashtable {
    HashCell ** tab;
    int size ;
} HashTable ;

/*
    Question 6.2
*/

HashCell* create_hashcell(Key* key);

/*
    Question 6.3
*/

int hash_function(Key* key, int size);

/*
    Question 6.4
*/

int find_position(HashTable* t, Key* key);

/*
    Question 6.5
*/

HashTable* create_hashtable(CellKey* keys, int size);

/*
    Question 6.6
*/

void delete_hashtable(HashTable* t);

/*
    Question 6.7
*/

Key* compute_winner(CellProtected* decl, CellKey* candidates, CellKey* voters, int sizeC, int sizeV);

#endif