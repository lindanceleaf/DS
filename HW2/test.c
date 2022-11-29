#include <stdio.h>
#include <stdlib.h>


int main(){
    int n;
    scanf("%d", &n);
    int ***data = malloc(n * sizeof(int **));
    for(int i = 0; i < n; i++){
        data[i] = malloc(n * sizeof(int *));
        for(int j = 0; j < n; j++){
            data[i][j] = calloc(n, sizeof(int));
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < n; k++){
                printf("%d ", data[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }
}



/*
int main(){
    int n;
    scanf("%d", &n);
    int **data = malloc(n * sizeof(int *));
    for(int i = 0; i < n; i++){
        data[i] = malloc(n * sizeof(int));
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            data[i][j] = 0;
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%d ", data[i][j]);
        }
        printf("\n");
    }
}
*/