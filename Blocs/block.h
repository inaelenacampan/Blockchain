#ifndef BLOCK_H
#define BLOCK_H

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "../Cryptographie/crypto.h"
#include "../DeclarationsSecurisees/declsec.h"
#include "../BaseDeDonnees/list.h"
#include "../BaseDeDonnees/hashTable.h"

/*
    Exercice 7 : Structure d'un block et persistance
*/

typedef struct block {
    Key* author ; // la clé publique de son créateur
    CellProtected* votes ; // une liste de déclarations de vote
    unsigned char* hash ; // la valeur hachée du bloc
    unsigned char* previous_hash ; // la valeur hachée du bloc précédent
    int nonce ; // une preuve de travail
} Block ;

/*
    Question 7.1
*/

void block_to_file(char * file_name, Block * b);

/*
    Question 7.2
*/

Block * file_to_block(char * file_name);

#endif