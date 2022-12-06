#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>
#include<string.h>
#define ll long long
#define typename int


typedef struct vector
{
	typename *array;
	unsigned long long size_t;
	unsigned long long capicity;
}vector;

vector initialize() {
	vector temp;
	temp.capicity = 2;
	temp.array = (typename*)malloc(sizeof(typename) * temp.capicity);
	temp.size_t = 0;
	return temp;
}

unsigned ll size(vector *datastructure) {
	return datastructure->size_t;
}

void push_back(vector *datastructure, typename value) {
	datastructure->array[datastructure->size_t] = value;
	datastructure->size_t += 1;
	if (datastructure->size_t * 2 >= datastructure->capicity) {
		datastructure->capicity *= 2;
		typename *temp = datastructure->array;
		datastructure->array = (typename *)malloc(sizeof(typename)*datastructure->capicity);
		for (int i = 0; i < size(datastructure); i++)
			datastructure->array[i] = temp[i];
		free(temp);
	}
}

void clear(vector *t) {
	free(t->array);
	*t = initialize();
}

double dis(double **table, int node1, int node2) {
	if (node1 == node2) return 0;
	double x_d = table[node1][0] - table[node2][0];
	double y_d = table[node1][1] - table[node2][1];
	return sqrt(x_d * x_d + y_d * y_d);
}

double **establish_table(int node_num) {
	double **dis_table = (double**)malloc(sizeof(double*) * node_num);
	for (int i = 0; i < node_num; i++)
		dis_table[i] = (double*)malloc(sizeof(double) * node_num);
	double **node_site = (double**)malloc(sizeof(double*) * node_num);
	for (int i = 0; i < node_num; i++)
		node_site[i] = (double*)malloc(sizeof(double) * 2);
	for (int i = 0; i < node_num; i++) {
		int id;
		double x, y;
		scanf("%d%lf%lf", &id, &x, &y);
		node_site[id][0] = x;
		node_site[id][1] = y;
	}
	for (int i = 0; i < node_num; i++) {
		for (int j = 0; j < node_num; j++) {
			dis_table[i][j] = dis(node_site, i, j);
		}
	}
	return dis_table;
}

bool end(bool *pass, int node_num) {
	for (int i = 0; i < node_num; i++)
		if (pass[i] == false) return false;
	//printf("daedwa");
	return true;
}

int shrotest_point(double **table, int point, int node_num, bool *pass){
    double dis = 1000000007;
    int point_index;
    for(int i = 0; i < node_num; i++){
        if(table[i][point] < dis && i != point && pass[i] == false){
            dis = table[i][point];
            point_index = i;
        }
    }
    return point_index;
}

int num;

vector *solve(double **table, int node_num, int uvadis, int root){
    bool *pass = (bool*)malloc(sizeof(bool) * node_num);//此陣列紀錄這個點有沒有被飛過
	for (int i = 0; i < node_num; i++)
		pass[i] = false;
	vector *ans = (vector*)malloc(sizeof(vector) * 100);
	for (int i = 0; i < 100; i++) {
		ans[i] = initialize();
	}
    num = 0;
    int index = root;
    for(int i = 0; i < node_num; i++){
        if (end(pass, node_num)) break;//若每個點都被飛過了，離開函式
        double dis = uvadis;
        int start = index;// index是當前的點
        int shrotest_index;// shrotest_index為離index最近的點
        while(1){
            if (index >= node_num) break;
            if (end(pass, node_num)) break;//若每個點都被飛過了，離開函式
            shrotest_index = shrotest_point(table, index, node_num, pass);//此函式會找出離index最近，且沒被飛過的點
            if (dis - table[start][shrotest_index] - table[index][shrotest_index] < 0.0){
                push_back(&ans[i], index);
                pass[index] = true;
				index = shrotest_index;
                break;
            }
            else if(dis - table[start][shrotest_index] - table[index][shrotest_index] >= 0.0){
				// 若無人機的燃料夠飛  離此點最近的點的距離+離此點最近的點到原點的距離
                dis -= table[index][shrotest_index];
                push_back(&ans[i], index);
                pass[index] = true;
                index = shrotest_index;
            }
        }
        num++;
    }
    return ans;
}

int main() {
	int node_num;
	double uvadis;
	scanf("%d%lf", &node_num, &uvadis);
	double **dis_table = establish_table(node_num); //建立一個二維陣列，紀錄每個點之間的直線距離
	int uav_ans = 100000;
	vector *ans;
	// solve 函式為，以第4個argument為起點，每次都飛向最短的路徑
	// 以用0為起點來舉例，先把起點標記為已經飛過的地點
	// 假設距離0最近的點是5 ， 檢查5是否可以飛回這台無人機的起點0
	// 若可以，將5加入這台無人機可飛的距離，並且尋找離5最近的點
	// 假設離5最近的點是7，檢查7是否可以飛回這台無人機的起點0
	// 若可以，將7加入這台無人機可飛的距離，並且尋找離7最近的點
	// 假設離7最近的點是9，檢查9是否可以飛回這台無人機的起點0
	// 假設不行，無人機直接飛回原點，這台無人機結束
	// 下一台無人機從9開始飛，重複一樣的動作
	for(int i = 0; i < node_num; i++){
		solve(dis_table, node_num, uvadis, i);
		if(num < uav_ans){
			uav_ans = num;
			ans = solve(dis_table, node_num, uvadis, i);
		}
	}// 此for迴圈為暴力跑一次以每個點為第0台無人機的起點的狀況
	printf("%d\n", uav_ans);
	for (int i = 0; i < uav_ans; i++) {
		printf("%d ", i);
		for (int j = 0; j < size(&ans[i]); j++) {
			printf("%d ", ans[i].array[j]);
		}
		printf("\n");
	}
}
