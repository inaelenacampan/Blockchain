#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#include "hashTable.h"
#include "list.h"
#include "../Cryptographie/crypto.h"
#include "../DeclarationsSecurisees/declsec.h"

/*
    Exercice 6 : Détermination du gagnant de l'élection
*/

/*
    Question 6.2
*/

HashCell* create_hashcell(Key* key){
    HashCell * new = (HashCell *) malloc(sizeof(HashCell));
    new->key = key;
    new->val = 0;

    return new;
}

/*
    Question 6.3
*/

int hash_function(Key* key, int size){
    // méthode de multiplication
    long val = key->n;
    long a = sqrt(7.) - 2;
    return floor(size*((val*a)%1));
}

/*
    Question 6.4
*/

int find_position(HashTable* t, Key* key){

    HashCell ** tab = t->tab;
    int n = t->size;

    int index = hash_function(key, n);
    int i = 0;

    while(i < n){
        if(tab[index % n]->key == NULL){
            return index;
        }
        else if(tab[index % n]->key == key){
            return index;
        }
        i++;
        index ++;
    }
    return index;
}

/*
    Question 6.5
*/

HashTable* create_hashtable(CellKey* keys, int size){
    return NULL;
}