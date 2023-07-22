# Blockchain

> Projet LU2IN006 (année 2021-2022) : Blockchain appliquée à un processus éléctoral
>
> Auteur : Ina Campan (projet hors-cursus)

## I. Structure du code

### Partie 1 : Implémentation d'outils de Cryptographie

Dossier _`Cryptographie`_ contenant :

+ `crypto.c` et `crypto.h` (fichiers qui definissent les fonctions de la bibliothéques)
+ `mainCrypto.c` (fichier de tests)
+ fonctions manipulées :

```c
    int is_prime_naive(long p);
    long modpow_naive(long a, long m, long n);
    long modpow(long a, long m, long n);
```