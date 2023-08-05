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

/*
    Question 5.5
*/

void delete_cell_key(CellKey* c){
    free(c->data);
    free(c);
}

void delete_list_keys(CellKey* LCK){

    CellKey * tmp = LCK;

    while(tmp != NULL){
        tmp = LCK;
        LCK = LCK->next;

        delete_cell_key(tmp);

        tmp = LCK;
    }
}

/*
    Question 5.6
*/

CellProtected* create_cell_protected(Protected* pr){
    CellProtected * new = (CellProtected*) malloc(sizeof(CellProtected));
    new->data = pr;
    new->next = NULL;
    return new;
}

/*
    Question 5.7
*/

void add_protected(CellProtected** list, Protected* pr){
    CellProtected * new = create_cell_protected(pr);
    new->next = *list;

    *list = new;
}

/*
    Question 5.8
*/

CellProtected* read_protected(char * file_name){

    FILE * file = fopen(file_name, "r");

    CellProtected * list = NULL;
    
    char buffer[256];

    while(fgets(buffer, 256, file)){

        Protected * pr = str_to_protected(buffer);
        add_protected(&list, pr);

    }

    fclose(file);

    return list;
}

/*
    Question 5.9
*/

void print_list_protected(CellProtected* LCP){
    CellProtected * copy = LCP;
    
    while(copy){
        char * chaine = protected_to_str(copy->data);
        printf("%s\n", chaine);

        free(chaine);
        copy = copy->next;
    }
}

/*
    Question 5.10
*/

void delete_cell_protected(CellProtected* c){
    free_protected(c->data);
    free(c);
}

void delete_list_protected(CellProtected* LCP){
    CellProtected * tmp = LCP;

    while(tmp != NULL){
        tmp = LCP;
        LCP = LCP->next;

        delete_cell_protected(tmp);

        tmp = LCP;
    }
}
