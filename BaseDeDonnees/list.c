#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

#include "list.h"
#include "../Cryptographie/crypto.h"
#include "../DeclarationsSecurisees/declsec.h"

/*
    Exercice 5 : Lecture et stockage des données dans des listes chainées
*/

/*
    Question 5.1
*/

CellKey* create_cell_key(Key* key){
    CellKey * cell = (CellKey *) malloc(sizeof(CellKey));
    cell->data = key;
    cell->next = NULL;
    return cell;
}

/*
    Question 5.2
*/

void add_key(CellKey** list, Key* key){

    CellKey * new = create_cell_key(key);
    new->next = *list;

    *list = new;
}

/*
    Question 5.3
*/

CellKey* read_public_keys(char * file_name){

    FILE * file = fopen(file_name, "r");

    CellKey * list = NULL;
    
    char buffer[256];

    while(fgets(buffer, 256, file)){

        long val, n;
        sscanf(buffer, "(%lx,%lx)%*s", &val, &n);
        Key * key = malloc(sizeof(Key));

        init_key(key, val, n);
        add_key(&list, key);

    }

    fclose(file);

    return list;
}

/*
    Question 5.4
*/

void print_list_keys(CellKey* LCK){
    CellKey * copy = LCK;
    
    while(copy){
        char * chaine = key_to_str(copy->data);
        printf("%s\n", chaine);

        free(chaine);
        copy = copy->next;
    }
}