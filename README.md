# Blockchain

> Projet LU2IN006 (année 2021-2022) : Blockchain appliquée à un processus éléctoral
>
> Auteur : Ina Campan (projet hors-cursus)

## I. Structure du code

### Partie 1 : Implémentation d'outils de Cryptographie

Dossier _`Cryptographie`_ contenant :

+ `crypto.c` et `crypto.h` (fichiers qui definissent les fonctions de la bibliothéque)
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

    /*
        Exercice 2 : Implémentation du protocole RSA
    */

    long extended_gcd ( long s, long t, long *u, long *v);
    void generate_key_values(long p, long q, long* n, long *s, long *u);
    long* encrypt(char* chaine, long s, long n);
    char* decrypt(long* crypted, int size, long u, long n);
```

### Partie 2 : Déclarations sécurisées

Dossier _`DeclarationsSecurisees`_ contenant :

+ `declsec.c` et `declsec.h` (fichiers qui definissent les fonctions de la bibliothéques)
+ `mainDeclsec.c` (fichier de tests)

```c
    /*
        Exercice 3 : Manipulations de structures sécurisées
    */

    void init_key(Key* key, long val, long n);
    void init_pair_keys(Key* pKey, Key* sKey, long low_size, long up_size);
    char* key_to_str(Key* key);
    Key* str_to_key(char* str);

    Signature* init_signature(long* content, int size);
    Signature* sign(char* mess, Key* sKey);
    char * signature_to_str (Signature * sgn);
    Signature * str_to_signature (char * str);

    Protected* init_protected(Key* pKey, char* mess, Signature* sgn);
    int verify(Protected* pr);
    char * protected_to_str(Protected* pr);
    Protected * str_to_protected(char * str);

    /*
        Exercice 4 : Création de données pour simuler le processus de vote
    */
    
    void generate_random_data(int nv, int nc);
```

### Partie 3 : Base de déclarations centralisée

Dossier _`BaseDeDonnees`_ contenant :

+ `list.c` et `list.h` (fichiers qui definissent les fonctions pour manipuler des listes simplement chainées)

```c
    /*
        Exercice 5 : Lecture et stockage des données dans des listes chainées
    */

    CellKey* create_cell_key(Key* key);
    void add_key(CellKey** list, Key* key);
    CellKey* read_public_keys(char * file_name);
    void print_list_keys(CellKey* LCK);
    void delete_cell_key(CellKey* c);
    void delete_list_keys(CellKey* LCK);

    CellProtected* create_cell_protected(Protected* pr);
    void add_protected(CellProtected** list, Protected* pr);
    CellProtected* read_protected(char * file);
    void print_list_protected(CellProtected* LCP);
    void delete_cell_protected(CellProtected* c);
    void delete_list_protected(CellProtected* LCP);

    void delete_invalid_protected(CellProtected ** list);
```

+ `hashTable.c` et `hashTable.h` (fichiers qui definissent les fonctions pour manipuler une table de hachage)

```c
    /*
        Exercice 6 : Détermination du gagnant de l'élection
    */

    HashCell* create_hashcell(Key* key);
    int hash_function(Key* key, int size);
    int find_position(HashTable* t, Key* key);
    HashTable* create_hashtable(CellKey* keys, int size);
```