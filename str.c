
#include "Inteiros.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#define MAX_DIGITS 10

int count_digits_char (unsigned long long key){
    unsigned long long count =0;
    while (key != 0){
        count++;
        key /= 10;
    }
    return count;
}

unsigned long long isBipolar(char *text){
    char last;
    int boolean=0;
    for (int i = 0; i < text[i]!='\0'; ++i) // verifica se e numero
        if(text [i] < '0' || text [i] > '9')return -2;
    for (int i = 0;text[i]!='\0'; ++i) {
        if (i==0)last=text[i];
        if(boolean==0){
            if (text[i] == last){
                continue;
            }else{
                boolean=1;
                last=text[i];
            }
        }else if(text[i] != last)return -1;

    }
    if (boolean==0)return -1;
    return atoi(text);
}

char* itoa(int num, char* buffer, int base){
    int current = 0;
    if (num == 0) {
        buffer[current++] = '0';
        buffer[current] = '\0';
        return buffer;
    }
    int num_digits = 0;
    if (num < 0) {
        if (base == 10) {
            num_digits ++;
            buffer[current] = '-';
            current ++;
            num *= -1;
        }
        else
            return NULL;
    }
    num_digits += (int)floor(log(num) / log(base)) + 1;
    while (current < num_digits)
    {
        int base_val = (int) pow(base, num_digits-1-current);
        int num_val = num / base_val;
        char value = num_val + '0';
        buffer[current] = value;
        current ++;
        num -= base_val * num_val;
    }
    buffer[current] = '\0';
    return buffer;
}


void reset_matrix_char(char **matrix, int lines){
    for (int k = 0; k < lines; ++k) {
        *(matrix+k)= calloc(20,sizeof (char));
    }
}

int isSorted(unsigned long long arr[], int size) {

    for (int i = 0; i < size - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return -1;
        }

    }
    return 1;
}

//merge sort
int merge(unsigned long long a[], unsigned long long aux[], int lo, int mid, int hi) {
    for (int k = lo; k <= hi; k++) {
        aux[k] = a[k];
    }

    int i = lo;
    int j = mid + 1;

    for (int k = lo; k <= hi; k++) {
        if (i > mid) a[k] = aux[j++];
        else if (j > hi) a[k] = aux[i++];
        else if (aux[j] < aux[i]) a[k] = aux[j++];
        else a[k] = aux[i++];
    }

}

//merge sort algorithm - vai divindo os arrays através dos indices e no final dá merge
void sort(unsigned long long a[], unsigned long long aux[], int lo, int hi) {
    if (hi <= lo) return;
    int mid = lo + (hi - lo) / 2;
    sort(a, aux, lo, mid);
    sort(a, aux, mid + 1, hi);
    merge(a, aux, lo, mid, hi);
}

// sorted em ordem crescente
void mergeSort(unsigned long long a[],int size){
    unsigned long long aux[size];
    sort(a, aux, 0, size - 1);
}


