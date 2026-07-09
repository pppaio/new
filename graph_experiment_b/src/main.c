#include <stdio.h>
#include <string.h>
#include "../include/graph_interface.h"
#include "../include/console_utils.h"

static void printMenuBanner(void)
{
    printf("\n========== 景区路径规划系统 [B角色: 邻接矩阵 + SOLID重构版] ==========\n");
    printf("  1. 创建景区图（选择 有向/无向）\n");
    printf("  2. 添加景点\n");
    printf("  3. 添加路径（两景点间道路及其长度）\n");
    printf("  4. 显示景区图（邻接矩阵）\n");
    printf("  5. 显示景点链表\n");
    printf("  6. 一键运行内置演示（湖光岩景区）\n");
    printf("  7. 销毁当前景区图（重置）\n");
    printf("  8. 查询接口测试(查某景点详情 / 边权重 / 边是否存在)\n");
    printf("  0. 退出系统\n");
    printf("=====================================================================\n");
    printf("请输入选项: ");
}

static int isGraphReady(const IGraph *graph)
{
    return (graph != NULL && graphGetVertexCount(graph) > 0);
}

static void handleCreateGraph(IGraph *graph)
{
    int graphDirection;
    printf("请选择图类型: 0=无向图(默认), 1=有向图: ");
    graphDirection = consoleReadInt(0);
    graphCreate(graph, graphDirection);
    printf("创建成功: %s图, 最大支持 %d 个景点\n",
           graphDirection ? "有向" : "无向", MAX_VERTEX_COUNT);
}

static void handleAddVertex(IGraph *graph)
{
    char vertexName[MAX_VERTEX_NAME_LENGTH];
    char vertexDesc[MAX_VERTEX_DESC_LENGTH];
    int newVertexId;

    printf("当前已有景点 %d 个\n", graphGetVertexCount(graph));
    printf("请输入景点名称: ");
    consoleClearInputBuffer();
    consoleReadLine(vertexName, sizeof(vertexName));
    if (strlen(vertexName) == 0) {
        printf("景点名称不能为空！\n");
        return;
    }
    printf("请输入景点描述(可直接回车跳过): ");
    consoleReadLine(vertexDesc, sizeof(vertexDesc));

    newVertexId = graphAddVertex(
        graph,
        vertexName,
        strlen(vertexDesc) > 0 ? vertexDesc : NULL
    );
    if (newVertexId >= 0) {
        GraphVertex vertexInfo;
        graphGetVertexById(graph, newVertexId, &vertexInfo);
        printf("添加成功: 景点编号(V%d) = %s\n", newVertexId, vertexInfo.vertexName);
    }
}

static void handleAddEdge(IGraph *graph)
{
    int fromVertexId;
    int toVertexId;
    int edgeWeight;
    int vertexCount = graphGetVertexCount(graph);
    GraphVertex fromVertex;
    GraphVertex toVertex;

    if (vertexCount < 2) {
        printf("景点不足(当前 %d 个)，请先添加至少两个景点\n", vertexCount);
        return;
    }

    graphDisplayVertexList(graph);

    printf("请输入起点景点编号 (V?): ");
    fromVertexId = consoleReadInt(-1);
    printf("请输入终点景点编号 (V?): ");
    toVertexId = consoleReadInt(-1);
    printf("请输入路径长度(正整数): ");
    edgeWeight = consoleReadInt(-1);

    if (graphAddEdge(graph, fromVertexId, toVertexId, edgeWeight) == 0) {
        graphGetVertexById(graph, fromVertexId, &fromVertex);
        graphGetVertexById(graph, toVertexId, &toVertex);
        printf("路径添加成功: %s(V%d) --%d--> %s(V%d)\n",
               fromVertex.vertexName, fromVertexId, edgeWeight,
               toVertex.vertexName, toVertexId);
    }
}

