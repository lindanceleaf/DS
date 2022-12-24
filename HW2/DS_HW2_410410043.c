#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
We divide ResourceX into several area.
Then, start to reallocate those rectangle into every area.
*/

int main(){
    int ResourceX, ResourceY, Users_num;
    scanf("%d %d %d", &ResourceY, &ResourceX, &Users_num);

    int UserID[Users_num];
    int **shape_data = malloc(Users_num * sizeof(int *));
    for(int i = 0; i < Users_num; i++){
        shape_data[i] = calloc(5, sizeof(int));
    }

    // input users' data
    for(int i = 0; i < Users_num; i++){
        char original_string[30];
        scanf("%d ", &UserID[i]);
        fgets(original_string, 30, stdin);

        // prepare for using strtok
        // use strtok_r to do nested strtok
        const char delimiter1[2] = " ";
        const char delimiter2[2] = "x";
        char *end_str1;
        char *token1 = strtok_r(original_string, delimiter1, &end_str1);
        while(token1 != NULL){
            char *end_str2;
            char *token2 = strtok_r(token1, delimiter2, &end_str2);

            // Because x*y is a constant value 16, we can know x by x = 16 / y
            // Use 0/1 to know every users' acceptable shape
            int get_y = atoi(token2);
            switch(get_y){
                case 1:
                    shape_data[i][0] = 1;
                    break;
                case 2:
                    shape_data[i][1] = 1;
                    break;
                case 4:
                    shape_data[i][2] =  1;
                    break;
                case 8:
                    shape_data[i][3] = 1;
                    break;
                case 16:
                    shape_data[i][4] = 1;
                    break;
            }

            token1 = strtok_r(NULL, delimiter1, &end_str1);
        }
    }

    int ac_shape[Users_num];
    int place[Users_num][2]; // to store the plcae where to put the ac_data
    int ac_num = 0;

    int block_num = ResourceX % 16 == 0 ? ResourceX / 16 : ResourceX / 16 + 1;
    int now_block = 0;
    int *ac_user = malloc(Users_num * sizeof(int));
    int now_x = 0, now_y = 0;
    int x_value[5] = {16, 8, 4, 2, 1};
    int y_value[5] = {1, 2, 4, 8, 16};
    bool *is_used = (bool *)calloc(Users_num, sizeof(bool));
    int border_x = 16 * (now_block + 1), border_y = ResourceY;
    bool is_last_block = false;
    
    // algorithm for the block not the last one
    int end_shape = -1;
    for(int choose_shape = 0; choose_shape < 5; choose_shape++){
        for(int user = 0; user < Users_num; user++){
            if(!is_used[user] && shape_data[user][choose_shape]){
                if(now_x + x_value[choose_shape] <= border_x && now_y + y_value[choose_shape] <= border_y){
                    place[ac_num][0] = now_x;
                    place[ac_num][1] = now_y;
                    ac_shape[ac_num] = choose_shape;
                    now_x += x_value[choose_shape];
                    ac_user[ac_num] = user;
                    is_used[user] = true;
                    ac_num++;
                }
                else if(now_x + x_value[choose_shape] > border_x){
                    now_x = now_block * 16;
                    now_y += y_value[choose_shape];
                    // user--;
                }
                else{
                    now_block++;
                    // user--;
                    if(now_block == block_num - 1){
                        is_last_block = true;
                        end_shape = choose_shape;
                        break;
                    }
                    now_x = now_block * 16;
                    now_y = 0;
                }
            }
        }
        if(is_last_block) break;
        now_x = 16 * now_block;
        now_y += y_value[choose_shape];
    }
    
    // algorithm for the last block
    now_x = 16 * (block_num - 1);
    now_y = 0;
    for(int choose_shape = end_shape; choose_shape < 5; choose_shape++){
        if(x_value[choose_shape] > (ResourceX - (block_num - 1) * 16)) continue;
        for(int user = 0; user < Users_num; user++){
            if(!is_used[user] && shape_data[user][choose_shape]){
                if(now_x + x_value[choose_shape] <= ResourceX && now_y + y_value[choose_shape] <= ResourceY){
                    place[ac_num][0] = now_x;
                    place[ac_num][1] = now_y;
                    ac_user[ac_num] = user;
                    is_used[user] = true;
                    ac_shape[ac_num] = choose_shape;
                    ac_num++;
                    now_x += x_value[choose_shape];
                }
                else if(now_x + x_value[choose_shape] > ResourceX){
                    user--;
                    now_y += y_value[choose_shape];
                    now_x = 16 * now_block;
                }
                else break;
            }
        }
        now_x = 16 * (block_num - 1);
        now_y += y_value[choose_shape];
    }

    printf("%d\n", ac_num);
    for(int i = 0; i < ac_num; i++){
        printf("%d ", ac_user[i]);
        switch(ac_shape[i]){
            case 0: printf("1x16 "); break;
            case 1: printf("2x8 " ); break;
            case 2: printf("4x4 "); break;
            case 3: printf("8x2 "); break;
            case 4: printf("16x1 "); break;
        }
        printf("%d %d\n", place[i][1], place[i][0]);
    }
}