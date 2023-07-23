# Blockchain

> Projet LU2IN006 (année 2021-2022) : Blockchain appliquée à un processus éléctoral
>
> Auteur : Ina Campan (projet hors-cursus)

## I. Structure du code

### Partie 1 : Implémentation d'outils de Cryptographie

Dossier _`Cryptographie`_ contenant :

+ `crypto.c` et `crypto.h` (fichiers qui definissent les fonctions de la bibliothéques)
+ `mainCrypto.c` (fichier de tests)

```c
    
    /*
        Exercice 1 : Résolution du problème de primalité
    */

    int is_prime_naive(long p);
    long modpow_naive(long a, long m, long n);
    long modpow(long a, long m, long n);
```

+ Question 1.5 : [Performances des deux méthodes d'exponentiation modulaire](plot.png)

```c
    /*
        TEST DE MILLER-RABIN
        Question 1.7 : Probabilite d'erreur majoree par (1/4)**k
    */

    int witness(long a, long b, long d, long p);
    long rand_long(long low, long up);
    int is_prime_miller(long p, int k);
    long random_prime_number(int low_size, int up_size, int k);
```