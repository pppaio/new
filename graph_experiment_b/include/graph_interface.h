#ifndef GRAPH_INTERFACE_H
#define GRAPH_INTERFACE_H

#include <stddef.h>

#define MAX_VERTEX_COUNT 20
#define MAX_VERTEX_NAME_LENGTH 32
#define MAX_VERTEX_DESC_LENGTH 64
#define INFINITE_WEIGHT 99999

typedef struct {
    int vertexId;
    char vertexName[MAX_VERTEX_NAME_LENGTH];
    char vertexDesc[MAX_VERTEX_DESC_LENGTH];
} GraphVertex;

typedef struct IGraph IGraph;

typedef struct GraphOps {
    void (*createGraph)(IGraph *self, int isDirected);
    void (*destroyGraph)(IGraph *self);
    int (*addVertex)(IGraph *self, const char *vertexName, const char *vertexDesc);
    int (*addEdge)(IGraph *self, int fromVertexId, int toVertexId, int edgeWeight);
    int (*getVertexCount)(const IGraph *self);
    int (*getVertexById)(const IGraph *self, int vertexId, GraphVertex *outVertex);
    int (*hasEdge)(const IGraph *self, int fromVertexId, int toVertexId);
    int (*getEdgeWeight)(const IGraph *self, int fromVertexId, int toVertexId);
    void (*displayGraph)(const IGraph *self);
    void (*displayVertexList)(const IGraph *self);
} GraphOps;

struct IGraph {
    const GraphOps *ops;
    void *implData;
};

static inline void graphCreate(IGraph *self, int isDirected)
{
    if (self && self->ops && self->ops->createGraph) {
        self->ops->createGraph(self, isDirected);
    }
}

static inline void graphDestroy(IGraph *self)
{
    if (self && self->ops && self->ops->destroyGraph) {
        self->ops->destroyGraph(self);
    }
}

static inline int graphAddVertex(IGraph *self, const char *vertexName, const char *vertexDesc)
{
    if (self && self->ops && self->ops->addVertex) {
        return self->ops->addVertex(self, vertexName, vertexDesc);
    }
    return -1;
}

static inline int graphAddEdge(IGraph *self, int fromVertexId, int toVertexId, int edgeWeight)
{
    if (self && self->ops && self->ops->addEdge) {
        return self->ops->addEdge(self, fromVertexId, toVertexId, edgeWeight);
    }
    return -1;
}

static inline int graphGetVertexCount(const IGraph *self)
{
    if (self && self->ops && self->ops->getVertexCount) {
        return self->ops->getVertexCount(self);
    }
    return 0;
}

static inline int graphGetVertexById(const IGraph *self, int vertexId, GraphVertex *outVertex)
{
    if (self && self->ops && self->ops->getVertexById) {
        return self->ops->getVertexById(self, vertexId, outVertex);
    }
    return -1;
}

static inline int graphHasEdge(const IGraph *self, int fromVertexId, int toVertexId)
{
    if (self && self->ops && self->ops->hasEdge) {
        return self->ops->hasEdge(self, fromVertexId, toVertexId);
    }
    return 0;
}

static inline int graphGetEdgeWeight(const IGraph *self, int fromVertexId, int toVertexId)
{
    if (self && self->ops && self->ops->getEdgeWeight) {
        return self->ops->getEdgeWeight(self, fromVertexId, toVertexId);
    }
    return INFINITE_WEIGHT;
}

static inline void graphDisplayGraph(const IGraph *self)
{
    if (self && self->ops && self->ops->displayGraph) {
        self->ops->displayGraph(self);
    }
}

static inline void graphDisplayVertexList(const IGraph *self)
{
    if (self && self->ops && self->ops->displayVertexList) {
        self->ops->displayVertexList(self);
    }
}

IGraph *createAdjacencyMatrixGraph(void);
void releaseGraphInstance(IGraph *graph);

#endif