static void handleQueryApi(IGraph *graph)
{
    int vertexId;
    int fromId;
    int toId;
    GraphVertex vertexInfo;
    if (!isGraphReady(graph)) {
        printf("请先创建图并添加景点\n");
        return;
    }

    printf("-- 查询顶点详情 --\n");
    printf("请输入顶点编号(V?): ");
    vertexId = consoleReadInt(-1);
    if (graphGetVertexById(graph, vertexId, &vertexInfo) == 0) {
        printf("  顶点查询结果: ");
        consolePrintVertexSummary(&vertexInfo);
        printf("\n");
    } else {
        printf("  顶点编号 %d 不存在\n", vertexId);
    }

    printf("-- 查询边是否存在及权重 --\n");
    printf("请输入起点ID 终点ID（空格分隔）: ");
    fromId = consoleReadInt(-1);
    toId = consoleReadInt(-1);
    if (graphHasEdge(graph, fromId, toId)) {
        printf("  V%d -> V%d 存在直接路径，权重 = %d\n",
               fromId, toId, graphGetEdgeWeight(graph, fromId, toId));
    } else {
        printf("  V%d -> V%d 不存在直接路径(INF)\n", fromId, toId);
    }
}

static void loadScenicDemoData(IGraph *graph)
{
    printf(">>> 正在加载【湖光岩世界地质公园】景区演示数据...\n");
    graphCreate(graph, 0);

    graphAddVertex(graph, "西门入口",   "景区主入口, 游客服务中心");
    graphAddVertex(graph, "玛珥湖广场", "湖中心观景广场");
    graphAddVertex(graph, "火山博物馆", "科普教育基地");
    graphAddVertex(graph, "望海楼",     "登高远眺景点");
    graphAddVertex(graph, "楞严寺",     "千年古刹, 白衣庵");
    graphAddVertex(graph, "九曲桥",     "湖心景观桥");
    graphAddVertex(graph, "东门出口",   "景区次出口, 停车场");

    graphAddEdge(graph, 0, 1, 500);
    graphAddEdge(graph, 0, 2, 300);
    graphAddEdge(graph, 1, 2, 200);
    graphAddEdge(graph, 1, 3, 450);
    graphAddEdge(graph, 1, 5, 150);
    graphAddEdge(graph, 2, 4, 350);
    graphAddEdge(graph, 3, 6, 700);
    graphAddEdge(graph, 4, 5, 220);
    graphAddEdge(graph, 5, 6, 400);
    graphAddEdge(graph, 3, 5, 180);

    printf(">>> 演示数据加载完成: %d 个景点\n", graphGetVertexCount(graph));
    graphDisplayGraph(graph);
    graphDisplayVertexList(graph);
}

int main(void)
{
    IGraph *scenicGraph;
    int userChoice;
    int graphInitialized = 0;

    consoleInitEncoding();
    scenicGraph = createAdjacencyMatrixGraph();

    if (scenicGraph == NULL) {
        printf("系统初始化失败: 无法创建景区图实例\n");
        return 1;
    }

    do {
        printMenuBanner();
        userChoice = consoleReadInt(-1);

        switch (userChoice) {
        case 1:
            handleCreateGraph(scenicGraph);
            graphInitialized = 1;
            break;
        case 2:
            if (!graphInitialized) {
                printf("请先选择 [1] 创建景区图\n");
                break;
            }
            handleAddVertex(scenicGraph);
            break;
        case 3:
            if (!graphInitialized) {
                printf("请先选择 [1] 创建景区图\n");
                break;
            }
            handleAddEdge(scenicGraph);
            break;
        case 4:
            if (!isGraphReady(scenicGraph)) {
                printf("请先创建图并添加景点\n");
                break;
            }
            graphDisplayGraph(scenicGraph);
            break;
        case 5:
            if (!isGraphReady(scenicGraph)) {
                printf("请先创建图并添加景点\n");
                break;
            }
            graphDisplayVertexList(scenicGraph);
            break;
        case 6:
            loadScenicDemoData(scenicGraph);
            graphInitialized = 1;
            break;
        case 7:
            graphDestroy(scenicGraph);
            printf("景区图已销毁重置\n");
            graphInitialized = 0;
            break;
        case 8:
            handleQueryApi(scenicGraph);
            break;
        case 0:
            printf("感谢使用景区路径规划系统，再见！\n");
            break;
        default:
            printf("无效选项(0~8), 请重试\n");
            break;
        }
    } while (userChoice != 0);

    releaseGraphInstance(scenicGraph);
    return 0;
}
