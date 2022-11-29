#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int result_cnt = 0, total = 0;

typedef struct{
    int Y[5];
    int X[5];
    int cnt;
}shape;

int main(){
    int Resource_Y, Resource_X, Users;
    scanf("%d %d %d\n", &Resource_Y, &Resource_X, &Users);

    shape Shape[Users];
    for(int i = 0;i < Users;i++){//input
        int UserId = 0;
        char str[25];
        scanf("%d ", &UserId);
        fgets(str, 24, stdin);
        
        char *token, *ptr = str;
        char *token_axis;
        token = strtok_r(ptr, " ", &ptr);
        int cnt = 0;
        while(token != NULL){
            token_axis = strtok_r(token, "x", &token);
            Shape[i].Y[cnt] = atoi(token_axis);
            Shape[i].X[cnt] = atoi(token);
            token = strtok_r(NULL, " ", &ptr);
            cnt++;
        }
        Shape[i].cnt = cnt;
        total += cnt;
    }

    int used = 0;

    int **result = malloc(total * sizeof(int*));
    for(int i = 0;i < total;i++){
        result[i] = malloc(5 * sizeof(int));
    }
    for(int i = 0;i < total;i++){
        result[i][0] = -1;
    }

    for(int i = 0;i < 5;i++){
        for(int j = 0;j < Users;j++){
            if(Shape[j].cnt <= i) continue;
            if(Shape[j].X[i] + used <= Resource_X){
                result[result_cnt][0] = j;
                result[result_cnt][1] = Shape[j].Y[i];
                result[result_cnt][2] = Shape[j].X[i];
                result[result_cnt][3] = 0;
                result[result_cnt][4] = used;
            }
            else continue;
            used += Shape[j].X[i];
            result_cnt++;
        }
    }

    printf("%d\n", result_cnt);
    for(int i = 0;i < result_cnt;i++){
        printf("%d %dx%d %d %d\n", result[i][0], result[i][1], result[i][2], result[i][3], result[i][4]);
    }

    free(result);
    return 0;
}