#ifndef DECLSEC_H
#define DECLSEC_H

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "../Cryptographie/crypto.h"

#define K 5000
#define SIZE_MAX 256
#define SIZE_TAB 256

/*
    Exercice 3 : Manipulations de structures sécurisées
*/

/*
    Question 3.1
*/

typedef struct key{
    long v;
    long n;
} Key;

/*
    Question 3.5
*/

typedef struct signature{
    long * content;
    int size;
} Signature;

/*
    Question 3.9
*/

typedef struct protected{
    Key * pKey; // clé publique de l'émetteur
    char * mess; // message
    Signature * sgn ; // signature associée
} Protected;

/*
    Question 3.2
*/

void init_key(Key* key, long val, long n);

/*
    Question 3.3
*/

void init_pair_keys(Key* pKey, Key* sKey, long low_size, long up_size);

/*
    Question 3.4
*/

char* key_to_str(Key* key);
Key* str_to_key(char* str);

/*
    Question 3.6
*/

Signature* init_signature(long* content, int size);

/*
    Question 3.7
*/

Signature* sign(char* mess, Key* sKey);

/*
    Question 3.8
*/

char * signature_to_str (Signature * sgn);
Signature * str_to_signature (char * str);

/*
    Question 3.10
*/

Protected* init_protected(Key* pKey, char* mess, Signature* sgn);

#endif