#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

#include "declsec.h"
#include "../Cryptographie/crypto.h"

/*
    Exercice 3 : Manipulations de structures sécurisées
*/

/*
    Question 3.2
*/

void init_key(Key* key, long val, long n){
    key->v = val;
    key->n = n;
}

/*
    Question 3.3
*/

void init_pair_keys(Key* pKey, Key* sKey, long low_size, long up_size){

    long p = random_prime_number (low_size, up_size, K) ;
    long q = random_prime_number (low_size , up_size, K) ;

    while (p==q){
        q = random_prime_number (low_size, up_size, K) ;
    }

    long n, s, u;
    generate_key_values(p,q ,&n ,&s ,&u);

    //Pour avoir des cles positives :
    if (u <0){
        long t =(p-1) *(q-1);
        u = u + t; //on aura toujours s*u mod t = 1
    }

    init_key(pKey, s, n);
    init_key(sKey, u, n);
}

/*
    Question 3.4
*/

char* key_to_str(Key* key){
    char * chaine = (char *) malloc(sizeof(char) * SIZE_MAX);
    sprintf(chaine, "(%lx,%lx)",key->v, key->n);
    return chaine;
}

Key* str_to_key(char* str){

    Key * res = (Key*)malloc(sizeof(Key));
    if(sscanf(str, "(%lx,%lx)", &(res->v), &(res->n))!=2){
        printf(" !! format incorrect de la chaine de caractere !! \n");
        exit(EXIT_FAILURE);
    }

    return res;
}

/*
    Question 3.6
*/

Signature* init_signature(long* content, int size){
    Signature * sgn = (Signature*) malloc(sizeof(Signature));
    sgn->content = content;
    sgn->size = size;
    return sgn;
}

/*
    Question 3.7
*/

Signature* sign(char* mess, Key* sKey){
    long * tab = encrypt(mess, sKey->v, sKey->n);
    int size = strlen(mess);

    return init_signature(tab, size);
}

/*
    Question 3.8
*/

char * signature_to_str (Signature * sgn){

    char * result = (char*)malloc(10*sgn->size* sizeof(char));

    result [0]= '#';
    int pos = 1;
    char buffer[SIZE_MAX];

    for (int i=0; i<sgn->size ; i++){
        sprintf(buffer , "%lx", sgn->content[i]);
        
        for (int j=0; j< strlen(buffer); j++){
            result [pos] = buffer[j];
            pos = pos +1;
        }
        result[pos] = '#' ;
        pos = pos+1;
    }

    result[pos] = '\0';
    result = realloc(result,(pos +1)*sizeof(char));

    return result ;
}

Signature * str_to_signature (char * str){
    
    int len = strlen(str);
    long * content = (long *) malloc (sizeof (long)*len);
    
    int num = 0;
    char buffer[SIZE_MAX];

    int pos = 0;
    
    for (int i=0; i<len; i++){
        if (str[i] != '#'){
            buffer[pos] = str[i];
            pos =pos +1;
        } else {
            if (pos != 0){
                buffer[pos] = '\0' ;
                sscanf (buffer, "%lx", &(content[num]));
                num = num + 1;
                pos = 0;
            }
        }
    }
    
    content = realloc(content, num * sizeof(long));
    return init_signature(content, num);
}

/*
    Question 3.10
*/

Protected* init_protected(Key* pKey, char* mess, Signature* sgn){
    Protected * protcd = (Protected *) malloc(sizeof(Protected));

    protcd->pKey = pKey;
    protcd->mess = strdup(mess);
    protcd->sgn = sgn;

    return protcd;
}

/*
    Question 3.11
*/

int verify(Protected* pr){

    char * chaine = decrypt((pr->sgn)->content, (pr->sgn)->size, (pr->pKey)->v, (pr->pKey)->n);
    int res = strcmp(chaine, pr->mess);
    
    free(chaine);
    return (res == 0);
}

/*
    Question 3.12
*/

char * protected_to_str(Protected* pr){

    char * key_str = key_to_str(pr->pKey);
    char * sgn_str = signature_to_str(pr->sgn);

    char * str = malloc(sizeof(char) * (strlen(pr->mess) + strlen(key_str) + strlen(sgn_str) + 3));
    sprintf(str, "%s %s %s", key_str, pr->mess, sgn_str);

    free(key_str);
    free(sgn_str);

    return str;
}

