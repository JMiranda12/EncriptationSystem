#include <__wctype.h>

#include "str.h"
#include "Inteiros.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

void clean_matrix_int(short** mat, int lines){
    for (int i = 0; i < lines; ++i) {
        for (int j = 0; j < 20; ++j) {
            *(*(mat+i)+j)=-1;
        }
    }
}

unsigned long long new_public_key_int(void) {
    unsigned long long result =0;
    unsigned long long max = (250);
    result = (rand() % (max - 0)) + 1;  //Random number entre 0 e max-1 +1 = rand number entre 1 e max
    return result;
}

short* key_long_2_digits_int(unsigned long long key){
    // Calcula o numero de digitos na chave
    int count = 0;
    unsigned long long temp = key;
    while (temp > 0) {
        count++;
        temp /= 10;
    }
    int num=0,i=0;
    short* str = malloc( count *sizeof (int));
    str[count]=-1;
    for (i = count-1; key!=0 ; i--) {
        num=key%10;
        key=key/10;
        str[i]=num;
    }
    return str; // apontador para o array de digitos
}


unsigned long long key_digits_2_long_int(short* keydigits) {
    int num_digits = 0;
    while (keydigits[num_digits] != -1) {
        num_digits++;
    }
    // Anda pelo array e reconstroi a chave original . Multiplica por 10 para adicionar o digito
    unsigned long long key = 0;
    for (int i = 0; i < num_digits; i++) {
        key = key * 10 + keydigits[i];
    }
    return key;
}


// Abordagem de gerar números bipolares sucessivos e verificar se são ou não múltiplos
unsigned long long calc_private_key_int(unsigned long long pubkey) {
    unsigned long long num_bip = 0;
    for (int k = 2; k < 100; ++k) {
        int bipolar[k];
        for (int i = 1; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                for (int l = 0; l < k; ++l)
                    bipolar[l] = i;
                if (i != j) {
                    for (int l = k - 1; l > 0; --l) {
                        bipolar[l] = j;
                        //conversao array para unsigned long long
                        for (int m = 0; m < k; m++) {
                            num_bip = num_bip * 10 + bipolar[m];
                        }
                        if (num_bip != pubkey) {
                            //verifica se e multiplo
                            if (num_bip % pubkey == 0) {
                                return num_bip;
                            }
                        }
                        num_bip = 0;
                    }
                }
            }
        }
    }
    return 0;
}

unsigned long long calc_runlength_int(unsigned long long privkey){
    // Variavel para guardar o run_length
    unsigned long long run_length = 0;
    unsigned long long temp = privkey;

    // Conta o numero de ocurrências de cada digito na privkey
    short digits[10] = {0};
    int num_digits = 0;
    while (temp > 0) {
        short digit = temp % 10;
        digits[digit]++;
        num_digits++;
        temp /= 10;
    }
    // Codifica a privkey usando o método de run-length
    for (int i = 0; i < 10; i++) {
        if (digits[i] > 0) {
            // Adiciona a contagem do numero de digits ao run-length
            run_length = run_length * 10 + digits[i];
            // Adiciona o digito ao run-length
            run_length = run_length * 10 + i;
        }
    }
    return run_length;
}

unsigned long long private_key_from_runlength_int(unsigned long long runlengthkey){
    int array[4];
    unsigned long long original_priv=0;
    array[3]=runlengthkey%10;
    runlengthkey /= 10;
    array[2]=runlengthkey%10;
    runlengthkey/=10;
    array[1]=runlengthkey%10;
    runlengthkey/=10;
    array[0]=runlengthkey;


    for (int i = 0; i < array[0]; ++i) {
        original_priv+=array[1];
        original_priv*=10;
    }
    for (int i = 0; i < array[2]; i++) {
        original_priv+=array[3];
        if (i!=array[2]-1)
            original_priv*=10;
    }
    return original_priv;
}

