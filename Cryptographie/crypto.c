#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "crypto.h"

/*
    Question 1.1 : p est un entier impair
    Valeurs de retour :
        - 1 si p est premier
        - 0 sinon
*/

int is_prime_naive(long p){

    if (p<=1) return 0;

    int i;

    for(i = 3; i < p ; i++){
        if(p%i == 0) return 0;
    }

    return 1;
}

/*
    Question 1.3
*/

long modpow_naive(long a, long m, long n){

    long res = a;
    int i;

    for( i = 0; i < m; i++){
        res = (res * a) % n;
    }

    return res;
}

/*
    Question 1.4
*/

long modpow(long a, long m, long n){

    /*cas de base*/

    if( m == 0 ) return 1;

    long res = modpow(a, m/2, n);

    if ( m % 2 == 0){
        return (res * res) % n;
    }

    return (a * res * res) % n ;
}

/*
    TEST DE MILLER-RABIN
*/