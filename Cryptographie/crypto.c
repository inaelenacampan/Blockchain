#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "crypto.h"

/*
    Exercice 1 : Résolution du problème de primalité
*/

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
    Question 1.6
    TEST DE MILLER-RABIN
*/

int witness(long a, long b, long d, long p){

    long x = modpow (a,d,p);
    if(x == 1){
        return 0;
    }
    for( long i = 0; i< b; i++){
        if(x == p -1){
            return 0;
        }
        x = modpow (x ,2,p);
    }
    return 1;
}

long rand_long(long low, long up){
    return rand () % (up - low + 1)+ low;
}

int is_prime_miller(long p, int k){
    if (p == 2) {
        return 1;
    }

    if (!( p & 1) || p <= 1) { //on verifie que p est impair et different de 1
        return 0;
    }

    //on determine b et d :
    long b = 0;
    long d = p - 1;

    while (!( d & 1)){ //tant que d n’est pas impair
        d = d/2;
        b=b+1;
    }

    // On genere k valeurs pour a, et on teste si c’est un temoin :
    long a;
    int i;

    for(i = 0; i < k; i++){

        a = rand_long (2, p -1);
        if( witness (a,b,d,p)){
            return 0;
        }
    }

    return 1;
}

/*
    Question 1.8
*/

long random_prime_number(int low_size, int up_size, int k){
    return 0;
}