char* key_long_2_digits_char(unsigned long long key) {
    // numero de digitos na key
    int num_digits = 0;
    unsigned long long temp = key;
    while (temp > 0) {
        num_digits++;
        temp /= 10;
    }

    // Aloca um array de caracteres para guardar os digitos
    char* digits = malloc(num_digits * sizeof(char));

    // Converte cada digito da chave para um caracter e adiciona-o
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


//Abordagem de gerar multiplos de n até encontrar um nr bipolar
unsigned long long calc_private_key_char(unsigned long long num) {
    unsigned long long mult = 0;
    char snum[100];
    unsigned long long nreturn = 0;
    int i = 2;
    int call = 0;
    while (1) {
        mult = num * i;
        itoa(mult, snum, 10);
        nreturn = isBipolar(snum);
        if (nreturn != -1) {
            //printf("%d * %d = %llu\n",num,i,mult);
            //printf("%llu\n",mult);
            return nreturn;
        }
        i++;
    }
    return -1;
}

unsigned long long calc_runlength_char(unsigned long long privkey) {
    // Cria uma string para guardar a codificação run-length
    char run_length[20];
    int index = 0;

    short digits[10] = {0};
    int num_digits = 0;
    unsigned long long temp = privkey;
    while (temp > 0) {
        short digit = temp % 10;
        digits[digit]++;
        num_digits++;
        temp /= 10;
    }

    // Codifica a private key
    for (int i = 0; i < 10; i++) {
        if (digits[i] > 0) {
            // Adiciona a contagem dos digitos ao run-length
            char digit_count[20];
            sprintf(digit_count, "%d", digits[i]);
            for (int j = 0; digit_count[j] != '\0'; j++) {
                run_length[index++] = digit_count[j];
            }
            //Adiciona o digito ao run-length
            run_length[index++] = i + '0';
            }
        }
    // null terminator
    run_length[index] = '\0';

    // Converte o run-length para um unsigned long long
    unsigned long long runlengthkey = strtoull(run_length, NULL, 10);

    return runlengthkey;
}

unsigned long long private_key_from_runlength_char(unsigned long long runlengthkey){
    int array[4];
    unsigned long long Bipolar=0;
    array[3]=runlengthkey%10;
    runlengthkey /= 10;
    array[2]=runlengthkey%10;
    runlengthkey/=10;
    array[1]=runlengthkey%10;
    runlengthkey/=10;
    array[0]=runlengthkey;


    for (int i = 0; i < array[0]; ++i) {
        Bipolar+=array[1];
        Bipolar*=10;
    }
    for (int i = 0; i < array[2]; i++) {
        Bipolar+=array[3];
        if (i!=array[2]-1)
            Bipolar*=10;
    }
    return Bipolar;
}

char **alloc_matrix_char(int nlines, int ncolumns) {
    char **matrix;
    int i;
    matrix = (char **) malloc(nlines * sizeof(char *));
    for (i = 0; i < nlines; i++) {
        matrix[i] = (char *) malloc(ncolumns * sizeof(char));
    }
    return matrix;
}

char ** store_key_char(char **matrix, int *plines,int ncolumns, unsigned long long key){
    int length = count_digits_char(key);
    int n1=0,i=0,j=0,k=0;

    while(*(matrix+j)!=NULL && *(*(matrix+j)+0)!='\0'){//    while(matrix[j]!=NULL && matrix[j][0]!='\0')
        j++;
    }
    if (j==*plines){
        printf("Preciso fazer realloc j=%d\n",j);
        int oldSize=*plines;//10+1
        int newSize=*plines+15;//20
        matrix = realloc (matrix,(newSize+1)* sizeof (char*)) ;//o +1 corresponde a ultima posição a NULL
        for (k = oldSize; k < newSize; ++k) {
            *(matrix+k)= calloc(ncolumns,sizeof (char));
        }
        *(matrix+k)=NULL;
        *plines=newSize;

    }
    for (i = length-1; i != -1; --i) {
        n1=key%10;
        key/=10;
        *(*(matrix+j)+i)='0'+n1;
    }

    return matrix;
}


int exists_key_char(char **matrix, int lines, unsigned long long key){
    int length = count_digits_char(key);
    char array[length];
    char digito[2];
    int n=0;
    for (int i = length-1; i != -1; --i) {
        n=key%10;
        key/=10;
        itoa(n,digito,10);
        array[i]=digito[0];
    }
    for (int i = 0; i < lines; ++i) {//linhas
        for (int j = 0; j < length; ++j) {//colunas
            if (matrix[i][j]!=array[j])
                break;
            if (j==length-1){
                //printf("%d\n",i);
                return i;
            }
        }
    }
    return -1;
}


unsigned long long get_private_key_char(char **matrix_kpub, char **matrix_kpriv, int lines, unsigned long long pubkey){
    unsigned long long nreturn=0;
    int posicao= exists_key_char(matrix_kpub,lines,pubkey);
    if (posicao!=-1){
        nreturn= key_digits_2_long_char(*(matrix_kpriv + posicao));
    }
    return nreturn;
}

unsigned long long get_runlength_char(char **matrix_kpriv, char **matrix_kcod, int lines, unsigned long long privkey){
    unsigned long long nreturn=0;
    int position= exists_key_char(matrix_kpriv, lines, privkey);
    if (position != -1){
        nreturn= key_digits_2_long_char(*(matrix_kcod + position));
    }
    return nreturn;
}

unsigned long long delete_key_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int lines, unsigned long long pubkey) {
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

char ** bulk_populate_public_keys_char(char **matrix_kpub, int *plines);
/* {   //gera chaves , guarda em string dinamica  e faz o copy
    unsigned long long random = new_public_key_int();
    matrix_kpub = store_key_char(matrix_kpub, plines,20 ,);
    return matrix_kpub;
}*/


char ** bulk_compute_private_keys_char(char **matrix_kpub, char **matrix_kpriv, int *plines);
 /*
  * {unsigned  long long number;
    unsigned  long long bipolar_number;
    for (int i = 0; i < *(matrix_kpub + i) != NULL; ++i) {
        if (*(*(matrix_kpub+ i) + 0) != '\0') {
            number=key_digits_2_long_char(*(matrix_kpub+ i));//converter de string para llu
            bipolar_number=calc_private_key_char(number);
            matrix_kpriv=store_key_char(matrix_kpriv, plines,20, bipolar_number);
        }
    }
    return matrix_kpriv;
}*/

char ** bulk_compute_runlengths_char(char **matrix_kpriv, char **matrix_kcod, int *plines);
/*    {   unsigned  long long number;
    unsigned  long long bipolar;
    for (int i = 0; i < *(matrix_kpriv + i) != NULL; ++i) {
        if (*(*(matrix_kpriv+ i) + 0) != '\0') {
            number = key_digits_2_long_char(*(matrix_kpriv + i));//converter de string para llu
            //number=key_digits_2_long_char(matrix_kpriv+ i);
            bipolar = calc_runlength_char(number);
            matrix_kcod = store_key_char(matrix_kcod, plines, 20, bipolar);
        }
    }
    return matrix_kcod;
}*/

char** search_private_keys_char(char **matrix_kpub, char **matrix_kpriv, int lines, unsigned long long partialpubkey){
        char *ret;
        int nd=0;
        int position=1;
        unsigned long long num=0;

        char* partialkey=key_long_2_digits_char(partialpubkey);

        for (int i = 0; i < lines; ++i) {
            ret = strstr(*(matrix_kpub+i), partialkey);
            if (ret!=NULL){
                nd++;
            }
        }
        unsigned long long  *arr = (unsigned long long *) calloc (nd, sizeof(unsigned long long));
        arr[0]=nd;
        for (int i = 0; i < lines; ++i) {
            ret = strstr(*(matrix_kpub+i), partialkey);
            if (ret!=NULL){
                //printf("%s\n",*(matrix_kpriv+i));
                num = key_digits_2_long_char(*(matrix_kpriv+i));
                arr[position]=num;
                position++;
            }
        }
        return arr;

    }

void sort_matrix_char(char **matrix, int lines, int order){
    unsigned long long arr[lines];
    for (int i = 0; i < lines; ++i) {
        arr[i]=key_digits_2_long_char(*(matrix+ i));
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
    //limpa a matriz
    for (int k = 0; k < lines; ++k) {
        *(matrix+k)= calloc(20,sizeof (char));
    }
    for (int i = 0; i < lines; ++i) {
        *(matrix+i)=key_long_2_digits_char(arr[i]);
    }

}

void sort_all_matrices_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int *plines, int order){
    sort_matrix_char(matrix_kpub,*plines,order);
    sort_matrix_char(matrix_kpriv,*plines,order);
    sort_matrix_char(matrix_kcod,*plines,order);
}

void list_keys_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int *plines, int order){
    sort_matrix_char(matrix_kpub,*plines,order);
    reset_matrix_char(matrix_kpriv,*plines);
    reset_matrix_char(matrix_kcod,*plines);
    bulk_compute_private_keys_char(matrix_kpub, matrix_kpriv, &plines);
    bulk_compute_runlengths_char(matrix_kpriv, matrix_kcod, &plines);
}

