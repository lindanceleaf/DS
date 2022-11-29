#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int ResourceX, ResourceY, Users_num;
    scanf("%d %d %d", &ResourceX, &ResourceY, &Users_num);

    int **resource = malloc(ResourceX * sizeof(int *));
    for(int i = 0; i < ResourceX; i++){
        resource[i] = calloc(ResourceY, sizeof(int));
    }

    // storage the request data
        // declare variable
    int User_ID;
    char original_string[1000];
    //int shape_num[Users_num];
    int ***data = malloc(Users_num * sizeof(int **));
    
    for(int i = 0; i < Users_num; i++){
        // input every request
        scanf("%d ", &User_ID);
        fgets(original_string, 1000, stdin);

        const char delimiter[2] = " ";
        int str_len = strlen(original_string);
        int cnt = 0;
        for(int j = 0; j < str_len; j++){
            if(original_string[j] == 'x') cnt++;
        }
        ///shape_num[i] = cnt;
        data[i] = malloc(cnt * sizeof(int *));
        for(int j = 0; j < cnt; j++){
            data[i][j] = calloc(2, sizeof(int));
        }

        char *end_str1;
        char *token = strtok_r(original_string, delimiter, &end_str1);
        int shape_order = 0;
        while(token != NULL){
            char temp[25];
            strcpy(temp, token);
            
            char *temp_token;
            char *end_str2;
            const char temp_delimiter[2] = "x";
            int t;
            temp_token = strtok_r(temp, temp_delimiter, &end_str2);
            t = atoi(temp_token);
            data[i][shape_order][0] = t;
            //printf("%d\n", t); 
            temp_token = strtok_r(NULL, temp_delimiter, &end_str2);
            t = atoi(temp_token);
            data[i][shape_order][1] = t;
            //printf("%d\n", t);
            shape_order ++;

            token = strtok_r(NULL, delimiter, &end_str1);
        }
    }

    int accepted_num = 0;
    int *accepted_ID = malloc(Users_num * sizeof(int));
    int **accepted_place = malloc(Users_num * sizeof(int *));
    for(int i = 0; i < Users_num; i++){
        accepted_place[i] = malloc(2 * sizeof(int));
    }
    int used_place = 0;
    int cnt = 0;
    while(1){
        if(used_place + data[cnt][0][1] <= ResourceY){
            accepted_ID[accepted_num] = cnt;
            accepted_place[accepted_num][0] = 0;
            accepted_place[accepted_num][1] = used_place;
            accepted_num ++;
            used_place += data[cnt][0][1];
        }
        else break;
        cnt ++;
        if(cnt == Users_num) break;
    }
    printf("%d\n", accepted_num);
    for(int i = 0; i < accepted_num; i++){
        printf("%d ", accepted_ID[i]);
        printf("%dx%d ", data[accepted_ID[i]][0][0], data[accepted_ID[i]][0][1]);
        printf("%d %d\n", accepted_place[i][0], accepted_place[i][1]);
    }
}