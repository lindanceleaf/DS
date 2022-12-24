#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

int main(){
    int Nodes_num, threshold;
    scanf("%d %d", &Nodes_num, &threshold);

    double Nodes_data[Nodes_num][2];
    for(int i = 0; i < Nodes_num; i++){
        int ID;
        scanf("%d", &ID);
        scanf("%lf %lf",&Nodes_data[ID][0], &Nodes_data[ID][1]); // [0] is x, [1] is y
    }

    double **distance = malloc(Nodes_num * sizeof(double *));
    for(int i = 0; i < Nodes_num; i++) distance[i] = calloc(Nodes_num, sizeof(double));
    for(int i = 0; i < Nodes_num - 1; i++){
        for(int j = i + 1; j < Nodes_num; j++){
            double x = Nodes_data[i][0] - Nodes_data[j][0];
            double y = Nodes_data[i][1] - Nodes_data[j][1];
            distance[i][j] = distance[j][i] = sqrt(x * x + y * y);
        }
    }

    bool visited[Nodes_num];
    int start_point[Nodes_num];
    int next_point[Nodes_num];
    int UAV_cnt = 0;
    for(int i = 0; i < Nodes_num; i++){
        visited[i] = false;
        next_point[i] = -1;
    }
    while(1){
        int start = -1;
        for(int i = 0; i < Nodes_num; i++){
            if(visited[i] == false){
                start = i;
                visited[start] = true;
                start_point[UAV_cnt] = start;
                break;
            }
        }
        if(start == -1) break;

        double dis = (double)threshold / 2;
        while(1){
            // find the minimum distance
            double min_distance = (double)INT_MAX; // 1e9
            int min_point = -1;
            for(int i = 0; i < Nodes_num; i++){
                if(visited[i] == true) continue;
                if(distance[i][start] < min_distance){
                    min_distance = distance[i][start];
                    min_point = i;
                }
            }
            if(min_point == -1) break;

            if(dis - min_distance >= 0.0){
                dis -= min_distance;
                next_point[start] = min_point;
                visited[min_point] = true;
                start = min_point;
            }
            else{
                UAV_cnt++;
                break;
            }
        }
    }
    UAV_cnt++;

    printf("%d\n", UAV_cnt);
    for(int i = 0; i < UAV_cnt; i++){
        printf("%d ", i);
        int point = start_point[i];
        while(1){
            printf("%d", point);
            if(next_point[point] == -1){
                printf("\n");
                break;
            }
            else{
                point = next_point[point];
                printf(" ");
            }
        }
    }
}