void save_txt_keys_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int lines, char filename[]){
    FILE * fp;
    fp=fopen(filename,"w");
    if(fp!=NULL){
        fprintf(fp,"Number of keys:%d\n",lines);
        fprintf(fp,"ID PUB\t\t PRIV\t\t\t RUN\n");
        for (int i = 0; *(matrix_kpub + i) != NULL; i++) {
            fprintf(fp,"%d %s\t\t %s\t\t\t %s\n",i,*(matrix_kpub + i),*(matrix_kpriv + i),*(matrix_kcod + i));
        }
        fclose(fp);
    }else{
        printf("ERRO FICHEIRO");
    }
}

void load_txt_keys_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int *plines, char filename[]){
    FILE *fp;
    fp=fopen(filename,"r");
    if(fp!=NULL){
        fscanf(fp,"%*s %*s %*s\n");
        fscanf(fp,"%*s %*s\t\t %*s\t\t\t %*s\t\t\t\n");

        char pub[100],priv[100],run[100];
        int i2=0;
        //for(int i=0;i<1500;i++){
        //fscanf(fp,"%d %s\t %s\t %s\n",&i2,pub,priv,run);
        while ((fscanf(fp,"%d %s\t\t %s\t\t\t %s\n",&i2,pub,priv,run))!=EOF){
            unsigned long long numero = strtoul (pub, NULL, 10);
            unsigned long long numero1 = strtoul (priv, NULL, 10);
            unsigned long long numero2 = strtoul (run, NULL, 10);
            //printf("[%d] %llu %llu %llu\n",i,numero,numero1,numero2);
            matrix_kpub=store_key_char(matrix_kpub, plines,20, numero);
            matrix_kpriv=store_key_char(matrix_kpriv, plines,20, numero1);
            matrix_kcod=store_key_char(matrix_kcod, plines,20, numero2);
        }
        fclose(fp);

    }
}



