#include <stdio.h>
#include "Graph.h"
void approxVertexCover(Graph g);
int main(void) {
    /* NEEDS TO BE COMPLETED */
    Edge e;
    int n;
    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    Graph g = newGraph(n);
    printf("Enter an edge (from): ");
    while (scanf("%d", &e.v) == 1) {
        printf("Enter an edge (to): ");
        scanf("%d", &e.w);
        insertEdge(g, e);
        printf("Enter an edge (from): ");
    }
    printf("Done.\n");
    approxVertexCover(g);
    freeGraph(g);
    return 0;
}
