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

    srand (time(NULL));

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