short** alloc_matrix_int(int nlines, int ncolumns) {
    short** matrix = malloc(nlines * sizeof(short*));
    for (int i = 0; i < nlines; i++) {
        matrix[i] = NULL;
    }
    return matrix;
}


void store_key_int(short** matrix, int lines, unsigned long long key) {
    // Encontra a 1ª posição livre da matrix
    int i;
    for (i = 0; i < lines && matrix[i] != NULL; i++);
    // Se a mtriz estiver cheia, retorna sem guardar a chave
    if (i == lines) return;
    // Aloca memória para os digitos da key
    int ndigits = 0;
    unsigned long long temp = key;
    while (temp > 0) {
        temp /= 10;
        ndigits++;
    }
    matrix[i] = malloc(ndigits * sizeof(short));

    // Guarda os digitos na ordem correta
    temp = key;
    for (int j = ndigits - 1; j >= 0; j--) {
        matrix[i][j] = temp % 10;
        temp /= 10;
    }
}


int exists_key_int(short** matrix, int lines, unsigned long long key) {
    int count = 0;
    unsigned long long temp = key;
    while (temp > 0) {
        count++;
        temp /= 10;
    }
    char array[count];
    int n=0;
    for (int i = count-1; i != -1; --i) {
        n=key%10;
        key/=10;
        array[i]=n;
    }
    for (int i = 0; i < lines; ++i) {//linhas
        for (int j = 0; j < count; ++j) {//colunas
            if (matrix[i][j]!=array[j])
                break;
            if (j==count-1){
                return 1;
            }
        }
    }
    return 0;
}


unsigned long long get_private_key_int(short **matrix_kpub, short **matrix_kpriv, int lines, unsigned long long pubkey){
    unsigned long long nreturn=0;
    int position= exists_key_int(matrix_kpub, lines, pubkey);
    if (position != -1){
        nreturn= key_digits_2_long_int(*(matrix_kpriv + position));
    }
    return nreturn;
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


void sort_matrix_int(short **matrix, int lines, int order){
    unsigned long long arr[lines];
    for (int i = 0; i < lines; ++i) {
        arr[i]=key_digits_2_long_int(*(matrix+ i));
    }
    if (order==1){
        mergeSort(arr,lines);
    }else{
        for ( int i = 0 ; i < lines; i++)
        {
            for ( int j = i; j < lines; j++)
            {
                if (arr[i] < arr[j])
                {
                    unsigned long long aux= arr[i];
                    arr[i] = arr[j];
                    arr[j] = aux;
                }
            }
        }
    }

    clean_matrix_int(matrix, lines);
    for (int i = 0; i < lines; ++i) {
        *(matrix+i)=key_long_2_digits_int(arr[i]);
    }

}


void sort_all_matrices_int(short** matrix_kpub, short** matrix_kpriv, short** matrix_kcod, int lines, int order) {
    sort_matrix_int(matrix_kpub, lines, order);
    sort_matrix_int(matrix_kpriv, lines, order);
    sort_matrix_int(matrix_kcod, lines, order);
}

void save_txt_keys_int(short **matrix_kpub, short **matrix_kpriv, short **matrix_kcod, int lines, char filename[]){
    FILE * fp;
    fp=fopen(filename,"w");
    if(fp!=NULL){
        fprintf(fp,"Number of keys:%d\n",lines);
        fprintf(fp,"ID PUB\t\t PRIV\t\t\t RUN\n");
        for (int i = 0; *(matrix_kpub + i) != NULL; i++) {
            unsigned long long pub =key_digits_2_long_int(*(matrix_kpub + i));
            unsigned long long priv =key_digits_2_long_int(*(matrix_kpriv+ i));
            unsigned long long run=key_digits_2_long_int(*(matrix_kcod+ i));
            fprintf(fp,"%d %llu\t\t %llu\t\t\t %llu\n",i,pub,priv,run);
        }
        fclose(fp);
    }else{
        printf("ERRO FICHEIRO");
    }
}

/*
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
}*/



