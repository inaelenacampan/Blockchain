#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

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

    long res;

    if ( m % 2 == 0){
        res = modpow(a, m/2, n);
        return (res * res) % n;
    }else{
        res = modpow(a, (m-1)/2, n);
        return (a * res * res) % n ;
    }
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
    srand(time(NULL));
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

long power(long a, long b){

    if(b==0) return 1;

    return a * power(a, b-1);
}

long random_prime_number(int low_size, int up_size, int k){

    /*
        plus petit nombre avec low_size bits
    */

    long low_number = power(2, low_size);

    /*
        plus grand nombre avec up_size bits
    */

    long up_number = power(2, up_size + 1) - 1;

    long a;

    do{
        a = rand_long(low_number, up_number);
    } while(is_prime_miller(a, k)==0);

    return a;
}

 /*
    Exercice 2 : Implémentation du protocole RSA
*/

long extended_gcd ( long s, long t, long *u, long *v){

    /*
        version récursive de l'algorithme d'euclide
    */
    if (t == 0){
        *u = 1;
        *v = 0;
        return s;
    }

    long uPrim , vPrim ;
    long gcd = extended_gcd (t, s%t, &uPrim , &vPrim );
    *u = vPrim;
    *v = uPrim - (s/t)* vPrim ;

    return gcd;
}

/*
    Question 2.1
*/

void generate_key_values(long p, long q, long* n, long *s, long *u){

    long t = (p-1) * (q-1);

    do{
        *s = rand_long(1,t);
    }while (extended_gcd(*s, t, u, n) != 1);

    *n = p * q ;
}

/*
    Question 2.2
*/

long* encrypt(char* chaine, long s, long n){

    int taille = strlen(chaine);
    long * tab = (long *) malloc(sizeof(long) * taille);

    for(int i = 0; i < taille; i++){
        long number = chaine[i];
        tab[i] = modpow(number, s, n);
    }
    return tab;
}

/*
    Question 2.3
*/

char* decrypt(long* crypted, int size, long u, long n){

    char * chaine = (char*) malloc(sizeof(char) * (size + 1));

    for(int i = 0; i < size; i++){
        chaine[i] = (char) modpow(crypted[i], u, n);
    }

    chaine[size] = '\0';
    return chaine;
}