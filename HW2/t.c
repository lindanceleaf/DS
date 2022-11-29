#include <stdio.h>
#include <stdlib.h>

int main(){
    int **ptr = malloc(5 * sizeof(int *));
    for(int i = 1; i <= 5; i++){
        ptr[i] = malloc(i * sizeof(int));
    }
    for(int i = 1; i <= 5; i++){
        for(int j = 1; j <= i; j++){
            ptr[i][j] = j;
        }
    }
    for(int i = 1; i <= 5; i++){
        for(int j = 1; j <= i; j++){
            printf("%d ", ptr[i][j]);
        }
        printf("\n");
    }
}