#include <__wctype.h>


#include "Inteiros.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>


unsigned long long new_public_key_int(void) {
     // Seed the random number generator with the current time
     srand(time(NULL));

     // Generate a random public key between 1 and 100000
     return rand() % 100000 + 1;
}



short* key_long_2_digits_int(unsigned long long key) {
    // Calculate the number of digits in the key
    int num_digits = 0;
    unsigned long long temp = key;
    while (temp > 0) {
        num_digits++;
        temp /= 10;
    }
    // Allocate memory for the array of digits
    short* digits = malloc(num_digits * sizeof(short));
    // Extract the digits of the key and store them in the array
    for (int i = num_digits - 1; i >= 0; i--) {
        digits[i] = key % 10;
        key /= 10;
    }
    // Return a pointer to the array of digits
    return digits;
}


unsigned long long key_digits_2_long_int(short* keydigits) {
    // Calculate the number of digits in the array
    int num_digits = 0;
    while (keydigits[num_digits] != -1) {
        num_digits++;
    }
    // Calculate the long key from the array of digits
    unsigned long long key = 0;
    for (int i = 0; i < num_digits; i++) {
        key = key * 10 + keydigits[i];
    }
    // Return the long key
    return key;
}


unsigned long long calc_private_key_int(unsigned long long pubkey) {
    // Calculate the smallest multiple of the public key that is greater than the public key
    unsigned long long privkey = pubkey + 1;

    // Check if the private key is a bipolar number
    while (1) {
        // Check if the private key has only two distinct digits
        short digits[10] = {0};
        int num_digits = 0;
        unsigned long long temp = privkey;
        while (temp > 0) {
            short digit = temp % 10;
            digits[digit]++;
            num_digits++;
            temp /= 10;
        }
        int num_distinct_digits = 0;
        for (int i = 0; i < 10; i++) {
            if (digits[i] > 0) {
                num_distinct_digits++;
            }
        }
        if (num_distinct_digits > 2) {
            // Private key has more than two distinct digits, increment and try again
            privkey++;
            continue;
        }

        // Check if all repetitions of one of the digits precede all occurrences of the other digit
        short first_digit = -1;
        short second_digit = -1;
        int first_digit_count = 0;
        int second_digit_count = 0;
        for (int i = 0; i < 10; i++) {
            if (digits[i] > 0) {
                if (first_digit == -1) {
                    first_digit = i;
                    first_digit_count = digits[i];
                } else if (second_digit == -1) {
                    second_digit = i;
                    second_digit_count = digits[i];
                } else {
                    // Private key has more than two distinct digits, increment and try again
                    privkey++;
                    break;
                }
            }
        }
        if (first_digit_count == num_digits || second_digit_count == num_digits) {
            // Private key is a bipolar number, return it
            return privkey;
        } else {
            // Private key is not a bipolar number, increment and try again
            privkey++;
        }
    }
}


unsigned long long calc_runlength_int(unsigned long long privkey){
    // Create a variable to store the run-length encoding
    unsigned long long run_length = 0;
    unsigned long long temp = privkey;

    // Count the number of occurrences of each digit in the private key
    short digits[10] = {0};
    int num_digits = 0;
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
            run_length = run_length * 10 + digits[i];

            // Add the digit to the run-length encoding
            run_length = run_length * 10 + i;
        }
    }

    // Return the run-length encoding
    return run_length;
}


unsigned long long private_key_from_runlength_int(unsigned long long runlengthkey) {
    // Create a variable to store the private key
    unsigned long long privkey = 0;

    // Decode the run-length encoding to obtain the private key
    while (runlengthkey > 0) {
        // Get the digit
        short digit = runlengthkey % 10;
        runlengthkey /= 10;

        // Get the count of the digit
        short digit_count = runlengthkey % 10;
        runlengthkey /= 10;

        // Add the digit to the private key the appropriate number of times
        for (int i = 0; i < digit_count; i++) {
            privkey = privkey * 10 + digit;
        }
    }

    // Reverse the digits in the private key
    unsigned long long reversed_privkey = 0;
    while (privkey > 0) {
        reversed_privkey = reversed_privkey * 10 + privkey % 10;
        privkey /= 10;
    }

    // Return the private key
    return reversed_privkey;
}

