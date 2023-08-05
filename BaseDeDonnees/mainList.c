#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

#include "list.h"
#include "hashTable.h"
#include "../DeclarationsSecurisees/declsec.h"

int main(){

    CellKey * listC = read_public_keys("../Data/candidats.txt");
    printf("--------- CANDIDATS ---------\n");
    print_list_keys(listC);

    CellKey * listV = read_public_keys("../Data/keys.txt");
    printf("--------- VOTANTS ---------\n");
    print_list_keys(listV);

    CellProtected* listP = read_protected("../Data/declarations.txt");
    printf("--------- DECLARATIONS ---------\n");
    print_list_protected(listP);

    delete_invalid_protected(&listP);

    Key * winner = compute_winner(listP, listC, listV, 15, 9000);
    char * winner_str = key_to_str(winner);

    printf("\nGAGNANT : %s\n", winner_str);

    free(winner_str);
    free(winner);

    delete_list_keys(listC);
    delete_list_keys(listV);
    delete_list_protected(listP);
    
    return 0;
}