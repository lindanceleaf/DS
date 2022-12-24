#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<stdbool.h>

const int inf = INT_MAX;
int node_num, link_num, req_num;

int *find_path(int route[node_num], int src, int dst){
    int *path = malloc(node_num * sizeof(int));
    for(int i = 0;i < node_num;i++){
        path[i] = -1;
    }

    int past = dst;
    int iter = 0;
    while(past != src){
        path[iter] = route[past];
        past = route[past];
        iter++;
    }

    return path;
}

int find_min(int dist[node_num], bool mark[node_num]){
    int min = inf, index = -1;

    for(int i = 0;i < node_num;i++){
        if(dist[i] < min && dist[i] > 0 && mark[i] == false){
            min = dist[i];
            index = i;
        }
    }

    return index;
}

int *dijkstra(int link[node_num][node_num], int src){
    int *path = malloc(node_num * sizeof(int));
    int dist[node_num];
    bool mark[node_num];
    for(int i = 0;i < node_num;i++){
        path[i] = -1;
        dist[i] = inf;
        mark[i] = false;
    }
    mark[src] = true;
    dist[src] = 0;

    //for(int i = 0;i < node_num;i++){
    //    for(int j = 0;j < node_num;j++){
    //        printf("%10d ", link[i][j]);
    //    }
    //    putchar('\n');
    //}

    int index = src;
    for(int i = 0;i < node_num - 1;i++){

        //for(int j = 0;j < node_num;j++){
        //    printf("%d ", path[j]);
        //}
        //putchar('\n');

        for(int j = 0;j < node_num;j++){
            if(link[index][j] + dist[index] < dist[j] && mark[j] == false && link[index][j] < inf && index != j){
                dist[j] = link[index][j] + dist[index];
                path[j] = index;
            }
        }
        mark[index] = true;
        index = find_min(dist, mark);
    }
    
    return path;
}

int main(){
    //input basic data
    scanf("%d %d %d", &node_num, &link_num, &req_num);

    //input quantum memories
    int memory_data[node_num][2];
    for(int i = 0;i < node_num;i++){
        scanf("%d %d", &memory_data[i][0], &memory_data[i][1]);
    }

    int link[node_num][node_num];
    for(int i = 0;i < node_num;i++){//initialize
        for(int j = 0;j < node_num;j++){
            link[i][j] = 0;
        }
    }
    for(int i = 0;i < link_num;i++){//input link data
        int end0 = -1, end1 = -1, channel = -1;
        scanf("%*d %d %d %d", &end0, &end1, &channel);
        link[end0][end1] = channel;
        link[end1][end0] = channel;
    }
    int path[node_num][node_num];//the length between all nodes is 1
    for(int i = 0;i < node_num;i++){
        for(int j = 0;j < node_num;j++){
            if(link[i][j] != 0){
                path[i][j] = 1;
                path[j][i] = 1;
            }
            else if(i == j) path[i][j] = 0;
            else{
                path[i][j] = inf;
                path[j][i] = inf;
            }
        }
    }

    //input request data
    int req[req_num][3];
    for(int i = 0;i < req_num;i++){
        scanf("%d %d %d", &req[i][0], &req[i][1], &req[i][2]);
    }

    //sort quantum memories by nodeId
    int memory[node_num];
    for(int i = 0;i < node_num;i++){
        memory[i] = 0;
    }
    for(int i = 0;i < node_num;i++){
        memory[memory_data[i][0]] = memory_data[i][1];
    }

    int final_resultcnt = 0;
    int final_result[req_num][node_num + 1];
    for(int i = 0;i < req_num;i++){
        for(int j = 0;j < node_num + 1;j++){
            final_result[i][j] = -1;
        }
    }

    int *route, *result;
    int resultcnt = 0;
    bool accept = true;
    for(int i = 0;i < req_num;i++){
        if(memory[req[i][1]] > 0 && memory[req[i][2] > 0]){
            route = dijkstra(path, req[i][1]);

            //for(int j = 0;j < node_num;j++){
            //    printf("%d ", route[j]);
            //}
            //putchar('\n');

            result = find_path(route, req[i][1], req[i][2]);

            //for(int j = 0;j < node_num;j++){
            //    printf("%d ", result[j]);
            //}
            //putchar('\n');

            while(result[resultcnt] != -1){
                resultcnt++;
            }

            int final_route[resultcnt + 1];

            for(int j = 0;j < resultcnt;j++){
                final_route[j] = result[resultcnt - j - 1];
            }
            final_route[resultcnt] = req[i][2];
            resultcnt++;

            for(int j = 0;j < resultcnt - 1;j++){
                if(link[final_route[j]][final_route[j + 1]] < 1){
                    accept = false;
                    break;
                }
                else if(memory[final_route[j]] < 2 && j != 0){
                    accept = false;
                    break;
                }
                else{
                    continue;
                }
            }

            if(accept == true){
                final_result[final_resultcnt][0] = req[i][0];
                for(int j = 0;j < resultcnt;j++){
                    final_result[final_resultcnt][j + 1] = final_route[j];
                }
                final_resultcnt++;

                for(int j = 1;j < resultcnt;j++){
                    link[final_result[i][j]][final_result[i][j + 1]]--;
                    link[final_result[i][j + 1]][final_result[i][j]]--;
                    if(link[final_result[i][j]][final_result[i][j + 1]] == 0){
                        path[final_result[i][j]][final_result[i][j + 1]] = inf;
                        path[final_result[i][j + 1]][final_result[i][j]] = inf;
                    }
                    memory[final_result[i][j]]--;
                    memory[final_result[i][j + 1]]--;
                }
            }
            resultcnt = 0;
            accept = true;
            free(route);
            free(result);
        }
    }

    printf("%d\n", final_resultcnt);
    for(int i = 0;i < final_resultcnt;i++){
        for(int j = 0;j < node_num + 1;j++){
            if(final_result[i][j] <= -1) break;
            else printf("%d ", final_result[i][j]);
        }
        putchar('\n');
    }

    return 0;
}