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
