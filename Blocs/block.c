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
#include "block.h"

/*
    Exercice 7 : Structure d'un block et persistance
*/

/*
    Question 7.1
*/

void block_to_file(char * file_name, Block * b){

    FILE * file = fopen(file_name, "w");

    char * key_str = key_to_str(b->key);
    fprintf(file, "%s\n", key_str);
    free(key_str);

    fprintf(file, "%s\n", b->hash);
    fprintf(file, "%s\n", b->previous_hash);
    fprintf(file, "%d\n", b->nonce);

    CellProtected * copy = b->votes;

    while(copy){
        char * chaine = protected_to_str(copy->data);
        printf("%s\n", chaine);

        free(chaine);
        copy = copy->next;
    }

    fclose(file);
}

/*
    Question 7.2
*/

Block * file_to_block(char * file_name){
    Block * b = (Block*) malloc(sizeof(Block));
    FILE * file = fopen(file_name, "r");

    fclose(file);
    return b;
}