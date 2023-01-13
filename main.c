#include <stdio.h>
#include "Inteiros.h"
#include "str.h"
#include "linkedwallet.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define MAX_DIGITS 10




void print_matrix_ints(short** matrix, int lines, int columns) {
    for (int i = 0; i < lines; i++) {
        if (matrix[i] == NULL) {
            printf("(empty)\n");
        } else {
            for (int j = 0; j < columns; j++) {
                printf("[%d]", matrix[i][j]);
            }
            printf("\n");
        }
    }
}
// 2 maneiras de implementação do print diferentes
void print_matriz_chars(char **matrix) {
    printf("\n-------MATRIX------\n");
    for (int i = 0; *(matrix + i) != NULL; i++) { //i < nlines

        printf("[%d] = %s\n", i, *(matrix + i));
    }
    printf("\n-------MATRIX------\n");
}


int main() {
/*
    srand(time(0)); // new random number
    unsigned long long public_key = new_public_key_int();
    printf("Generated public key: %llu \n", public_key);

    unsigned long long private_key = calc_private_key_int(public_key); //Abordagem certa (+eficiente)
    printf("111Generated private key: %llu \n", private_key);



    unsigned long long runlength_key = calc_runlength_int(private_key);
    printf("Runlength : %llu \n", runlength_key);


    unsigned long long private_key_length = private_key_from_runlength_int(runlength_key);
    printf("Run-length encoding: %llu, Private key: %llu\n", runlength_key, private_key_length);


    int nlines = 4;
    int ncolumns = 3;
    short** matrix = alloc_matrix_int(nlines, ncolumns);
    //print_matrix_ints(matrix,4,4);

    unsigned long long key_mat1 = new_public_key_int();
    unsigned long long key_mat2 = new_public_key_int();
    store_key_int(matrix, 4, key_mat1);
    store_key_int(matrix, 4, key_mat2);
    print_matrix_ints(matrix, 4, 4);
*/

/*
    short** matrix = alloc_matrix_int(3, 3);
    store_key_int(matrix, 3, 187);
    store_key_int(matrix, 3, 145);
    store_key_int(matrix, 3, 896);

    int key_exists = exists_key_int(matrix, 3, 187);
    int key_does_not_exist = exists_key_int(matrix, 3, 502);
    printf("Key exists: %d\n", key_exists);
    printf("Key does not exist: %d\n", key_does_not_exist);
*/

/*
    // --------GET_PRIVATE_KEY_INT-------
    short** public_keys_matrix = alloc_matrix_int(3, 3);  // Allocate memory for the public keys matrix
    short** private_keys_matrix = alloc_matrix_int(3, 3);  // Allocate memory for the private keys matrix

    // Store a public key and its corresponding private key
    unsigned long long public_key = 122;  // Public key

    unsigned long long private_key = calc_private_key_int(public_key);  // Calculate the corresponding private key
    store_key_int(public_keys_matrix, 3, public_key);  // Store the public key in the public keys matrix
    store_key_int(private_keys_matrix, 3, private_key);
    // Store the private key in the private keys matrix
    // print_matrix_ints(public_keys_matrix,3,5);
    // print_matrix_ints(private_keys_matrix,3,5);
    // Get the private key corresponding to the given public key
    unsigned long long private_key_from_matrix = get_private_key_int(public_keys_matrix, private_keys_matrix, 3, public_key);
    printf("%llu \n", public_key);
    printf("Private key corresponding to public key %llu: %llu\n", public_key, private_key_from_matrix);
*/


/*// --------------KEY_LONG_2_DIGITS_INT

    unsigned long long public_key = new_public_key_int();
    printf("%llu\n", public_key);

    short* digits = key_long_2_digits_int(public_key);
    printf("Digits of the key %llu \n", public_key);
    for (int i = 0; i < 10 ; i++) {
        printf(" %hd",digits[i]);
    }
    printf("\n");
*/

    /* short** matrix_kpub = alloc_matrix_int(2,2);
     short** matrix_kpriv = alloc_matrix_int(2,2);
   //  short** matrix_kpriv = alloc_matrix_int(2,10);
     store_key_int(matrix_kpub,0,12);
     store_key_int(matrix_kpub,1,4444);
     store_key_int(matrix_kpriv,0,22);
     store_key_int(matrix_kpriv,1,543);

     //printf("%d\n",exists_key_int(matrix_kpub,1,123));
     //printf("%d\n",exists_key_int(matrix_kpriv,2,12));
     printf("%llu\n",get_private_key_int(matrix_kpub,matrix_kpriv,1,444));
 */


/* ------- SORT_MATRIX_INT

    // create a matrix with 5 lines and 5 columns
    short** matrix = (short**) malloc(5 * sizeof(short*));
    for (int i = 0; i < 5; i++) {
        matrix[i] = (short*) malloc(5 * sizeof(short));
    }

    // fill the matrix with random values
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            matrix[i][j] = rand() % 10;
        }
    }

    // print the original matrix
    printf("Original matrix:\n");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    // sort the matrix in ascending order
    sort_matrix_int(matrix, 5, 1);

    // print the sorted matrix
    printf("\nSorted matrix (ascending):\n");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
*/

/*
 //------File Handling



    short** matrix_kpub=alloc_matrix_int(2,3);
    short** matrix_kpriv=alloc_matrix_int(2,3);
    short** matrix_kcod=alloc_matrix_int(2,3);

    store_key_int(matrix_kpub,2,122);
    store_key_int(matrix_kpub,2,444);
    store_key_int(matrix_kpriv,2,144);
    store_key_int(matrix_kpriv,2,644);
    store_key_int(matrix_kcod,2,563);
    store_key_int(matrix_kcod,2,754);

  print_matrix_ints(matrix_kpub,2,3);
    printf("------\n");
    print_matrix_ints(matrix_kpriv,2,3);
    printf("------\n");
    print_matrix_ints(matrix_kcod,2,3);
    printf("------\n");
    char filename[] = "tesss.txt";
   save_txt_keys_int(matrix_kpub,matrix_kpriv,matrix_kcod,2,filename);
*/

// CHARS

// calc_private_key_char -->
/*    unsigned long long pubkey = 557;
    unsigned long long privkey = calc_private_key_char(pubkey);
    printf("Private key for pubkey %llu: %llu\n", pubkey, privkey);

    //calc_runlength_char && private_key_from_runlength_char

    printf("%llu\n",calc_runlength_char(privkey));
    printf("%llu\n",private_key_from_runlength_char(privkey));
*/

  // alloc_matrix_char && store_key_char
 /*  int nlines = 5;
    int ncolumns = 5;
    char** matrix;
    matrix = alloc_matrix_char(nlines, ncolumns);
    unsigned long long key = 2244;
    store_key_char(matrix,2,key);
    print_matriz_chars(matrix);
*/

 /*
    // Create a matrix with 5 lines and 10 columns
    char** matrix = alloc_matrix_char(5, 10);
    // Store the key 12345 in the matrix
    store_key_char(matrix, 5, 12345);
    // Print the matrix to check if the key was stored correctly
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 10; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
*/

 // exists_key_char
/*
    char** matrix=alloc_matrix_char(5,10);
    store_key_char(matrix,1,22444);
    store_key_char(matrix,2,22333);
    store_key_char(matrix,3,55444);
    printf("%d\n", exists_key_char(matrix, 1, 22444));
    printf("%d\n", exists_key_char(matrix, 2, 5588));
    printf("%d\n", exists_key_char(matrix, 3, 55444));
*/

// get_privatekey_char
/*
    char** matrix_kpub=alloc_matrix_char(3,5);
    char** matrix_kpriv=alloc_matrix_char(3,5);
    store_key_char(matrix_kpub,3,22444);
    store_key_char(matrix_kpriv,3,22333);
    printf("Private key for pubkey 22444: %llu\n",get_private_key_char(matrix_kpub,matrix_kpriv,3,22444) );
*/

 /*
 //get_runlength_char

        char* matrix_kpriv[3] = {"16", "36", "5522"};
        char* matrix_kcod[3] = {"2", "3", "4"};
        int lines = 3;
        unsigned long long privkey = 16;
        unsigned long long runlength = get_runlength_char(matrix_kpriv, matrix_kcod, lines, privkey);
        printf("Run-length key: %llu\n", runlength);


*/


/*
    unsigned long long pubKey =4432;
    printf("-------------------------------\n");
    clock_t ini = clock(); // guarda o inicial
    printf("%llu -> %llu\n",pubKey,calc_private_key_int(pubKey));
    printf("%.1f Microsegundos pelos bipolares consecutivos\n", (((double)clock() - ini) / CLOCKS_PER_SEC)*1000000);
    clock_t ini1 = clock(); // guarda o inicial
    printf("%llu -> %llu\n",pubKey,calc_private_key_char(pubKey));
    printf("%.1f Microsegundos pela multiplicacao sucessiva\n", (((double)clock() - ini1) / CLOCKS_PER_SEC)*1000000);
    printf("-------------------------------\n");
    return 0;
*/
}






