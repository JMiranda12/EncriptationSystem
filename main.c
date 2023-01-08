#include <stdio.h>
#include "Inteiros.h"
#include "str.h"
#define MAX_DIGITS 10


void save_txt();

void print_matrix_ints(short** matrix, int lines, int columns) {
    for (int i = 0; i < lines; i++) {
        if (matrix[i] == NULL) {
            printf("(empty)\n");
        } else {
            for (int j = 0; j < columns; j++) {
                printf("%d ", matrix[i][j]);
            }
            printf("\n");
        }
    }
}
/*
void print_matrix_chars(short** matrix,int lines, int columns) {
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
}
*/
int main() {

    // unsigned long long public_key = new_public_key_int();
    // printf("Generated public key: %llu \n", public_key);

    // unsigned long long public_key = 251;
    // unsigned long long private_key = calc_private_key_int(public_key);
    // printf("Generated private key: %llu \n", private_key);

    // unsigned long long private_key = 7778888;
    // unsigned long long runlength_key = calc_runlength_int(private_key);
    // printf("Runlength : %llu \n", runlength_key);

    // Test with run-length encoding 2122
    /*unsigned long long run_length_encoding = 2122;
    *unsigned long long private_key = private_key_from_runlength_int(run_length_encoding);
    *printf("Run-length encoding: %llu, Private key: %llu\n", run_length_encoding, private_key);
    */

    // int nlines = 4;
    // int ncolumns = 3;
    // short** matrix = alloc_matrix_int(nlines, ncolumns);
/*
    int lines = 3;
    int columns = 5;
    unsigned long long key = 11222;
    unsigned long long key2 = 22333;
    short** matrix = alloc_matrix_int(lines, columns);
    store_key_int(matrix, lines, key);
    store_key_int(matrix, lines, key2);
    print_matrix(matrix, lines, columns);
    return 0;
*/
/*
    short** matrix = alloc_matrix_int(3, 5);
    store_key_int(matrix, 3, 2244);
    //print_matrix(matrix,3,5);
    printf("%d", exists_key_int(matrix,3,2244));
*/

/*
// Create a matrix and store some keys in it
    short** matrix = alloc_matrix_int(3, 5);
    store_key_int(matrix, 3, 224444);
    store_key_int(matrix, 3, 224444);
    store_key_int(matrix, 3, 224444);

    // Test the exists_key_int function
    int key_exists = exists_key_int(matrix, 3, 224444);
    int key_does_not_exist = exists_key_int(matrix, 3, 224444);
    printf("Key exists: %d\n", key_exists);  // Should output 1
    printf("Key does not exist: %d\n", key_does_not_exist);  // Should output 0
*/

/* --------GET_PRIVATE_KEY_INT-------
    short** public_keys_matrix = alloc_matrix_int(5, 10);  // Allocate memory for the public keys matrix
    short** private_keys_matrix = alloc_matrix_int(5, 10);  // Allocate memory for the private keys matrix

// Store a public key and its corresponding private key
    unsigned long long public_key = 12345;  // Public key
    unsigned long long private_key = calc_private_key_int(public_key);  // Calculate the corresponding private key
    store_key_int(public_keys_matrix, 5, public_key);  // Store the public key in the public keys matrix
    store_key_int(private_keys_matrix, 5, private_key);  // Store the private key in the private keys matrix
    print_matrix(public_keys_matrix,3,5);
    print_matrix(private_keys_matrix,3,5);
// Get the private key corresponding to the given public key
    unsigned long long private_key_from_matrix = get_private_key_int(public_keys_matrix, private_keys_matrix, 5, public_key);
    printf("Private key corresponding to public key %llu: %llu\n", public_key, private_key_from_matrix);
*/


/* --------------KEY_LONG_2_DIGITS_INT
    unsigned long long public_key = new_public_key_int(); //This will generate a new random public key
    printf("%llu\n", public_key);

    short* digits = key_long_2_digits_int(public_key); //Get the digits of the key
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

short** matrix_kpub=alloc_matrix_int(5,5);
short** matrix_kpriv=alloc_matrix_int(5,5);
short** matrix_kcod=alloc_matrix_int(5,5);

    store_key_int(matrix_kpub,1,22333);
    store_key_int(matrix_kpub,2,33444);
    store_key_int(matrix_kpriv,1,22244);
    store_key_int(matrix_kpriv,2,77555);
    store_key_int(matrix_kcod,1,11133);
    store_key_int(matrix_kcod,2,11222);

  // print_matrix(matrix_kpub,5,5);
   printf("%hd ", matrix_kpub[1][1]);
   printf("------\n");
  // print_matrix(matrix_kpriv,5,5);
    printf("------\n");
  // print_matrix(matrix_kcod,5,5);
    printf("------\n");
   save_txt_keys_int(matrix_kpub,matrix_kpriv,matrix_kcod,5,"testttt.txt");
*/

// CHARS

// calc_private_key_char
  /*  unsigned long long pubkey = 251;
    unsigned long long privkey = calc_private_key_char(pubkey);
    printf("Private key for pubkey %llu: %llu\n", pubkey, privkey);
*/
    //calc_runlength_char && private_key_from_runlength_char
  /*  unsigned long long privkey = 2253;
    printf("%llu",calc_runlength_char(privkey));
    printf("%llu",private_key_from_runlength_char(privkey));
*/

  // alloc_matrix_char && store_key_char
  /*  int nlines = 5;
    int ncolumns = 5;
    char** matrix;
    matrix = alloc_matrix_char(nlines, ncolumns);
    unsigned long long key = 2244;
    store_key_char(matrix,2,key);

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
/*
 //get_runlength_char

        char* matrix_kpriv[3] = {"16", "36", "5522"};
        char* matrix_kcod[3] = {"2", "3", "4"};
        int lines = 3;
        unsigned long long privkey = 16;
        unsigned long long runlength = get_runlength_char(matrix_kpriv, matrix_kcod, lines, privkey);
        printf("Run-length key: %llu\n", runlength);


*/


    return 0;
}






