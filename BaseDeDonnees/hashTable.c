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
        else if((tab[index % n]->key)->v == key->v && (tab[index % n]->key)->n == key->n){
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

    HashTable * new = (HashTable*) malloc(sizeof(HashTable));
    new->size = size;
    new->tab = (HashCell **) malloc(sizeof(HashCell*) * size);

    for (int i = 0; i < size; i++) {
        (new->tab)[i] = NULL;
    }

    CellKey * head = keys;

    int index;

    while(head){

        index = find_position(new, head->data);
        (new->tab)[index] = create_hashcell(head->data);

        head = head->next;
    }

    return new;
}

/*
    Question 6.6
*/

void delete_hashCell(HashCell* c){
    free(c->key);
    free(c);
}

void delete_hashtable(HashTable* t){

    for(int i = 0; i < t->size; i++){
        if(t->tab[i] != NULL){
            delete_hashCell(t->tab[i]);
        }
    }

    free(t->tab);
    free(t);
}

/*
    Question 6.7
*/

Key* compute_winner(CellProtected* decl, CellKey* candidates, CellKey* voters, int sizeC, int sizeV){

    HashTable * hC = create_hashtable(candidates, sizeC);
    HashTable * hV = create_hashtable(voters, sizeV);


    return NULL;
}