#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

int *dijkstra(int node_num, int **graph, int start){
    int distance[node_num];
    bool visited[node_num];
    int *former_point = malloc(node_num * sizeof(int));

    // initialize
    for(int i = 0; i < node_num; i++){
        distance[i] = INT_MAX;
        visited[i] = false;
        former_point[i] = -1;
    }

    // dijkstra algorithm
    distance[start] = 0;
    for(int i = 0; i < node_num - 1; i++){
        int min_distance = INT_MAX;
        int min_nodes = node_num;

        for(int j = 0; j < node_num; j++){
            if(distance[j] < min_distance && visited[j] == false){
                min_distance = distance[j];
                min_nodes = j;
            }
        }
        if(min_distance == INT_MAX) break; // find the path is dead end

        // update distance
        for(int j = 0; j < node_num; j++){
            if(graph[min_nodes][j] != INT_MAX && visited[j] == false && distance[j] == INT_MAX){
                // distance == INT_MAX mean that the distance haven't been changed
                distance[j] = distance[min_nodes] + 1; 
                former_point[j] = min_nodes;
            }
        }
        visited[min_nodes] = true;
    }
    return former_point;
}

int main(){
    int Nodes_num, Links_num, Req_num;
    scanf("%d %d %d", &Nodes_num, &Links_num, &Req_num);

    // input and storage quantum memories of every node
    int Nodes_memory[Nodes_num];
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
        // initialize channel and graph
    for(int i = 0; i < Nodes_num; i++){
        for(int j = 0; j < Nodes_num; j++){
            channel[i][j] = channel[j][i] = 0;
            graph[i][j] = graph[j][i] = INT_MAX;
        }
    }
        // build channel and graph
    for(int i = 0; i < Links_num; i++){
        int Links_ID, LinksEnd1, LinksEnd2, channel_num;
        scanf("%d %d %d %d", &Links_ID, &LinksEnd1, &LinksEnd2, &channel_num);
        channel[LinksEnd1][LinksEnd2] = channel[LinksEnd2][LinksEnd1] = channel_num;
        graph[LinksEnd1][LinksEnd2] = graph[LinksEnd2][LinksEnd1] = 1;
    }

    // storage request data
    int Req_data[Req_num][2];// 2 mean source and destination
    for(int i = 0; i < Req_num; i++){
        int Req_ID, Req_Src, Req_Dst;
        scanf("%d %d %d", &Req_ID, &Req_Src, &Req_Dst);
        Req_data[Req_ID][0] = Req_Src;
        Req_data[Req_ID][1] = Req_Dst;
    }

    // record accepted data(including ID, length, and path)
    int **ac_data = malloc(Req_num * sizeof(int *));
    for(int i = 0; i < Req_num; i++){
        ac_data[i] = calloc(Nodes_num, sizeof(int));
    }
    int accepted_number = 0;
    int accepted_ID[Nodes_num];
    int accepted_length[Nodes_num];
    for(int i = 0; i < Req_num; i++){
        int *former_point = dijkstra(Nodes_num, graph, Req_data[i][0]);

        // build the shortest path
        int path_len = 0;
        int *shortest_path = malloc(Nodes_num * sizeof(int));
        // start from the last point and build the path by the former_point
        int recent_point = Req_data[i][1];
        shortest_path[0] = Req_data[i][1];
        bool can_to_dst = true;
        while(1){
            shortest_path[path_len + 1] = former_point[recent_point];
            recent_point = former_point[recent_point];
            path_len ++;
            if(recent_point == -1){
                can_to_dst = false;
                break;
            }
            else if(recent_point == Req_data[i][0]) break;
        }
        
        if(can_to_dst){
            // check the resoureces
            bool is_accepted = true;

            // src's and dst's quantum memories need at least 1
            if(Nodes_memory[shortest_path[0]] < 1 || Nodes_memory[shortest_path[path_len]] < 1) is_accepted = false;
            //  relay_point's quantum memories need at least 2
            for(int j = 1; j < path_len; j++){
                if(Nodes_memory[shortest_path[j]] < 2) is_accepted = false;
            }
            // every link that the shortest path pass need to at least 1 channel
            for(int j = 1; j < path_len; j++){
                if(channel[shortest_path[j]][shortest_path[j-1]] < 1) is_accepted = false;
            }

            if(is_accepted){
                accepted_ID[accepted_number] = i;
                accepted_length[accepted_number] = path_len;
                for(int j = 0; j < path_len + 1; j++){
                    ac_data[accepted_number][j] = shortest_path[path_len - j];
                }
                accepted_number ++;

                // update the new channel and quantum_memories
                Nodes_memory[shortest_path[0]] --;
                Nodes_memory[shortest_path[path_len]] --;
                for(int j = 1; j < path_len; j++){
                    Nodes_memory[shortest_path[j]] -= 2;
                }
                for(int j = 1; j < path_len + 1; j++){
                    channel[shortest_path[j]][shortest_path[j-1]] --;
                    channel[shortest_path[j-1]][shortest_path[j]] --;
                }

                // build new graph to create more accepted_path
                for(int j = 0; j < path_len + 1; j++){
                    if(Nodes_memory[shortest_path[j]] <= 0){
                        for(int k = 0; k < Nodes_num; k++){
                            graph[shortest_path[j]][k] = INT_MAX;
                            graph[k][shortest_path[j]] = INT_MAX;
                        }
                    }
                }
                for(int j = 1; j < path_len + 1; j++){
                    if(channel[shortest_path[j]][shortest_path[j-1]] <= 0){
                        graph[shortest_path[j]][shortest_path[j-1]] = INT_MAX;
                        graph[shortest_path[j-1]][shortest_path[j]] = INT_MAX;
                    }
                }
            }
        }
        free(former_point);
        free(shortest_path);
    }
    
    // output the data
    printf("%d\n", accepted_number);
    for(int i = 0; i < accepted_number; i++){
        printf("%d ", accepted_ID[i]);
        for(int j = 0; j < accepted_length[i] + 1; j++){
            printf("%d ", ac_data[i][j]);
        }
        printf("\n");
    }
    free(ac_data);
}