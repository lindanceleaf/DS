#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// struct that form merkle tree
typedef struct node{
    unsigned long hash_value;
    struct node *left;
    struct node *right;
} node;

// turn hash value to string
char *HashValue_to_char(unsigned long hash_value){
    char *Hash_String = malloc(15 * sizeof(char));
    itoa(hash_value, Hash_String, 10);
    return Hash_String;
}

// Hashing Function (MurmurOAAT32)
unsigned long hashing(char *key){
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

    char data[Str_num][Str_MaxLen + 1];
    for(int i = 0; i < Str_num; i++){
        scanf("%s", data[i]);
    }

    node leaves[Str_num];
    for(int i = 0; i < Str_num; i++){
        leaves[i].hash_value = hashing(data[i]);
        leaves[i].left = NULL;
        leaves[i].right = NULL;
        printf("%lu\n", leaves[i].hash_value);
    }
}