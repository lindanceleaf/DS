#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// struct that form merkle tree
typedef struct node{
    unsigned long hash_value;
    struct node *left;
    struct node *right;
} node;

// hash_value to 4 char
char *HashValue_to_char(unsigned long hash_value){
    /* char *hash_char = malloc(4 * sizeof(unsigned char));
    for(int i = 3; i >= 0; i--){
        hash_char[i] = hash_value % 256;
        hash_value /= 256;
    }
    return hash_char; */
    int data[15];
    memset(data, 0, 15 * sizeof(int));
    int cnt = 0;
    while(hash_value != 0){
        data[cnt] = hash_value % 10;
        hash_value /= 10;
        cnt++;
    }
    char *Hash_String = malloc(cnt * sizeof(char));
    for(int i = cnt - 1; i >= 0; i--){
        Hash_String[cnt - 1 - i] = data[i] + 48;
    }
    return Hash_String;
}

// Hashing Function (MurmurOAAT32)
unsigned char *hashing(char *key){
    unsigned long h = 3323198485ul;
    for(; *key ; ++key){
        h ^= *key;
        h *= 0x5bd1e995;
        h ^= h >> 15;
    }

    return h;
}


int main(){
    int Str_num, Str_MaxLen;
    scanf("%d %d", &Str_num, &Str_MaxLen);

    unsigned char data[Str_num][Str_MaxLen + 1];
    for(int i = 0; i < Str_num; i++){
        scanf("%s", data[i]);
    }

    node leaves[Str_num];
    for(int i = 0; i < Str_num; i++){
        unsigned char *h_v = malloc(4 * sizeof(unsigned char));
        h_v = hashing(data[i]);
        strcpy(leaves[i].hash_value, h_v);
        leaves[i].left = NULL;
        leaves[i].right = NULL;
        printf("%d", i);
        for(int j = 0; j < 4; j++){
            printf(" %d", leaves[i].hash_value[j]);
        }
        printf("\n");
    }


}