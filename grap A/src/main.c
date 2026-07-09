#include "graph_adjlist.h"
#include <windows.h>


void Menu()
{
    printf("\n====景区路径规划系统（邻接表版）====\n");
    printf("1. 创建景区图\n");
    printf("2. 添加景点\n");
    printf("3. 添加景点间路径\n");
    printf("4. 显示整个景区图\n");
    printf("5. 显示每个景点邻接链表\n");
    printf("0. 退出程序\n");
    printf("====================================\n");
    printf("请输入操作序号：");
}

int main()
{
    SetConsoleOutputCP(65001);
    GraphAdjList G;
    int op, w;
    char name1[20], name2[20];
    while(1)
    {
        Menu();
        scanf("%d", &op);
        getchar(); // 吸收换行

        switch(op)
        {
            case 1:
                CreateGraph(&G);
                break;
            case 2:
                printf("输入新增景点名称：");
                scanf("%s", name1);
                AddVex(&G, name1);
                break;
            case 3:
                printf("输入起点景点：");
                scanf("%s", name1);
                printf("输入终点景点：");
                scanf("%s", name2);
                printf("输入道路距离：");
                scanf("%d", &w);
                AddEdge(&G, name1, name2, w);
                break;
            case 4:
                ShowGraph(&G);
                break;
            case 5:
                ShowAllVexLink(&G);
                break;
            case 0:
                printf("程序退出\n");
                return 0;
            default:
                printf("输入序号无效，请重新选择\n");
        }
    }
    return 0;
}