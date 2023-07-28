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

/*
    Exercice 5 : Lecture et stockage des données dans des listes chainées
*/

/*
    Question 5.1
*/

CellKey* create_cell_key(Key* key);

#endif