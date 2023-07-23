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

void print_long_vector ( long *result , int size ){
    printf ("Vector : [ ");

    for (int i=0; i< size ; i++){
        printf ("%lx ", result [i]);
    }
    printf (" ] \n");
}

int main(){

    srand(time(NULL));

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

        srand(time(NULL));

        clock_t begin = clock();
        int res = is_prime_naive(nb);
        clock_t end = clock();

        double temps = (double)(end - begin) / CLOCKS_PER_SEC;

        if(res == 1 && temps > 0.002){
            val_bool = 1;
            printf("Le plus grand nombre premier trouve vaut : %d\n", nb);
        }
    }
    /*
        Question 1.5
    */

    FILE *test_pow = NULL;
    test_pow = fopen("test_pow.txt","w");

    FILE * test_pow_naive = NULL;
    test_pow_naive = fopen("test_pow_naive.txt","w");
    
    int m;
    double temps;
    clock_t begin, end;

    fprintf(test_pow,"temps\tm\n");
    fprintf(test_pow_naive,"temps\tm\n");

    for( m = 5000; m < 10500 ; m = m + 503){

        srand(time(NULL));
        begin = clock();
        long res1 = modpow(27008900, m, 130920);
        end = clock();

        temps = (double)(end - begin);

        fprintf(test_pow,"%lf\t%lf\n",temps,(double)m);

        srand(time(NULL));
        begin = clock();
        long res2 = modpow_naive(27008900, m, 130920);
        end = clock();

        temps = (double)(end - begin);

        fprintf(test_pow_naive,"%lf\t%lf\n",temps,(double)m);
    }

    fclose(test_pow);
    fclose(test_pow_naive);

    /*
        FONCTION DE TESTS : RSA
    */
    srand (time(NULL));

    long p = random_prime_number (3,7, 5000) ;
    long q = random_prime_number (3,7, 5000) ;

    while (p==q){
        q = random_prime_number (3,7, 5000) ;
    }

    long n, s, u;
    generate_key_values(p,q ,&n ,&s ,&u);

    //Pour avoir des cles positives :
    if (u <0){
        long t = (p -1) *(q -1);
        u = u + t; //on aura toujours s*u mod t = 1
    }

    //Afichage des cles en hexadecimal
    printf ("cle publique = (%lx , %lx) \n", s, n);
    printf ("cle privee = (%lx , %lx) \n", u, n);

    //Chiffrement:
    // char mess [10] = "Hello";
    char mess [20] = "bonjour, madame!";
    int len = strlen(mess);

    long * crypted = encrypt (mess,s,n);

    printf ("Initial message : %s \n", mess );
    printf ("Encoded representation : \n");
    print_long_vector(crypted,len);

    //Dechiffrement
    char * decoded = decrypt(crypted, len, u, n);
    printf("Decoded : %s \n", decoded);

    free(crypted);
    free(decoded);

    return 0;
}