Protected * str_to_protected(char * str){

    char cle[SIZE_MAX];
    int cpt = 0;

    while(str[cpt]!=' '){
        cle[cpt] = str[cpt];
        cpt++;
    }

    cle[cpt] = '\0';

    Key * pKey = str_to_key(cle);

    int i = 0;
    char mess[SIZE_MAX];

    while(str[cpt+i+1]!=' '){
        mess[i] = str[cpt + i+1];
        i++;
    }

    mess[i] = '\0';

    int k = 0;
    char sgn[SIZE_MAX];
    while(str[cpt + i + k+2]!='\0'){
        sgn[k] = str[cpt + i + k+2];
        k++;
    }

    sgn[k] = '\0';

    Signature * s = str_to_signature(sgn);

    return init_protected(pKey, mess, s);
}

void free_signature(Signature * sgn){
    free(sgn->content);
    free(sgn);
}

void free_protected(Protected * pr){
    if(pr->pKey !=NULL){
        free(pr->pKey);
    }
    if(pr->mess !=NULL){
        free(pr->mess);
    }
    if(pr->sgn!=NULL){
        free_signature(pr->sgn);
    }
    free(pr);
}

/*
    Exercice 4 : Création de données pour simuler le processus de vote
*/

void generate_random_data(int nv, int nc){

    /*
        nv = nombre citoyens
        nc = nombre candidats

        Résultats : 
            - keys.txt contenant tous ces couples de clés
            - candidates.txt contenant la clé publique de tous les candidats (choisis parmi les votants)
            - declarations.txt contenant toutes les déclarations signées
    */

    /*Les trois fichiers à remplir*/

    FILE *keys = NULL;
    keys = fopen("../Data/keys.txt","w");

    FILE *candidats = NULL;
    candidats = fopen("../Data/candidats.txt","w");

    FILE *declarations = NULL;
    declarations = fopen("../Data/declarations.txt","w");

    if (((nv <= 0) || (nc <= 0)) || (nv < nc)){
        exit(EXIT_FAILURE);
    }

    Couple_keys * arrayKeys = (Couple_keys *) malloc(sizeof(Couple_keys) * nv);
    int i;

    for(i = 0; i < nv ; i++){

        //initialisation des couples dans le tableau des clés

        (arrayKeys[i]).pKey = malloc(sizeof(Key));
        (arrayKeys[i]).sKey = malloc(sizeof(Key));
        (arrayKeys[i]).statut = 0;

        init_pair_keys((arrayKeys[i]).pKey, (arrayKeys[i]).sKey, 3, 7);

        char * pKey_str = key_to_str((arrayKeys[i]).pKey);
        char * sKey_str = key_to_str((arrayKeys[i]).sKey);

        fprintf(keys, "%s %s\n", pKey_str, sKey_str);

        free(pKey_str);
        free(sKey_str);
    }

    // selection des candidats

    int index;

    // tableau des index des candidats dans le tableau des keys
    int * index_candidats = (int *) malloc(sizeof(int) * nc);

    i = 0;

    while(i < nc){

        index = rand() % nv;

        if((arrayKeys[index]).statut == 0){

            // changement du statut

            (arrayKeys[index]).statut == 1;

            char * pKey_c = key_to_str((arrayKeys[index]).pKey);
            fprintf(candidats, "%s\n", pKey_c);
            free(pKey_c);

            index_candidats[i] = index;
            i++;
        }
    }

    int choix;

    for(i = 0; i < nv; i++){

        choix = rand() % nc;

        char * mess = key_to_str(arrayKeys[
            (index_candidats[choix])].pKey);

        Signature * sgn = sign(mess, arrayKeys[i].sKey);

        Protected * pr = init_protected(arrayKeys[i].pKey, mess, sgn);

        char * pr_str = protected_to_str(pr);
        fprintf(declarations, "%s\n", pr_str);
        free(pr_str);

        free(mess);
        free_signature(sgn);

        // la cle publique de protected est free a la fin
        free(pr->mess);
        free(pr);
    }

    for(i = 0; i < nv; i++){
        free(arrayKeys[i].pKey);
        free(arrayKeys[i].sKey);
    }

    free(index_candidats);
    free(arrayKeys);

    fclose(keys);
    fclose(candidats);
    fclose(declarations);
}