short** alloc_matrix_int(int nlines, int ncolumns) {
    short** matrix = malloc(nlines * sizeof(short*));
    for (int i = 0; i < nlines; i++) {
        matrix[i] = NULL;
    }
    return matrix;
}


void store_key_int(short** matrix, int lines, unsigned long long key) {
    // Find the first available position in the matrix
    int i;
    for (i = 0; i < lines && matrix[i] != NULL; i++);

    // If the matrix is full, return without storing the key
    if (i == lines) return;

    // Allocate memory for the key digits
    int ndigits = 0;
    unsigned long long temp = key;
    while (temp > 0) {
        temp /= 10;
        ndigits++;
    }
    matrix[i] = malloc(ndigits * sizeof(short));

    // Store the key digits in the correct order
    temp = key;
    for (int j = ndigits - 1; j >= 0; j--) {
        matrix[i][j] = temp % 10;
        temp /= 10;
    }
}


int exists_key_int(short** matrix, int lines, unsigned long long key) {
    // Iterate over the rows of the matrix
    for (int i = 0; i < lines; i++) {
        if (matrix[i] == NULL) continue;  // Skip empty rows
        int ndigits = 0;
        while (matrix[i][ndigits] != 0) ndigits++;  // Count the number of digits in the key

        // Compare the digits of the key with the digits of the key in the matrix
        unsigned long long temp = key;
        int equal = 1;
        for (int j = 0; j < ndigits; j++) {
            if (temp % 10 != matrix[i][j]) {
                equal = 0;
                break;
            }
            temp /= 10;
        }

        // Return 1 if the key was found
        if (equal) return 1;
    }

    // Return 0 if the key was not found
    return 0;
}


unsigned long long get_private_key_int(short** matrix_kpub, short** matrix_kpriv, int lines, unsigned long long pubkey) {
    // Iterate through each line in the matrix_kpub
    for (int i = 0; i < lines; i++) {
        // Check if the current line in matrix_kpub matches the given pubkey
        if (matrix_kpub[i] == pubkey) {
            // If it matches, return the corresponding private key from matrix_kpriv
            return matrix_kpriv[i];
        }
    }
    // If the pubkey was not found in matrix_kpub, return 0
    return 0;
}


unsigned long long get_runlength_int(short** matrix_kpriv, short** matrix_kcod, int lines, unsigned long long privkey) {
    for (int i = 0; i < lines; i++) {
        unsigned long long current_privkey = key_digits_2_long_int(matrix_kpriv[i]);
        if (current_privkey == privkey) {
            return key_digits_2_long_int(matrix_kcod[i]);
        }
    }
    return 0;
}



unsigned long long delete_key_int(short **matrix_kpub, short **matrix_kpriv, short **matrix_kcod, int lines, short pubkey) {
    for (int i = 0; i < lines; i++) {
        if (matrix_kpub[i][0] == pubkey) {
            // Delete key from matrix_kpub
            for (int j = 0; j < 10; j++) {
                matrix_kpub[i][j] = 0;
            }
            // Delete corresponding key from matrix_kpriv
            for (int j = 0; j < 10; j++) {
                matrix_kpriv[i][j] = 0;
            }
            // Delete corresponding key from matrix_kcod
            for (int j = 0; j < 10; j++) {
                matrix_kcod[i][j] = 0;
            }
            return pubkey;
        }
    }
    return 0;
}


void bulk_populate_public_keys_int(short **matrix_kpub, int lines) {
    for (int i = 0; i < lines; i++) {
        unsigned long long key = new_public_key_int();
        store_key_int(matrix_kpub, lines, key);
    }
}


