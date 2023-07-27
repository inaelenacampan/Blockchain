#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>

#include "declsec.h"

void print_long_vector ( long *result , int size ){
    printf ("[ ");

    for (int i=0; i< size ; i++){
        printf ("%lx ", result [i]);
    }
    printf (" ] \n");
}

int main(){
    
    srand(time(NULL));

    //Testing Init Keys
    Key* pKey = malloc(sizeof(Key));
    Key* sKey = malloc(sizeof(Key));
    init_pair_keys(pKey, sKey, 3, 7);
    
    printf("pKey : %lx , %lx \n", pKey->v, pKey->n);
    printf("sKey : %lx , %lx \n", sKey->v, sKey->n);

    //Testing Key Serialization

    char * chaine = key_to_str(pKey);
    printf ("key_to_str : %s \n", chaine);
    
    Key* k = str_to_key(chaine);
    printf("str_to_key : %lx , %lx \n", k->v, k->n);
    
    //Testing signature

    //Candidate keys:
    
    Key* pKeyC = malloc(sizeof(Key));
    Key* sKeyC = malloc(sizeof(Key));
    init_pair_keys(pKeyC, sKeyC, 3, 7);
    
    //Declaration:
    char * mess = key_to_str(pKeyC);
    printf("%s vote pour %s \n", chaine, mess);
    
    Signature * sgn = sign(mess, sKey);
    printf("signature : ");
    print_long_vector(sgn->content, sgn->size);

    char * chaine2 = signature_to_str(sgn);
    printf("signature to str : %s \n", chaine2);

    Signature * sgn2 = str_to_signature(chaine2);
    printf ("str to signature : ");
    print_long_vector(sgn2->content, sgn2->size);

    //Testing protected:
    Protected * pr = init_protected(pKey, mess, sgn);
    
    //Verification:
    if (verify(pr)){
        printf("Signature valide \n");
    } else {
        printf("Signature non valide \n");
    }

    char * chaine3 = protected_to_str(pr);
    printf ("protected to str : %s \n", chaine3);
    
    Protected * pr2 = str_to_protected(chaine3);

    char * s1 = key_to_str(pr2 -> pKey);
    char * s2 = signature_to_str(pr2->sgn);
    printf("str to protected : %s %s %s \n", s1, pr2->mess, s2);

    free(s1);
    free(s2);

    free(sKey);

    free(pKeyC);
    free(sKeyC);
    free(k);

    free_signature(sgn2);
    free_protected(pr);
    free_protected(pr2);

    free(chaine);
    free(chaine2);
    free(chaine3);
    free(mess);

    generate_random_data(3000, 5);

    return 0;
}