#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>

#include "crypto.h"

int main(){

    /*
        Question 1.1
    */

    assert(is_prime_naive(-45)==0);
    assert(is_prime_naive(0)==0);
    assert(is_prime_naive(1)==0);
    assert(is_prime_naive(2)==1);
    assert(is_prime_naive(199)==1);
    assert(is_prime_naive(100453)==0);

    /*
        Question 1.2 : tests sur le plus grand nombre premier
        2 millièmes de seconde = 0.002 secondes
    */

    int nb;
    int val_bool = 0;

    for( nb = 3 ; nb < 100000000000 && val_bool == 0; nb = nb + 2 ){
        
        clock_t begin = clock();
        int res = is_prime_naive(nb);
        clock_t end = clock();

        double time = (double)(end - begin) / CLOCKS_PER_SEC;

        if(res == 1 && time > 0.002){
            val_bool = 1;
            printf("Le plus grand nombre premier trouve vaut : %d\n", nb);
        }
    }
    
    return 0;
}