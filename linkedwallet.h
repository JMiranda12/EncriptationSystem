
#ifndef ENCRIPTATIONSYSTEM_LINKEDWALLET_H
#define ENCRIPTATIONSYSTEM_LINKEDWALLET_H


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct wallet {
    char **matpubchars;
    char **matprivchars;
    char **matrunchars;
    char **matpubints;
    char **matprivints;
    char **matrunints;
    int lines;
    int columns;
}WALLET;

typedef struct wallet_node {
    WALLET info;
    struct wallet *pnext;
}WALLET_NODE;

typedef struct wallet_ll{
    WALLET_NODE *phead;
    WALLET_NODE *ptail;
    int n_nodes;
}WALLET_LL;


typedef struct client{
    char* name;
    char* email;
    WALLET_LL *wallet_node;
}CLIENT;

typedef struct client_node{
    CLIENT cliente;
    struct client_node *pnext;
}CLIENT_NODE;

typedef struct client_node_ll{
    CLIENT_NODE *phead;
    CLIENT_NODE *ptail;
    int n_clientes;
}CLIENT_NODE_LL;











#endif //ENCRIPTATIONSYSTEM_LINKEDWALLET_H
