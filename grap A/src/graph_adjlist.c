#include "graph_adjlist.h"

// 根据景点名称查找顶点下标，不存在返回-1
 int LocateVex(GraphAdjList *G, char *vexName)
{
    for(int i = 0; i < G->vexNum; i++)
    {
        if(strcmp(G->adjList[i].vexName, vexName) == 0)
            return i;
    }
    return -1;
}

// 初始化空邻接表图
void CreateGraph(GraphAdjList *G)
{
    G->vexNum = 0;
    G->edgeNum = 0;
    for(int i = 0; i < MAX_VEX_NUM; i++)
    {
        G->adjList[i].firstEdge = NULL;
        memset(G->adjList[i].vexName, 0, sizeof(G->adjList[i].vexName));
    }
    printf("已初始化景区邻接表图\n");
}

// 添加新景点
int AddVex(GraphAdjList *G, char *vexName)
{
    if(G->vexNum >= MAX_VEX_NUM)
    {
        printf("景点数量已达上限，无法新增\n");
        return 0;
    }
    // 查重
    if(LocateVex(G, vexName) != -1)
    {
        printf("景点%s已存在，无需重复添加\n", vexName);
        return 0;
    }
    strcpy(G->adjList[G->vexNum].vexName, vexName);
    G->adjList[G->vexNum].firstEdge = NULL;
    G->vexNum++;
    printf("成功添加景点：%s\n", vexName);
    return 1;
}

// 添加双向路径（无向边）
int AddEdge(GraphAdjList *G, char *v1Name, char *v2Name, int weight)
{
    int v1 = LocateVex(G, v1Name);
    int v2 = LocateVex(G, v2Name);
    if(v1 == -1 || v2 == -1)
    {
        printf("路径端点景点不存在，添加失败\n");
        return 0;
    }

    // 构建v1指向v2的边结点
    EdgeNode *e1 = (EdgeNode*)malloc(sizeof(EdgeNode));
    e1->adjVex = v2;
    e1->weight = weight;
    e1->nextEdge = G->adjList[v1].firstEdge;
    G->adjList[v1].firstEdge = e1;

    // 构建v2指向v1的边结点（无向图双向）
    EdgeNode *e2 = (EdgeNode*)malloc(sizeof(EdgeNode));
    e2->adjVex = v1;
    e2->weight = weight;
    e2->nextEdge = G->adjList[v2].firstEdge;
    G->adjList[v2].firstEdge = e2;

    G->edgeNum++;
    printf("成功添加路径：%s <-> %s，距离：%d\n", v1Name, v2Name, weight);
    return 1;
}

// 打印景区整体图信息
void ShowGraph(GraphAdjList *G)
{
    printf("=========景区邻接表总览=========\n");
    printf("景点总数：%d，道路总数：%d\n", G->vexNum, G->edgeNum);
    for(int i = 0; i < G->vexNum; i++)
    {
        printf("[%d]景点：%s  连通：", i, G->adjList[i].vexName);
        EdgeNode *p = G->adjList[i].firstEdge;
        while(p != NULL)
        {
            printf("%s(%d) ", G->adjList[p->adjVex].vexName, p->weight);
            p = p->nextEdge;
        }
        printf("\n");
    }
    printf("================================\n");
}

// 逐个打印每个景点的邻接链表（实验要求功能）
void ShowAllVexLink(GraphAdjList *G)
{
    printf("\n=====各景点独立邻接链表=====\n");
    for(int i = 0; i < G->vexNum; i++)
    {
        printf("景点【%s】链表：", G->adjList[i].vexName);
        EdgeNode *p = G->adjList[i].firstEdge;
        if(p == NULL)
        {
            printf("无相邻景点\n");
            continue;
        }
        while(p != NULL)
        {
            printf("%s(距离%d) -> ", G->adjList[p->adjVex].vexName, p->weight);
            p = p->nextEdge;
        }
        printf("NULL\n");
    }
    printf("===========================\n");
}