// Graph ADT
// Array of Edges Representation ... COMP9024 T2
#include "Graph.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#define ENOUGH 10000  // maximum number of edges

typedef struct GraphRep {
    Edge* edges; // array of edges
    int   nV;    // #vertices (numbered 0..nV-1)
    int   nE;    // #edges
    int   n;     // size of edge array
} GraphRep;

Graph newGraph(int V) {
    assert(V >= 0);

    Graph g = malloc(sizeof(GraphRep));
    assert(g != NULL);

    g->nV = V;
    g->nE = 0;

    // allocate enough memory for edges
    g->n = ENOUGH;
    g->edges = malloc(g->n * sizeof(Edge));
    assert(g->edges != NULL);

    return g;
}

int numOfVertices(Graph g) {
    return g->nV;
}

// check if two edges are equal
bool eq(Edge e1, Edge e2) {
    return ((e1.v == e2.v && e1.w == e2.w)
        || (e1.v == e2.w && e1.w == e2.v));
}

void insertEdge(Graph g, Edge e) {
    // ensure that g exists and array of edges isn't full
    assert(g != NULL && g->nE < g->n);

    int i = 0;
    while (i < g->nE && !eq(e, g->edges[i]))
        i++;
    if (i == g->nE)                     // edge e not found
        g->edges[g->nE++] = e;
}

void removeEdge(Graph g, Edge e) {
    assert(g != NULL);                 // ensure that g exists

    int i = 0;
    while (i < g->nE && !eq(e, g->edges[i]))
        i++;
    if (i < g->nE)                      // edge e found
        g->edges[i] = g->edges[--g->nE];
}

bool adjacent(Graph g, Vertex x, Vertex y) {
    assert(g != NULL);

    Edge e;
    e.v = x; e.w = y;

    int i = 0;
    while (i < g->nE) {
        if (eq(e, g->edges[i]))
            return true;
        i++;
    }
    return false;
}

void showGraph(Graph g) {
    assert(g != NULL);

    printf("Number of vertices: %d\n", g->nV);
    printf("Number of edges: %d\n", g->nE);
    int i;
    for (i = 0; i < g->nE; i++)
        printf("Edge %d - %d\n", g->edges[i].v, g->edges[i].w);
}

void freeGraph(Graph g) {
    assert(g != NULL);

    free(g->edges);
    free(g);
}
Edge  randomEdge(Graph g) {
    int i = rand()%(g->nE);
   
    return g->edges[i];


}
Graph copyGraph(Graph g) {

        int numVertices = numOfVertices(g);
        Graph copy = newGraph(numVertices);
        for (int i = 0; i < g->nE; i++) {
            insertEdge(copy, g->edges[i]);
        }
        return copy;
}
bool  graphIsEmpty(Graph g) {
    if (g->nE == 0 && g->nV==0)
        return true;
    else
        return false;
}
Graph removeIncidentEdges(Graph g, Edge e) {
    for (int i = 0; i < g->nE; i++) {
        if ((e.v == g->edges[i].v || e.v == g->edges[i].w || e.w == g->edges[i].w || e.w == g->edges[i].v) && !eq(e, g->edges[i]))
        {
            removeEdge(g, g->edges[i]);
            i = 0;   
        } 
    }
    removeEdge(g, e);
    return g;
}
void approxVertexCover(Graph g) {
    int* visited = malloc(g->nV * sizeof(int));
    int q = 0;
    while (g->nE != 0) {
        int i = rand() % g->nE;
        visited[q++] = g->edges[i].v;
        visited[q++] = g->edges[i].w;
        removeIncidentEdges(g, g->edges[i]);
    }
    printf("Best vertex cover: \n");
    for (int v = 0; v < q; v++) {
        printf("%d \n", visited[v]);
    }
    printf("\n");
}
