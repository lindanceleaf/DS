#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

/*
malloc items
    main : Nodes_memory, channel, graph, Req_data, ac_data
    dijkstra : distance, former_point, visited
*/

int *dijkstra(int nodes_num, int **graph, int **channel, int *memory, int start, int end){
    int *distance = malloc(nodes_num * sizeof(int));
    int *former_point = malloc(nodes_num * sizeof(int));
    bool *visited = malloc(nodes_num * sizeof(bool));

    for(int i = 0; i < nodes_num; i++){
        distance[i] = INT_MAX;
        former_point[i] = -1;
        visited[i] = false;
    }
    
    distance[start] = 0;
    for(int i = 0; i < nodes_num - 1; i++){
        int min_nodes = -1;
        int min_distance = INT_MAX;

        // find the min_distance nodes that is unvisited
        for(int j = 0; j < nodes_num; j++){
            if(distance[j] < min_distance){
                min_distance = distance[j];
                
            }
        }

        // update the distance that connect to the min_node

    }
    
}

int main(){
    int Nodes_num, Links_num, Req_num;
    scanf("%d %d %d", &Nodes_num, &Links_num, &Req_num);

    // input and storage quantum memories of every node
    int *Nodes_memory = malloc(Nodes_num * sizeof(int));
    for(int i = 0; i < Nodes_num; i++){
        int Nodes_ID, Memory;
        scanf("%d %d", &Nodes_ID, &Memory);
        Nodes_memory[Nodes_ID] = Memory;
    }

    // input channel and build graph
    int **channel = malloc(Nodes_num * sizeof(int *));
    int **graph = malloc(Nodes_num * sizeof(int *));
    for(int i = 0; i < Nodes_num; i++){
        channel[i] = malloc(Nodes_num * sizeof(int));
        graph[i] = malloc(Nodes_num * sizeof(int));
    }
        // initialize
    for(int i = 0; i < Nodes_num; i++){
        for(int j = 0; j < Nodes_num; j++){
            channel[i][j] = channel[j][i] = 0;
            graph[i][j] = graph[j][i] = INT_MAX;
        }
    }
        // build
    for(int i = 0; i < Links_num; i++){
        int Links_ID, LinksEnd1, LinksEnd2, channel_num;
        scanf("%d %d %d %d", &Links_ID, &LinksEnd1, &LinksEnd2, &channel_num);
        channel[LinksEnd1][LinksEnd2] = channel[LinksEnd2][LinksEnd1] = channel_num;
        graph[LinksEnd1][LinksEnd2] = graph[LinksEnd2][LinksEnd1] = 1;
    }

    // storage request data
    int **Req_data = malloc(Req_num * sizeof(int *));
    for(int i = 0; i < Req_num; i++){
        Req_data = malloc(2 * sizeof(int));// 2 means source and destination
    }
    for(int i = 0; i < Req_num; i++){
        int Req_ID, Req_Src, Req_Dst;
        scanf("%d %d %d", &Req_ID, &Req_Src, &Req_Dst);
        Req_data[Req_ID][0] = Req_Src;
        Req_data[Req_ID][1] = Req_Dst;
    }

    int **ac_data = malloc(Req_num * sizeof(int *));
    for(int i = 0; i < Req_num; i++){
        ac_data[i] = malloc(Nodes_num * sizeof(int));
    }
    int accepted_number = 0;
    int accepted_ID[Nodes_num];
    int accepted_length[Nodes_num];
}