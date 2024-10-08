#define _CRT_SECURE_NO_WARNINGS
#include "Set.h"
#include "WGraph.h"
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
Graph prim(Graph g) {
    int nV = numOfVertices(g);
    Graph mst = newGraph(nV);
    Set usedV = newSet();
    Vertex v, w;
    Edge bestEdge;
    Edge bestEdge2;
    int minWeight;

    addtoSet(usedV, 0);

    /* NEEDS TO BE COMPLETED */
    int sum = 0;
    Vertex pmin = -1;
    while (sizeSet(usedV) != nV)
    {
        minWeight = INT_MAX;
        for (int j = 0; j < nV;j++){
            v = j;
            if (memberOfSet(usedV, j)){
                
                for (int i = 0; i < nV; i++) {
                    if(!memberOfSet(usedV, i)) {
                        w = i;
                        if (minWeight > adjacent(g, v, w) && adjacent(g, v, w)) {
                            minWeight = adjacent(g, v, w);
                            pmin = w;
                            bestEdge.v = v;
                            bestEdge2.v = w;
                            bestEdge.w = w;
                            bestEdge2.w = v;
                            bestEdge.weight = minWeight;
                            bestEdge2.weight = minWeight;
                        }
                    }
                }
            }
        }
         sum += bestEdge.weight;
         addtoSet(usedV, pmin);
         insertEdge(mst, bestEdge);
         insertEdge(mst, bestEdge2);  
    }
    printf("Sum of edge weights in Minimum Spanning Tree: %d",sum);
    return mst;
}

int main(void) {
    /* NEEDS TO BE COMPLETED */
    Edge e;
    Edge r;
    int n;
    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    Graph g = newGraph(n);
    Graph mst = newGraph(n);

    printf("Enter an edge (from): ");
    while (scanf("%d", &e.v) == 1) {
            r.w = e.v;
            printf("Enter an edge (to): ");
            scanf("%d", &e.w);
            r.v = e.w;
            printf("Enter the weight: ");
            scanf("%d", &e.weight);
            r.weight = e.weight;
            insertEdge(g, e);
            insertEdge(g, r);
        printf("Enter an edge (from): ");
    }
    printf("Done.\n");
    mst = prim(g);
    freeGraph(mst);
    return 0;
}