void bulk_compute_private_keys_int(short **matrix_kpub, short **matrix_kpriv, int lines) {
    for (int i = 0; i < lines; i++) {
        // Calculate the private key for the public key in the current line of the matrix_kpub
        unsigned long long privkey = calc_private_key_int(matrix_kpub[i]);
        // Store the private key in the current line of the matrix_kpriv
        store_key_int(matrix_kpriv, lines, privkey);
    }
}


void bulk_compute_runlengths_int(short **matrix_kpriv, short **matrix_kcod, int lines) {
    for (int i = 0; i < lines; i++) {
        unsigned long long privkey = matrix_kpriv[i][0];
        unsigned long long runlength = calc_runlength_int(privkey);
        store_key_int(matrix_kcod, lines, runlength);
    }
}


// Helper function to check if a given key contains a partial key
bool contains(unsigned long long key, unsigned long long partial) {
    while (key > 0) {
        if (key % 10 == partial % 10) {
            return true;
        }
        key /= 10;
        partial /= 10;
    }
    return false;
}
short** search_private_keys_int(short** matrix_kpub, short** matrix_kpriv, int lines, unsigned long long partialpubkey) {
    // Create an array to store the matching private keys
    short** matching_keys = malloc(sizeof(short*) * lines);

    // Keep track of the number of matching keys found
    int count = 0;

    // Iterate through the public key matrix
    for (int i = 0; i < lines; i++) {
        // Check if the current public key contains the partial key
        if (contains(matrix_kpub[i], partialpubkey)) {
            // If it does, store the corresponding private key in the matching keys array
            matching_keys[count] = matrix_kpriv[i];
            count++;
        }
    }

    // Reallocate the matching keys array to the correct size
    matching_keys = realloc(matching_keys, sizeof(short*) * count);

    return matching_keys;
}


void sort_matrix_int(short **matrix, int lines, int order) {
    short *temp;
    for (int i = 0; i < lines - 1; i++) {
        for (int j = i + 1; j < lines; j++) {
// Compare the keys in the current line and the next line
            if ((order == 1 && matrix[i][0] > matrix[j][0]) || (order == 0 && matrix[i][0] < matrix[j][0])) {
// Swap the keys
                temp = matrix[i];
                matrix[i] = matrix[j];
                matrix[j] = temp;
            }
        }
    }
}


void sort_all_matrices_int(short** matrix_kpub, short** matrix_kpriv, short** matrix_kcod, int lines, int order) {
    sort_matrix_int(matrix_kpub, lines, order);
    sort_matrix_int(matrix_kpriv, lines, order);
    sort_matrix_int(matrix_kcod, lines, order);
}


void save_txt_keys_int(short** matrix_kpub, short** matrix_kpriv, short** matrix_kcod, int lines, char filename[]) {
    int i, j;
    FILE *fp;
    fp = fopen(filename, "w");
    for (i = 0; i < lines; i++) {
        for (j = 0; j < 5; j++) {
            if (matrix_kpub[i][j] != NULL) {
                fprintf(fp, "%hd ", matrix_kpub[i][j]);
            } else {
                fprintf(fp, "0 ");
            }
        }
        fprintf(fp, "\n");
    }
    fprintf(fp, "------\n");
    for (i = 0; i < lines; i++) {
        for (j = 0; j < 5; j++) {
            if (matrix_kpriv[i][j] != NULL) {
                fprintf(fp, "%hd ", matrix_kpriv[i][j]);
            } else {
                fprintf(fp, "0 ");
            }
        }
        fprintf(fp, "\n");
    }
    fprintf(fp, "------\n");
    for (i = 0; i < lines; i++) {
        for (j = 0; j < 5; j++) {
            if (matrix_kcod[i][j] != NULL) {
                fprintf(fp, "%hd ", matrix_kcod[i][j]);
            } else {
                fprintf(fp, "0 ");
            }
        }
        fprintf(fp, "\n");
    }
    fprintf(fp, "------\n");
    fclose(fp);
}