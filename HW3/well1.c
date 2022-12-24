#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>

int main(){
    int Nodes_num, threshold;
    scanf("%d %d", &Nodes_num, &threshold);
    
    // input nodes data
    double Nodes_data[Nodes_num][2];
    for(int i = 0; i < Nodes_num; i++){
        int ID;
        scanf("%d", &ID);
        scanf("%lf %lf",&Nodes_data[ID][0], &Nodes_data[ID][1]); // [0] is x, [1] is y
    }

    // build the distance table
    double **distance = malloc(Nodes_num * sizeof(double *));
    for(int i = 0; i < Nodes_num; i++) distance[i] = calloc(Nodes_num, sizeof(double));
    for(int i = 0; i < Nodes_num - 1; i++){
        for(int j = i + 1; j < Nodes_num; j++){
            double x = Nodes_data[i][0] - Nodes_data[j][0];
            double y = Nodes_data[i][1] - Nodes_data[j][1];
            distance[i][j] = distance[j][i] = sqrt(x * x + y * y);
        }
    }

    bool visited[Nodes_num]; // record the Nodes whether is visited
    int next_point[Nodes_num]; // record the next point of every nodes
    for(int i = 0; i < Nodes_num; i++){
        visited[i] = false;
        next_point[i] = -1;
    }


    int UAV_cnt = 0;
    int start_point[Nodes_num];
    while(1){
        int start = -1;
        // find the start_point
        for(int i = 0; i < Nodes_num; i++){
            if(visited[i] == false){
                start = i;
                start_point[UAV_cnt] = i;
                visited[i] = true;
                break;
            }
        }
        if(start == -1) break;
        
        double dis = (double)threshold;
        while(1){
            double min_distance = (double)INT_MAX;
            int min_point = -1;
            for(int i = 0; i < Nodes_num; i++){
                if(visited[i] == false && distance[start][i] < min_distance){
                    min_distance = distance[start][i];
                    min_point = i;
                }
            }
            if(min_point == -1) break;

            if(dis - min_distance - distance[min_point][start_point[UAV_cnt]] >= 0.0){
                dis -= min_distance;
                next_point[start] = min_point;
                start = min_point;
                visited[min_point] = true;
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
        printf("%d", start_point[i]);
        int next = start_point[i];
        while(1){
            if(next_point[next] != -1){
                next = next_point[next];
                printf(" %d", next);
            }
            else{
                printf("\n");
                break;
            }
        }
    }
}