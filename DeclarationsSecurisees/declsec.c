#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

#include "declsec.h"
#include "../Cryptographie/crypto.h"

/*
    Exercice 3 : Manipulations de structures sécurisées
*/

/*
    Question 3.2
*/

void init_key(Key* key, long val, long n){
    key->v = val;
    key->n = n;
}

/*
    Question 3.3
*/

void init_pair_keys(Key* pKey, Key* sKey, long low_size, long up_size){

    srand (time(NULL));

    long p = random_prime_number (low_size, up_size, K) ;
    long q = random_prime_number (low_size , up_size, K) ;

    while (p==q){
        q = random_prime_number (low_size, up_size, K) ;
    }

    long n, s, u;
    generate_key_values(p,q ,&n ,&s ,&u);

    //Pour avoir des cles positives :
    if (u <0){
        long t = (p -1) *(q -1);
        u = u + t; //on aura toujours s*u mod t = 1
    }

    init_key(pKey, s, n);
    init_key(sKey, u, n);
}

/*
    Question 3.4
*/

char* key_to_str(Key* key){
    char * chaine = (char *) malloc(sizeof(char) * SIZE_MAX);
    sprintf(chaine, "(%lx,%lx)",key->v, key->n);
    return chaine;
}

Key* str_to_key(char* str){

    Key * res = (Key*)malloc(sizeof(Key));
    if(sscanf(str, "(%lx,%lx)", &(res->v), &(res->n))!=2){
        printf(" !! format incorrect de la chaine de caractere !! \n");
        exit(EXIT_FAILURE);
    }

    return res;
}

/*
    Question 3.6
*/

Signature* init_signature(long* content, int size){
    Signature * sgn = (Signature*) malloc(sizeof(Signature));
    sgn->content = content;
    sgn->size = size;
    return sgn;
}