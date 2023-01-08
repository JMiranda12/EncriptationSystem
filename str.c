
#include "Inteiros.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#define MAX_DIGITS 10


char* key_long_2_digits_char(unsigned long long key) {
    // Calculate the number of digits in the key
    int num_digits = 0;
    unsigned long long temp = key;
    while (temp > 0) {
        num_digits++;
        temp /= 10;
    }
    // Allocate an array of characters to hold the digits
    char* digits = malloc(num_digits * sizeof(char));

    // Convert each digit of the key to a character and add it to the array
    temp = key;
    for (int i = num_digits - 1; i >= 0; i--) {
        digits[i] = (temp % 10) + '0';
        temp /= 10;
    }

    return digits;
}


unsigned long long key_digits_2_long_char(char* keydigits) {
    unsigned long long key = 0;
    int i;
    for (i = 0; keydigits[i] != '\0'; i++) {
        key = key * 10 + (keydigits[i] - '0');
    }
    return key;
}


unsigned long long calc_private_key_char(unsigned long long pubkey) {
    // Generate the first bipolar number (11)
    char privkey[3] = {'1', '1', '\0'};

    // Keep generating successive bipolar numbers until a multiple of pubkey is found
    while (key_digits_2_long_char(privkey) % pubkey != 0) {
        // Increment the second digit of the current bipolar number
        privkey[1]++;

        // If the second digit is greater than 9, set it to 0 and increment the first digit
        if (privkey[1] > '9') {
            privkey[1] = '0';
            privkey[0]++;
        }
    }
    // Return the private key as a long integer
    return key_digits_2_long_char(privkey);
}

unsigned long long calc_runlength_char(unsigned long long privkey){
    // Create a string to store the run-length encoding
    char run_length[20];
    int index = 0;

    // Count the number of occurrences of each digit in the private key
    short digits[10] = {0};
    int num_digits = 0;
    unsigned long long temp = privkey;
    while (temp > 0) {
        short digit = temp % 10;
        digits[digit]++;
        num_digits++;
        temp /= 10;
    }

    // Encode the private key using run-length encoding
    for (int i = 0; i < 10; i++) {
        if (digits[i] > 0) {
            // Add the count of the digit to the run-length encoding
            char digit_count[20];
            sprintf(digit_count, "%d", digits[i]);
            for (int j = 0; digit_count[j] != '\0'; j++) {
                run_length[index++] = digit_count[j];
            }
            // Add the digit to the run-length encoding
            run_length[index++] = i + '0';
        }
    }
    // Add the null terminator to the end of the run-length encoding
    run_length[index] = '\0';

    // Convert the run-length encoding to an unsigned long long
    unsigned long long runlengthkey = strtoull(run_length, NULL, 10);

    // Return the run-length encoding as an unsigned long long
    return runlengthkey;
}



unsigned long long private_key_from_runlength_char(unsigned long long runlengthkey){
    // Create a string to store the run-length encoding
    char run_length[20];
    sprintf(run_length, "%llu", runlengthkey);

    // Create a string to store the private key
    char private_key[20];
    int index = 0;

    // Decode the run-length encoding to obtain the private key
    for (int i = 0; run_length[i] != '\0'; i += 2) {
        // Get the count of the digit
        char digit_count[20];
        digit_count[0] = run_length[i];
        digit_count[1] = '\0';
        int count = atoi(digit_count);

        // Get the digit
        char digit[2];
        digit[0] = run_length[i + 1];
        digit[1] = '\0';
        int num = atoi(digit);

        // Add the digit to the private key the appropriate number of times
        for (int j = 0; j < count; j++) {
            private_key[index++] = num + '0';
        }
    }
    // Add the null terminator to the end of the private key
    private_key[index] = '\0';

    // Convert the private key to an unsigned long long
    unsigned long long privkey = strtoull(private_key, NULL, 10);

    // Return the private key
    return privkey;
}


char** alloc_matrix_char(int nlines, int ncolumns) {
    char** matrix;
    int i;
    matrix = (char**) malloc(nlines * sizeof(char*));
    for (i = 0; i < nlines; i++) {
        matrix[i] = (char*) malloc(ncolumns * sizeof(char));
    }
    return matrix;
}

void store_key_char(char** matrix, int lines, unsigned long long key) {
    // Convert key to array of digits
    char* keydigits = key_long_2_digits_char(key);
    int i;
    // Find first empty position in matrix
    for (i = 0; i < lines; i++) {
        if (matrix[i][0] == 0) {
            // Found empty position, store key in matrix
            int j;
            for (j = 0; j < strlen(keydigits); j++) {
                matrix[i][j] = keydigits[j];
            }
            break;
        }
    }
    free(keydigits);
}


int exists_key_char(char** matrix, int lines, unsigned long long key) {
    int i, j;
    char keydigits[12];
    sprintf(keydigits, "%llu", key);
    int keylength = strlen(keydigits);
    for (i = 0; i < lines; i++) {
        int currkeylength = strlen(matrix[i]);
        if (currkeylength != keylength) {
            continue;
        }
        int isequal = 1;
        for (j = 0; j < keylength; j++) {
            if (matrix[i][j] != keydigits[j]) {
                isequal = 0;
                break;
            }
        }
        if (isequal) {
            return 1;
        }
    }
    return 0;
}


