#ifndef GRAPH_ADJLIST_H
#define GRAPH_ADJLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VEX_NUM 50  // 最大景点数量

// 边链表结点：存储邻接景点下标、路径权重
typedef struct EdgeNode {
    int adjVex;             // 邻接顶点下标
    int weight;             // 路径长度/权重
    struct EdgeNode *nextEdge;
} EdgeNode;

// 顶点结构体：景点名称 + 边链表头
typedef struct VexNode {
    char vexName[20];       // 景点名称
    EdgeNode *firstEdge;
} VexNode, AdjList[MAX_VEX_NUM];

// 邻接表总图结构体
typedef struct {
    AdjList adjList;
    int vexNum;             // 当前景点总数
    int edgeNum;            // 当前路径总数
} GraphAdjList;

// 对外接口函数声明
// 1. 创建空图
void CreateGraph(GraphAdjList *G);
// 2. 添加景点（顶点）
int AddVex(GraphAdjList *G, char *vexName);
// 3. 添加双向路径（无向图，景区道路互通）
int AddEdge(GraphAdjList *G, char *v1Name, char *v2Name, int weight);
// 4. 打印整个景区图信息
void ShowGraph(GraphAdjList *G);
// 5. 单独打印每个景点的邻接链表
void ShowAllVexLink(GraphAdjList *G);
// 内部工具：根据景点名查找下标

int LocateVex(GraphAdjList *G, char *vexName);

#endif