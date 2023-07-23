#ifndef CRYPTO_H
#define CRYPTO_H

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/*
    Exercice 1 : Résolution du problème de primalité
*/

/*
    Question 1.1 : p est un entier impair
    Complexite de la fonction : en O(p)
*/

int is_prime_naive(long p);

/*
    Question 1.3
    Complexite de la fonction : en O(m)
*/

long modpow_naive(long a, long m, long n);

/*
    Question 1.4 : version recursive
    Complexite de la fonction : O(log2(m))
*/

long modpow(long a, long m, long n);

/*
    Question 1.6
    TEST DE MILLER-RABIN
*/

int witness(long a, long b, long d, long p);
long rand_long(long low, long up);
int is_prime_miller(long p, int k);

/*
    Question 1.8
*/

long random_prime_number(int low_size, int up_size, int k);

#endif