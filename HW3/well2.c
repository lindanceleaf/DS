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
    // find the first start point
    // find the max distance and choose one of the both ends to be the start point
    double max_distance = distance[0][1];
    int max_point = 0;
    for(int i = 0; i < Nodes_num - 1; i++){
        for(int j = i + 1; j < Nodes_num; j++){
            if(distance[i][j] > max_distance){
                max_distance = distance[i][j];
                max_point = i;
            }
        }
    }
    start_point[0] = max_point;
    visited[max_point] = true;
    int start = start_point[0];
    while(1){
        double dis = (double)threshold;
        while(1){
            // find the nearest point
            double min_distance = (double)INT_MAX;
            int nearest_point = -1;
            for(int i = 0; i < Nodes_num; i++){
                if(visited[i] == false && distance[start][i] < min_distance){
                    min_distance = distance[start][i];
                    nearest_point = i;
                }
            }
            if(nearest_point == -1) break;
            
            // check whether the distance is over threshold
            if(dis - min_distance - distance[nearest_point][start_point[UAV_cnt]] >= 0.0){
                dis -= min_distance;
                next_point[start] = nearest_point;
                start = nearest_point;
                visited[nearest_point] = true;
            }
            else{
                UAV_cnt++;
                break;
            }
        }
        // find the next start_point
        // find the farthest point from the last start point
        double max_distance = 0.0;
        int max_point = -1;
        for(int i = 0; i < Nodes_num; i++){
            if((start_point[UAV_cnt - 1] == i) || visited[i]) continue;
            double far_distance = distance[start_point[UAV_cnt - 1]][i];
            if(far_distance > max_distance){
                max_distance = far_distance;
                max_point = i;
            }
        }
        start = max_point;
        if(start == -1) break;
        visited[start] = true;
        start_point[UAV_cnt] = start;
    }
    UAV_cnt++;

    // output the result
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