unsigned long long get_private_key_char(char** matrix_kpub, char** matrix_kpriv, int lines, unsigned long long pubkey) {
    int i, j;
    unsigned long long privkey;
    for (i = 0; i < lines; i++) {
        privkey = 0;
        for (j = 0; j < strlen(matrix_kpub[i]); j++) {
            privkey = privkey * 10 + (matrix_kpub[i][j] - '0');
        }
        if (privkey == pubkey) {
            privkey = 0;
            for (j = 0; j < strlen(matrix_kpriv[i]); j++) {
                privkey = privkey * 10 + (matrix_kpriv[i][j] - '0');
            }
            return privkey;
        }
    }
    return 0;
}

unsigned long long get_runlength_char(char** matrix_kpriv, char** matrix_kcod, int lines, unsigned long long privkey) {
    int i;
    for (i = 0; i < lines; i++) {
// Convert private key from matrix_kpriv to long long
        char* privkey_str = matrix_kpriv[i];
        unsigned long long privkey_long = strtoull(privkey_str, NULL, 10);

        if (privkey == privkey_long) {
            // Found private key, get corresponding run-length key
            char* runlength_str = matrix_kcod[i];
            unsigned long long runlength_long = strtoull(runlength_str, NULL, 10);
            return runlength_long;
        }
    }

// Private key not found
    return 0;
}

unsigned long long delete_key_char(char** matrix_kpub, char** matrix_kpriv, char** matrix_kcod, int lines, unsigned long long pubkey) {
    int i;
    unsigned long long privkey = 0;
    for (i = 0; i < lines; i++) {
        if (matrix_kpub[i] == pubkey) {
            privkey = matrix_kpriv[i];
            matrix_kpub[i] = 0;
            matrix_kpriv[i] = 0;
            matrix_kcod[i] = 0;
            break;
        }
    }
    return privkey;
}


void bulk_populate_public_keys_char(char** matrix_kpub, int lines) {
    int i;
    for (i = 0; i < lines; i++) {
        // Generate a random public key between 1 and 100000
        unsigned long long pubkey = new_public_key_int();

        // Convert the public key to an array of digits in ASCII
        char* pubkey_digits = key_long_2_digits_char(pubkey);

        // Store the public key in the matrix
        store_key_char(matrix_kpub, lines, pubkey_digits);

        // Free the memory allocated for the array of digits
        free(pubkey_digits);
    }
}


void bulk_compute_private_keys_char(char **matrix_kpub, char **matrix_kpriv, int lines);

/**
 * Automatically calculate and store all run-lengths for the existing private keys.
 * @param matrix_kpriv - private keys matrix
 * @param matrix_kcod - run-lengths matrix
 * @param lines - matrix number of lines
 */
    void bulk_compute_runlengths_char(char **matrix_kpriv, char **matrix_kcod, int lines);

/**
 * Return a list of all private keys matching a given partial public key.
 * @param matrix_kpub - public keys matrix
 * @param matrix_kpriv - private keys matrix
 * @param lines - matrix number of lines
 * @param partialpubkey - part of public key to filter the private keys
 * @return array of private keys matching the partialpubkey
 */
    char **
    search_private_keys_char(char **matrix_kpub, char **matrix_kpriv, int lines, unsigned long long partialpubkey);

/**
 * Sort a matrix keys in ascending or descending order
 * @param matrix - matrix to be sorted
 * @param lines - matrix number of lines
 * @param order - order == 1 ? ascending : descending
 */
    void sort_matrix_char(char **matrix, int lines, int order);

/**
 * Sort all matrices keys in ascending or descending order
 * @param matrix_kpub - public keys matrix
 * @param matrix_kpriv - private keys matrix
 * @param matrix_kcod - run-lengths matrix
 * @param lines - matrix number of lines
 * @param order - order == 1 ? ascending : descending
 */
    void sort_all_matrices_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int lines, int order);

/**
 * Print all keys on the console, sorted by pubkeys sizes (i.e. number of digits).
 * @param matrix_kpub - public keys matrix
 * @param matrix_kpriv - private keys matrix
 * @param matrix_kcod - run-lengths matrix
 * @param lines - matrix number of lines
 * @param order - order == 0 ? current order : order == 1 ? ascending : descending
 */
    void list_keys_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int lines, int order);

/**
 * Save all matrix data to a text file
 * @param matrix_kpub - public keys matrix
 * @param matrix_kpriv - private keys matrix
 * @param matrix_kcod - run-lengths matrix
 * @param lines - matrix number of lines
 * @param filename - name of the text file where to store the data
 */
    void save_txt_keys_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int lines, char filename[]);

/**
 * Loads data into the matrices from a text file.
 * @param matrix_kpub - public keys matrix
 * @param matrix_kpriv - private keys matrix
 * @param matrix_kcod - run-lengths matrix
 * @param lines - matrix number of lines
 * @param filename - name of the text file to load data from
 */
    void load_txt_keys_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int lines, char filename[]);

/**
 * Save all matrix data to a binary file
 * @param matrix_kpub - public keys matrix
 * @param matrix_kpriv - private keys matrix
 * @param matrix_kcod - run-lengths matrix
 * @param lines - matrix number of lines
 * @param filename - name of the binary file where to store the data
 */
    void save_bin_keys_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int lines, char filename[]);

/**
 * Loads data into the matrices from a binary file.
 * @param matrix_kpub - public keys matrix
 * @param matrix_kpriv - private keys matrix
 * @param matrix_kcod - run-lengths matrix
 * @param lines - matrix number of lines
 * @param filename -name of the binary file to load data from
 */
    void load_bin_keys_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int lines, char filename[]);

