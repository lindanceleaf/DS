#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

int Nodes_num, Links_num, Req_num;

int *dijkstra(int graph[Nodes_num][Nodes_num], int start){
    int distance[Nodes_num];
    int *former_point;

    former_point = malloc(Nodes_num * sizeof(int));
    for(int i = 0;i < Nodes_num; i++){
        distance[i] = INT_MAX;
        former_point[i] = -1;
    }
    
    distance[start] = 0;
    bool visited[Nodes_num];
    for(int i = 0; i < Nodes_num; i++){
        visited[i] = false;
    }
    for(int i = 0; i < Nodes_num - 1;i++){
        int min_distance = INT_MAX, min_Nodes = Nodes_num;

        // find the unvisited and min_distance point
        for(int j = 0; j < Nodes_num; j++){
            if(visited[j] == false){
                if(distance[j] < min_distance){
                    min_distance = distance[j];
                    min_Nodes = j;
                }
            }
        }

        // update the shortest distance
        for(int j = 0; j < Nodes_num; j++){
            if(visited[j] == false && graph[min_Nodes][j] < INT_MAX && distance[j] == INT_MAX){
                distance[j] = min_distance + graph[min_Nodes][j];
                former_point[j] = min_Nodes;
            }
        }
        visited[min_Nodes] = true;
    }
    return former_point;
}

int main(){
    scanf("%d %d %d", &Nodes_num, &Links_num, &Req_num);
    // input & build every nodes' quantum merories
    int Nodes_Merory[Nodes_num];
    int NodeID, Memories;
    for(int i = 0;i < Nodes_num; i++){
        scanf("%d %d", &NodeID, &Memories);
        Nodes_Merory[NodeID] = Memories;
    }

    // input graph & channel_num
        // initialize
    int graph[Nodes_num][Nodes_num];
    int channel[Nodes_num][Nodes_num];
    for(int i = 0; i < Nodes_num; i++){
        for(int j = 0; j < Nodes_num; j++){
            graph[i][j] = INT_MAX;
            channel[i][j] = 0;
        }
    }
        // build
    int LinkID, End1, End2, Channels;
    for(int i = 0;i < Links_num; i++){
        scanf("%d %d %d %d", &LinkID, &End1, &End2, &Channels);
        graph[End1][End2] = 1;
        graph[End2][End1] = 1;
        channel[End1][End2] = Channels;
        channel[End2][End1] = Channels;
    }

    int ReqID, ReqSrc, ReqDst;
    int Req_list[Req_num][2];
    for(int i = 0; i < Req_num; i++){
        scanf("%d %d %d", &ReqID, &ReqSrc, &ReqDst);
        Req_list[ReqID][0] = ReqSrc;
        Req_list[ReqID][1] = ReqDst;
    }

    int accepted_number = 0;
    int **ac_data = malloc(Req_num * sizeof(int*));
    for(int i = 0; i < Req_num; i++){
        ac_data[i] = calloc(Nodes_num, sizeof(int));
    }
    int *ac_ID = calloc(Req_num, sizeof(int));
    int ac_path_len[Nodes_num];
    
    for(int i = Req_num - 1;i >= 0; i--){
        int *former_point = dijkstra(graph, Req_list[i][0]);

        int shortest_path[Nodes_num];
        shortest_path[0] = Req_list[i][1];
        int path_len;
        for(path_len = 1;; path_len++){
            shortest_path[path_len] = former_point[shortest_path[path_len-1]];
            if(shortest_path[path_len] == Req_list[i][0]) break;
        }
        free(former_point);

        bool if_ac = true;
        if(Nodes_Merory[shortest_path[0]] < 1 || Nodes_Merory[shortest_path[path_len]] < 1) if_ac = false;
        for(int j = 1; j < path_len; j++){
            if(Nodes_Merory[shortest_path[j]] < 2) if_ac = false;
        }
        for(int j = 0; j < path_len; j++){
            if(channel[shortest_path[j]][shortest_path[j + 1]] < 1) if_ac = false;
        }
        
        if(if_ac == true){
            ac_ID[accepted_number] = i;
            for(int j = path_len; j >= 0; j--){
                ac_data[accepted_number][path_len - j] = shortest_path[j];
            }
            ac_path_len[accepted_number] = path_len;
            Nodes_Merory[shortest_path[0]] --;
            Nodes_Merory[shortest_path[path_len]] --;
            for(int j = 1; j < path_len; j++){
                Nodes_Merory[shortest_path[j]] -= 2;
            }
            for(int j = 0; j < path_len; j++){
                channel[shortest_path[j]][shortest_path[j + 1]] --;
                channel[shortest_path[j + 1]][shortest_path[j]] --;
            }
            accepted_number ++;
        }
    }
    
    printf("%d\n", accepted_number);
    for(int i = accepted_number - 1; i >= 0; i--){
        printf("%d ", ac_ID[i]);
        for(int j = 0; j < ac_path_len[i] + 1; j++){
            printf("%d ", ac_data[i][j]);
        }
        printf("\n");
    }
    free(ac_ID);
    free(ac_data);
}