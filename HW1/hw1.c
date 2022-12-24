#include<stdio.h>
#define MAXN 1000
#define INF 1e9

struct Node{
    int id;
    int QuantumMemery;
};

struct Link{
    int id;
    int end1;
    int end2;
    int channel;
};

struct Request{
    int id;
    int src;
    int dst;
};

struct Accreq{
    int src;
    int rep[MAXN];
    int dst;
};

//input varible
struct Node nodes[MAXN];
struct Link links[MAXN];
struct Request reqs[MAXN];
struct Accreq accreq[MAXN];
int NodesNum, LinksNum, ReqsNum, accreqNum = 0, repNum = 0;

//dijkstra varible
int graph[MAXN][MAXN];
int visited[MAXN];
int path[MAXN];
int distance[MAXN];

void dijkstra(int src);
void remove_quantum_memery(int dst);

int main(void){

    //input
    scanf("%d %d %d\n", &NodesNum, &LinksNum, &ReqsNum);

    for(int i = 0; i < NodesNum; i++){
        scanf("%d %d", &nodes[i].id, &nodes[i].QuantumMemery);
    }

    for(int i = 1; i <= LinksNum; i++){     //link[]�q1�}�l
        scanf("%d %d %d %d", &links[i].id, &links[i].end1, &links[i].end2, &links[i].channel);
    }

    for(int i = 0; i < ReqsNum; i++){
        scanf("%d %d %d", &reqs[i].id, &reqs[i].src, &reqs[i].dst);
    }

    //init graph (i == links.id + 1)
    for(int i = 1; i <= LinksNum; i++){
        graph[links[i].end1][links[i].end2] = i;
        graph[links[i].end2][links[i].end1] = i;
    }


    //start
    for(int i = 0; i < ReqsNum; i++){
        dijkstra(reqs[i].src);
        if(distance[reqs[i].dst] < INF){
            remove_quantum_memery(reqs[i].dst);
            accreq[accreqNum].src = reqs[i].src;
            accreq[accreqNum].dst = reqs[i].dst;
            accreqNum++;
        }
    }
    //ans
    printf("%d\n", accreqNum);
    for(int i = 0; i < accreqNum; i++){

        //accrep_id
        printf("%d ", i);
        printf("%d ", accreq[i].src);
        if(repNum != 0){
            //rep�˵ۦL
            for(int j = repNum; j > 0; j--){
                printf("%d ", accreq[i].rep[j]);
            }
        }
        printf("%d\n", accreq[i].dst);
    }
}

void dijkstra(int src){

    //init
    for(int i = 0; i < NodesNum; i++){
        visited[i] = 0;
        distance[i] = INF;
        path[i] = -1;
    }

    distance[src] = 0;

    //start
    for(int i = 0; i < NodesNum; i++){

        int NearNode = -1, MinDis = INF;

        for(int j = NodesNum - 1; j >= 0; j--){
            if(!visited[j] && distance[j] < MinDis){
                MinDis = distance[j];
                NearNode = j;
            }
        }

        if(NearNode == -1) return;

        visited[NearNode] = 1;

        //�M��  update distance[]
        for(int j = 0; j < NodesNum; j++){

            //�I���I���Z�� > �g�L�̵u���|�`�I���Z�� => ��s���|
            if(!visited[j] && graph[NearNode][j] && distance[j] > distance[NearNode] + !(!graph[NearNode][j]) ){

                int link_id = graph[NearNode][j];

                //�d�ݧ�蠟���u���O����O�_����
                if(nodes[links[link_id].end1].QuantumMemery && nodes[links[link_id].end2].QuantumMemery && links[link_id].channel){
                    distance[j] = distance[NearNode] + 1;
                    path[j] = NearNode;
                }
            }
        }
    }return;
}

void remove_quantum_memery(int dst){
    int parent_id = path[dst];
    while(parent_id != -1){
        nodes[links[parent_id].end1].QuantumMemery--;
        nodes[links[parent_id].end2].QuantumMemery--;
        links[parent_id].channel--;

        //�Nparent_id���W����
        parent_id = path[parent_id];

        if(parent_id != -1){
            //���������g�L���I (�ư� src dst)
            accreq[accreqNum].rep[repNum] = links[parent_id].end1;
            repNum++;
        }

    }
    return;
}
