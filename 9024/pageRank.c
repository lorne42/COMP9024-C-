#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "WGraph.h"

typedef struct Myvertex {
    int inbound;
    int outbound;
    int scores;
    int v;
} Myvertex;
void insertionSort(Myvertex* V, int n) {
    int i;
    for (i = 1; i < n; i++) {
        int elementi = V[i].inbound;
        int elemento = V[i].outbound;
        int elementv = V[i].v;
        int elements = V[i].scores;
        // for this element ...
        int j = i - 1;
        while (j >= 0 && V[j].inbound < elementi) {  // ... work down the ordered list
            V[j + 1].inbound = V[j].inbound;
            V[j + 1].outbound = V[j].outbound;
            V[j + 1].v = V[j].v;
            V[j + 1].scores = V[j].scores;// ... moving elements up
            j--;
        }
        V[j + 1].inbound = elementi;
        V[j + 1].outbound = elemento;
        V[j + 1].v = elementv;
        V[j + 1].scores = elements;
        // and insert in correct position
    }
    for (i = 1; i < n; i++) {
        int elementi = V[i].inbound;
        int elemento = V[i].outbound;
        int elementv = V[i].v;
        int elements = V[i].scores;
        // for this element ...
        int j = i - 1;
        while (j >= 0 && V[j].scores < elements && V[j].inbound==elementi) {  // ... work down the ordered list
            V[j + 1].inbound = V[j].inbound;
            V[j + 1].outbound = V[j].outbound;
            V[j + 1].v = V[j].v;
            V[j + 1].scores = V[j].scores;// ... moving elements up
            j--;
        }
        V[j + 1].inbound = elementi;
        V[j + 1].outbound = elemento;
        V[j + 1].v = elementv;
        V[j + 1].scores = elements;
        // and insert in correct position
    }
}
void sort(Graph g, int num) {
    Myvertex* V = (Myvertex*)malloc(sizeof(Myvertex) * num);
    for (int i = 0; i < num; i++) {
        V[i].inbound = 0;
        V[i].outbound = 0;
        V[i].scores = 0;
        V[i].v = i;
    }
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num; j++) {
            if (adjacent(g,j,i) != 0) {
                V[i].inbound++;
            }
            if (adjacent(g, i, j) != 0) {
                V[i].outbound++;
            }
        }
        V[i].scores = V[i].outbound;
    }
    for (int p = 0; p < num; p++) {
        for (int q = 0; q < num; q++) {
            if (adjacent(g, p, q) != 0) {
                V[p].scores += V[q].inbound;
            }
        }
    }
    insertionSort(V, num);
    printf("Webpage ranking: \n");
    for (int i = 0; i < num; i++) {
        printf("%d has %d inbound links and scores %d on outbound links.\n", V[i].v, V[i].inbound, V[i].scores);
    }

    return;
}

int main(void) {
    Edge e;
    int n;
    int num;
    printf("Enter the number of webpages: ");
    scanf("%d", &n);
    Graph g = newGraph(n);

    printf("Enter a webpage: ");
    while (scanf("%d", &e.v) == 1) {
        printf("Enter the number of links on webpage %d: ", e.v);
        scanf("%d", &num);
        for (int i = 0; i < num; i++) {
            printf("Enter a link on webpage %d: ", e.v);
            scanf("%d", &e.w);
            e.weight = 1;
            insertEdge(g, e);
        }
        printf("Enter a webpage: ");
    }
    printf("Done.\n\n");
    sort(g, n);
    freeGraph(g);
    return 0;
}
