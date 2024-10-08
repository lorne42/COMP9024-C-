/*
Memory Allocation and Initialization:

Memory allocation for GraphLnk, Timetables, and other data structures takes O(1) time for each allocation.
Initializing the structures and arrays involves looping over the number of vertices and schedules, respectively, and setting initial values. This initialization takes O(n + m) time.
Reading Station Data and Timetables:

Reading station data involves scanning n stations, each with constant time operations. So, this takes O(n) time.
Reading timetables involves nested loops. The outer loop runs m times (number of timetables), and the inner loop runs s times (number of stops in each timetable). Therefore, this part has a time complexity of O(m * s).
Graph and Timetable Edge Insertion:

Inserting edges into the graph (insertEdgeofG) and timetables (insertEdgeofT) involves manipulating linked lists. The worst-case scenario is adding an edge to the end of a linked list, which takes O(d), where d is the length of the linked list. In the worst case, this can be O(n) for the graph edges and O(m * s) for timetable edges.
Path Finding (DFS):

The findPaths function uses a Depth-First Search (DFS) algorithm to find paths in the graph. The worst-case time complexity of DFS is O(V + E), where V is the number of vertices and E is the number of edges. In the context of this code, it can be considered O(n + m * s).
Result Processing:

The processing of results involves nested loops. In the worst case, it iterates over all paths and timetable edges, resulting in O(m * s) complexity.
Overall, considering the dominant factors:

The total time complexity is O(n + m * s + m * s + n + m * s).
Ignoring lower-order terms and constants, the overall complexity is approximately O(m * s).
Keep in mind that this analysis assumes worst-case scenarios for certain operations. The actual performance may vary based on specific input data and the distribution of edges in the graph.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define INT_MAX 2147483647

typedef struct Station_arc {
    int Sid;
    struct Station_arc* next;
} Station_arc;

typedef struct Station_node {
    int Sid;
    char name[17];
    int transferTime;
    Station_arc* firstarc;
} Station_node;

typedef struct GraphLnk {
    int NumVertices;
    int NumEdges;
    Station_node* NodeTable;
} GraphLnk;

typedef struct TrainRoute {
    int routeNumber;
    int arrivalStation;
    int departureTime;
    int arrivalTime;
    struct TrainRoute* next;
} TrainRoute;

typedef struct TrainSchedule {
    int Sid;
    struct TrainRoute* head;
} TrainSchedule;

typedef struct Timetables {
    int NumSchedules;
    int NumEdges;
    TrainSchedule* ScheduleTable;
} Timetables;

typedef struct Result_node {
    int sid;
    int time;
    struct Result_node* next;
} Result_node;

typedef struct Results {
    int num;
    Result_node* resulttable;
} Results;

void insertEdgeofG(GraphLnk* graph, int sourceSid, int destinationSid) {
    // Validate if source and destination vertices exist
    if (sourceSid < 0 || sourceSid >= graph->NumVertices || destinationSid < 0 || destinationSid >= graph->NumVertices) {
        printf("Invalid vertex indices\n");
        return;
    }

    // Create a new edge node
    Station_arc* newEdge = (Station_arc*)malloc(sizeof(Station_arc));
    newEdge->Sid = destinationSid;
    newEdge->next = NULL;

    // Find the source station in the NodeTable
    Station_node* sourceStation = &(graph->NodeTable[sourceSid]);

    // If the source station has no edges yet, set the new edge as the first edge
    if (sourceStation->firstarc == NULL) {
        sourceStation->firstarc = newEdge;
    }
    else {
        // Otherwise, find the last edge in the list and append the new edge
        Station_arc* currentEdge = sourceStation->firstarc;
        if (currentEdge->Sid == destinationSid)
            return;
        while (currentEdge->next != NULL) {
            if (currentEdge->Sid == destinationSid)
                return;
            currentEdge = currentEdge->next;
        }
        currentEdge->next = newEdge;
    }

    // Increment the number of edges in the graph
    graph->NumEdges++;
}

int find_nodeid(GraphLnk* graph, char n[]) {
    for (int i = 0; i < graph->NumVertices; i++) {
        if (strcmp(graph->NodeTable[i].name, n) == 0)
            return graph->NodeTable[i].Sid;
    }
    return -1;
}

void insertEdgeofT(Timetables* timetables, int sourceSid, int routeNumber, int arrivalStation, int departureTime, int arrivalTime) {
    if (sourceSid < 0 || sourceSid >= timetables->NumSchedules) {
        printf("Invalid source station ID\n");
        return;
    }

    TrainRoute* newRoute = (TrainRoute*)malloc(sizeof(TrainRoute));
    if (newRoute == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    newRoute->routeNumber = routeNumber;
    newRoute->arrivalStation = arrivalStation;
    newRoute->departureTime = departureTime;
    newRoute->arrivalTime = arrivalTime;
    newRoute->next = timetables->ScheduleTable[sourceSid].head;
    timetables->ScheduleTable[sourceSid].head = newRoute;

    timetables->NumEdges++;
}

#define MAX_PATH_LENGTH 100

typedef struct {
    int* nodes;
    int length;
} Path;

void DFS(GraphLnk* graph, int startID, int endID, bool* visited, int* path, int pathIndex, Path** allPaths, int* numPaths) {
    visited[startID] = true;
    path[pathIndex] = startID;
    pathIndex++;

    if (startID == endID) {
        Path* newPath = (Path*)malloc(sizeof(Path));
        newPath->nodes = (int*)malloc(pathIndex * sizeof(int));
        for (int i = 0; i < pathIndex; ++i) {
            newPath->nodes[i] = path[i];
        }
        newPath->length = pathIndex;

        allPaths[*numPaths] = newPath;
        (*numPaths)++;
    }
    else {
        Station_arc* arc = graph->NodeTable[startID].firstarc;
        while (arc != NULL) {
            int neighborID = arc->Sid;
            if (!visited[neighborID]) {
                DFS(graph, neighborID, endID, visited, path, pathIndex, allPaths, numPaths);
            }
            arc = arc->next;
        }
    }

    visited[startID] = false;
}

Path** findPaths(GraphLnk* graph, int startID, int endID, int* numPaths) {
    bool* visited = (bool*)malloc(graph->NumVertices * sizeof(bool));
    int* path = (int*)malloc(MAX_PATH_LENGTH * sizeof(int));

    for (int i = 0; i < graph->NumVertices; ++i) {
        visited[i] = false;
    }

    Path** allPaths = (Path**)malloc(MAX_PATH_LENGTH * sizeof(Path*));
    *numPaths = 0;

    DFS(graph, startID, endID, visited, path, 0, allPaths, numPaths);

    free(visited);
    free(path);

    return allPaths;
}

void freePaths(Path** allPaths, int numPaths) {
    for (int i = 0; i < numPaths; ++i) {
        free(allPaths[i]->nodes);
        free(allPaths[i]);
    }
    free(allPaths);
}

void addResult(Result_node* resultsList, int sid, int time) {
    Result_node* newResult = (Result_node*)malloc(sizeof(Result_node));
    if (newResult == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newResult->sid = sid;
    newResult->time = time;
    newResult->next = NULL;
    if (resultsList->next == NULL) {
        resultsList->next = newResult;
    }
    else {
        Result_node* currentResult = resultsList->next;
        while (currentResult->next != NULL) {
            currentResult = currentResult->next;
        }
        currentResult->next = newResult;
    }
}

void clearResults(Result_node* resultsList) {
    Result_node* currentResult = resultsList->next;
    Result_node* nextResult;

    while (currentResult != NULL) {
        nextResult = currentResult->next;
        free(currentResult);
        currentResult = nextResult;
    }

    resultsList->next = NULL;
}

int convertmin(int t) {
    int a = (t / 100) * 60 + (t % 100);
    return a;
}

void freeResults(Results* re) {
    if (re != NULL) {
        Result_node* currentResult = re->resulttable;
        Result_node* nextResult;

        while (currentResult != NULL) {
            nextResult = currentResult->next;
            free(currentResult); // Free the current node
            currentResult = nextResult;
        }

        // Free the Results structure itself
        free(re);
    }
}


int main() {
    GraphLnk* g = (GraphLnk*)malloc(sizeof(GraphLnk));
    Timetables* table = (Timetables*)malloc(sizeof(Timetables));
    int n; // Number of stations
    printf("Size of network: ");
    scanf("%d", &n);
    table->ScheduleTable = (TrainSchedule*)malloc(sizeof(TrainSchedule) * n);
    if (table->ScheduleTable == NULL) {
        fprintf(stderr, "Memory allocation failed for NodeTable\n");
        exit(EXIT_FAILURE);
    }
    table->NumSchedules = n;
    table->NumEdges = 0;
    assert(table->ScheduleTable != NULL);
    for (int i = 0; i < table->NumSchedules; ++i) {
        table->ScheduleTable[i].head = NULL;
    }

    g->NodeTable = (Station_node*)malloc(sizeof(Station_node) * n);
    if (g->NodeTable == NULL) {
        fprintf(stderr, "Memory allocation failed for NodeTable\n");
        exit(EXIT_FAILURE);
    }
    g->NumVertices = n;
    g->NumEdges = 0;
    assert(g->NodeTable != NULL);
    for (int i = 0; i < g->NumVertices; ++i) {
        g->NodeTable[i].firstarc = NULL;
    }

    // Read station data
    for (int i = 0; i < n; i++) {
        g->NodeTable[i].Sid = i;
        table->ScheduleTable[i].Sid = i;
        scanf("%s", g->NodeTable[i].name);
        scanf("%d", &g->NodeTable[i].transferTime);
    }

    int m;
    printf("Number of timetables: ");
    scanf("%d", &m);

    int s; // Number of stops in the timetable
    char last_station[17];
    int last_time;
    char tmp_name[17];
    int tmp_time;
    for (int i = 0; i < m; i++) {
        printf("Number of stops: ");
        scanf("%d", &s);
        for (int j = 0; j < s; j++) {
            scanf("%s", tmp_name);
            scanf("%d", &tmp_time);

            if (j != 0) {
                insertEdgeofT(table, find_nodeid(g, last_station), i, find_nodeid(g, tmp_name), last_time, tmp_time);
                insertEdgeofG(g, find_nodeid(g, last_station), find_nodeid(g, tmp_name));
            }
            strcpy(last_station, tmp_name);
            last_time = tmp_time;
        }
    }

    // Process user queries for Stage 1
    char from[17], to[17];
    int arriveTime;

    while (1) {
        printf("\n");
        printf("From: ");
        scanf("%s", from);

        if (strcmp(from, "done") == 0) {
            printf("Bye\n");
            break;
        }
        printf("To: ");
        scanf("%s", to);
        printf("Arrive at or before: ");
        scanf("%d", &arriveTime);
        int startID = find_nodeid(g, from);
        int endID = find_nodeid(g, to);

        int numPaths;
        Path** allPaths = findPaths(g, startID, endID, &numPaths);
        int path_no[100];
        for (int i = 0; i < 100; i++)
            path_no[i] = -1;
        Results* re = (Results*)malloc(sizeof(Results));
        re->resulttable = (Result_node*)malloc(sizeof(Result_node) * 100);
        if (re->resulttable == NULL) {
            fprintf(stderr, "Memory allocation failed for NodeTable\n");
            exit(EXIT_FAILURE);
        }

        re->num = 0;
        assert(re->resulttable != NULL);
        for (int i = 0; i < 100; ++i) {
            re->resulttable[i].sid = -1;
            re->resulttable[i].time = -1;
            re->resulttable[i].next = NULL;
        }
        for (int i = 0; i < numPaths; ++i) {
            TrainRoute* currentroute = table->ScheduleTable[(allPaths[i]->nodes[allPaths[i]->length - 2])].head;
            while (currentroute != NULL) {
                if (currentroute->arrivalStation == allPaths[i]->nodes[allPaths[i]->length - 1] && currentroute->arrivalTime <= arriveTime) {
                    for (int j = 0; j < 100; j++) {
                        if (path_no[j] == -1) {
                            path_no[j] = i;
                            break;
                        }
                    }
                    break;
                }
                else
                    currentroute = currentroute->next;
            }
        }
        for (int i = 0; i < 100 && path_no[i] >= 0; i++) {
            int j = path_no[i];
            int tmp_lid = -1;
            int last_lid = -1;
            TrainRoute* lastedge = NULL;
            for (int e = 0; e < allPaths[j]->length - 1; e++) {
                TrainRoute* currentedge = table->ScheduleTable[allPaths[j]->nodes[e]].head;
                while (currentedge != NULL) {
                    if (currentedge->arrivalStation == allPaths[j]->nodes[e + 1]) {
                        break;
                    }
                    currentedge = currentedge->next;
                }
                tmp_lid = currentedge->routeNumber;

                if (last_lid == -1) {
                    addResult(&re->resulttable[re->num], allPaths[j]->nodes[e], currentedge->departureTime);
                }
                else if (last_lid == tmp_lid) {
                    addResult(&re->resulttable[re->num], allPaths[j]->nodes[e], currentedge->departureTime);
                    if (e == allPaths[j]->length - 2) {
                        addResult(&re->resulttable[re->num], allPaths[j]->nodes[e + 1], currentedge->arrivalTime);
                        re->num++;
                        break;
                    }
                }
                else if (last_lid != tmp_lid) {
                    if (convertmin(lastedge->arrivalTime) + g->NodeTable[allPaths[j]->nodes[e]].transferTime <= convertmin(currentedge->departureTime)) {
                        addResult(&re->resulttable[re->num], allPaths[j]->nodes[e], lastedge->arrivalTime);
                        addResult(&re->resulttable[re->num], allPaths[j]->nodes[e], currentedge->departureTime);
                        if (e == allPaths[j]->length - 2) {
                            addResult(&re->resulttable[re->num], allPaths[j]->nodes[e + 1], currentedge->arrivalTime);
                            re->num++;
                            break;
                        }
                    }
                    else {
                        clearResults(&re->resulttable[re->num]);
                    }
                }
                lastedge = currentedge;
                last_lid = tmp_lid;
            }
        }

        printf("\n");
        if (re->num == 0) {
            printf("No connection.");
            printf("\n");
        }
        else if (re->num == 1) {
            Result_node* tmp = re->resulttable[0].next;
            Result_node* last = NULL;
            while (tmp) {
                if (last == NULL || tmp->sid != last->sid) {
                    printf("%04d ", tmp->time);
                    printf("%s", g->NodeTable[tmp->sid].name);
                    printf("\n");
                    last = tmp;
                    tmp = tmp->next;
                }
                else {
                    printf("Change at %s", g->NodeTable[tmp->sid].name);
                    printf("\n");
                    printf("%04d ", tmp->time);
                    printf("%s", g->NodeTable[tmp->sid].name);
                    printf("\n");
                    last = tmp;
                    tmp = tmp->next;
                }
            }
        }
        else {
            int latesttime = 0;
            int mintime = INT_MAX;
            int index[100];
            for (int i = 0; i < 100; i++)
                index[i] = -1;
            Result_node* q = NULL;
            for (int i = 0; i < re->num; i++) {
                q = re->resulttable[i].next;
                if (re->resulttable[i].next->time > latesttime)
                    latesttime = re->resulttable[i].next->time;
                while (q->next) {
                    q = q->next;
                }
                if (convertmin(q->time) - re->resulttable[i].next->time < mintime) {
                    mintime = convertmin(q->time) - re->resulttable[i].next->time;
                }
            }

            for (int i = 0; i < re->num; i++) {
                q = re->resulttable[i].next;
                while (q->next) {
                    q = q->next;
                }
                if (re->resulttable[i].next->time == latesttime && convertmin(q->time) - re->resulttable[i].next->time == mintime)
                    for (int j = 0; j < 100; j++) {
                        if (index[j] == -1) {
                            index[j] = i;
                            break;
                        }
                    }
            }

            for (int i = 0; i < 100; i++) {
                if (index[i] != -1) {
                    Result_node* tmp = re->resulttable[index[i]].next;
                    Result_node* last = NULL;
                    while (tmp) {
                        if (last == NULL || tmp->sid != last->sid) {
                            printf("%04d ", tmp->time);
                            printf("%s", g->NodeTable[tmp->sid].name);
                            printf("\n");
                            last = tmp;
                            tmp = tmp->next;
                        }
                        else {
                            printf("Change at %s", g->NodeTable[tmp->sid].name);
                            printf("\n");
                            printf("%04d ", tmp->time);
                            printf("%s", g->NodeTable[tmp->sid].name);
                            printf("\n");
                            last = tmp;
                            tmp = tmp->next;
                        }
                    }
                }
                else
                    break;
            }
        }
        freePaths(allPaths, numPaths);
        freeResults(re);
    }

    free(g->NodeTable);
    free(g);
    free(table->ScheduleTable);
    free(table);
    return 0;
}


