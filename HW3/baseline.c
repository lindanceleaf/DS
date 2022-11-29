#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct{
    int start;
    int end;
    double length;
} links;

int find_root(int x, int root[]){
    if(x == root[x]) return x;
    else return find_root(root[x], root);
}

int main(){
    int Nodes_num, threshold;
    scanf("%d %d", &Nodes_num, &threshold);
    
    double Nodes_data[Nodes_num][2];
    for(int i = 0; i < Nodes_num; i++){
        int ID;
        scanf("%d", &ID);
        scanf("%lf %lf",&Nodes_data[ID][0], &Nodes_data[ID][1]);
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

    // ! check for distance table
    /* for(int i = 0; i < Nodes_num; i++){
        for(int j = 0; j < Nodes_num; j++){
            printf("%lf ", distance[i][j]);
        }
        printf("\n");
    } */

    // create the sorted distance list (by binary insertion sort)
    int links_num = (Nodes_num * (Nodes_num - 1)) / 2; // combination taken 2 from n
    int cnt = 0;
    links links_data[links_num]; 
    // only sort distance from upper triangular matrix to keep start_point_ID < end_point_ID
    for(int i = 0; i < Nodes_num - 1; i++){
        for(int j = i + 1; j < Nodes_num; j++){
            // distance[i][j] is the data that would put into the list
            int place = cnt;
            if(cnt == 0){
                links_data[0].start = i;
                links_data[0].end = j;
                links_data[0].length = distance[i][j];
                cnt++;
            }
            else if(links_data[cnt - 1].length < distance[i][j]){
                links_data[cnt].start = i;
                links_data[cnt].end = j;
                links_data[cnt].length = distance[i][j];
                cnt++;
            }
            else{
                int left = 0, right = cnt - 1;
                while(left <= right){
                    int mid = left + (right - left) / 2;
                    if(links_data[mid].length < distance[i][j]) left = mid + 1;
                    else if(links_data[mid - 1].length < distance[i][j]){
                        place = mid;
                        break;
                    }
                    else right = mid - 1;
                }

                for(int k = cnt; k > place; k--){
                    links_data[k] = links_data[k - 1];
                }
                links_data[place].start = i;
                links_data[place].end = j;
                links_data[place].length = distance[i][j];
                cnt++;
            }
        }
    }

    // ! check the links_data whether is right
    /* for(int i = 0; i < links_num; i++){
        printf("%d %d %d %lf\n", i,links_data[i].start, links_data[i].end, links_data[i].length);
    } */

    // create minimum spanning tree
    int root[Nodes_num];
    for(int i = 0; i < Nodes_num; i++) root[i] = i;
    links tree[Nodes_num - 1];
    int success_links_num = 0;

    for(int i = 0; i < links_num; i++){
        int start_root = find_root(links_data[i].start, root);
        int end_root = find_root(links_data[i].end, root);
        // if is ring then do nothing
        if(start_root == end_root) continue;
        // not ring then connect
        else{
            // union
            tree[success_links_num++] = links_data[i];
            if(start_root < end_root) root[end_root] = start_root;
            else root[start_root] = end_root;
        }
    }

    // DFS
    // sort the links in tree to do DFS
    for(int i = 0; i < Nodes_num - 2; i++){
        for(int j = i; j < Nodes_num - 2 - i; j++){
            if((tree[j].start > tree[j + 1].start) || (tree[j].start == tree[j + 1].start && tree[j].end > tree[j + 1].end)){
                links temp = tree[j];
                tree[j] = tree[j + 1];
                tree[j + 1] = temp;
            }
        }
    }
    int path[Nodes_num];
    int stack[Nodes_num];
    stack[0] = 0;

    int path_cnt = 0;
    int top = 0;
    bool is_pop[Nodes_num];
    for(int i = 0; i < Nodes_num; i++) is_pop[i] = false;
    while(top != -1){
        int parent = stack[top--];
        path[path_cnt++] = parent;
        is_pop[parent] = true;
        for(int i = Nodes_num - 2; i >= 0; i--){
            if(tree[i].start == parent && !is_pop[tree[i].end]){
                stack[++top] = tree[i].end;
            }
            else if(tree[i].end == parent && !is_pop[tree[i].start]){
                stack[++top] = tree[i].start;
            }
        }
    }

    // ! test path
    /* for(int i = 0 ; i < path_cnt; i++) printf("%d ", path[i]);
    printf("\n"); */

    // UAV
    int UAV_cnt = 0;
    int path_start[Nodes_num], path_end[Nodes_num];
    path_start[0] = path_end[0] = path[0];
    double path_len = 0;
    for(int i = 1; i < path_cnt; i++){
        double adding_distance = distance[path[i - 1]][path[i]];
        if(path_len + adding_distance <= (double)threshold / 2){
            path_len += adding_distance;
            path_end[UAV_cnt] = path[i];
        }
        else{
            UAV_cnt++;
            path_start[UAV_cnt] = path_end[UAV_cnt] = path[i];
            path_len = 0;
        }
    }
    UAV_cnt++;

    // output result
    printf("%d\n", UAV_cnt);
    int UAV_ID = 0;
    printf("0 ");
    for(int i = 0; i < Nodes_num; i++){
        printf("%d", path[i]);
        if(path[i] == path_end[UAV_ID]){
            printf("\n");
            UAV_ID++;
            if(i != Nodes_num - 1) printf("%d ", UAV_ID);
        }
        else{
            printf(" ");
        }
    }
}