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



#endif