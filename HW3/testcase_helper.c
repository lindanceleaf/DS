#include <stdio.h>
#include <math.h>

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

    int nodes[] = {0, 51, 34, 57, 88, 24, 62, 55, 46, 83, 28, 64, 3, 65, 47, 26, 27, 4, 11, 61, 33, 87, 75, 67, 77, 63, 60, 32, 49, 14, 41, 38, 1, 17, 19, 21, 70, 31, 9, 80, 8, 23, 39, 68, 85, 54, 58, 5, 35, 22, 53, 12, 40, 79, 6, 82, 74, 73, 2, 84, 36, 43, 20, 71, 15, 16, 44, 10, 52, 45, 72, 13, 42, 50, 59, 66, 7, 29, 25, 37, 56, 30, 48, 81, 78, 18, 86, 76, 69};

    for(int i = 0; i < Nodes_num - 1; i++){
        printf("%d %d %lf\n", nodes[i], nodes[i + 1], distance[nodes[i]][nodes[i + 1]]);
    }
}