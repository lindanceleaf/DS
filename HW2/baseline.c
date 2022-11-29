#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int ResourceX, ResourceY, Users_num;
    scanf("%d %d %d", &ResourceY, &ResourceX, &Users_num);

    int UserID[Users_num];
    int **shape_data = malloc(Users_num * sizeof(int *));
    int shape_num[Users_num];
    // 
    for(int i = 0; i < Users_num; i++){
        char original_string[30];
        scanf("%d ", &UserID[i]);
        fgets(original_string, 30, stdin);

        shape_num[i] = 0;
        int original_string_len = strlen(original_string);
        for(int j = 0; j < original_string_len; j++){
            if(original_string[j] == 'x') shape_num[i] ++;
        }

        shape_data[i] = malloc(shape_num[i] * sizeof(int));

        const char delimiter1[2] = " ";
        const char delimiter2[2] = "x";
        char *end_str1;
        char *token1 = strtok_r(original_string, delimiter1, &end_str1);
        int cnt = 0; // to know where to store data
        while(token1 != NULL){
            char *end_str2;
            char *token2 = strtok_r(token1, delimiter2, &end_str2);

            // Because x*y is a constant value 16, we can know x by y
            shape_data[i][cnt] = atoi(token2); // the number is y
            cnt ++;

            token1 = strtok_r(NULL, delimiter1, &end_str1);
        }

    }
    int ac_num = 0;
    int ac_ID[Users_num];
    int ac_data[Users_num];
    int ac_position[Users_num][2]; 
    int x_sum = 0;
    for(int i = 0; i < Users_num; i++){
        int shape_y = shape_data[i][0];
        int shape_x = 16 / shape_data[i][0];
        if(shape_y <= ResourceY && x_sum + shape_x <= ResourceX){
            ac_ID[ac_num] = i;
            ac_data[ac_num] = shape_y;
            ac_position[ac_num][0] = 0; // y
            ac_position[ac_num][1] = x_sum; // x
            x_sum += shape_x;
            ac_num ++;
        }
    }
    printf("%d\n", ac_num);
    for(int i = 0; i < ac_num; i++){
        printf("%d ", ac_ID[i]);
        printf("%dx%d ", ac_data[i], 16/ac_data[i]);
        printf("%d %d\n", ac_position[i][0], ac_position[i][1]);
    }
    
}