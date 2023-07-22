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

#endif