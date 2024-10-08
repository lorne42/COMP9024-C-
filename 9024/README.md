# Data Structures and Algorithms Project

This project contains implementations of various data structures and algorithms, including Binary Search Trees (BST), Red-Black Trees (RBT), graphs, Prim's algorithm for Minimum Spanning Tree, and a PageRank algorithm. The code is designed to demonstrate the use of efficient data structures for solving common computational problems.

## Files and Description

### 1. `BST.c` and `BST.h`
- **Description**: Implements a Binary Search Tree (BST) and provides functions for inserting, deleting, searching, and balancing the tree. It includes AVL tree rotations to maintain tree balance.
- **Key Functions**:
  - `TreeInsert`: Inserts a new node into the BST.
  - `TreeDelete`: Deletes a node from the BST.
  - `TreeHeight`: Returns the height of the tree.
  - `TreeSearch`: Searches for a node in the BST.
- **Usage**: Include both `BST.c` and `BST.h` in your project to manage and manipulate a binary search tree.

### 2. `graph-ArrayofEdges.c`
- **Description**: Implements a graph using an array of edges representation. This file allows for operations such as inserting and removing edges, and checking adjacency between vertices.
- **Key Functions**:
  - `insertEdge`: Adds an edge to the graph.
  - `removeEdge`: Removes an edge from the graph.
  - `approxVertexCover`: Approximates the vertex cover of the graph.
- **Usage**: Compile and run to test graph operations.

### 3. `memerrors.c`
- **Description**: Demonstrates proper memory allocation and deallocation in C using dynamic memory management functions (`malloc`, `free`). Each function is designed to prevent memory leaks.
- **Usage**: Compile and run to observe memory management in action.

### 4. `pageRank.c`
- **Description**: Implements a PageRank algorithm for ranking web pages based on inbound and outbound links between pages. The program reads a graph structure and calculates PageRank scores.
- **Key Functions**:
  - `sort`: Sorts web pages based on their inbound and outbound links.
  - `insertionSort`: A helper function that sorts vertices based on their PageRank score.
- **Usage**: Compile and run, providing the number of webpages and the corresponding links to compute the ranking.

### 5. `prim.c`
- **Description**: Implements Prim's algorithm to find the Minimum Spanning Tree (MST) of a given graph. It calculates the sum of the edge weights in the MST.
- **Key Functions**:
  - `prim`: Finds the MST using Prim's algorithm.
  - `insertEdge`: Adds an edge to the graph.
- **Usage**: Compile and run to compute the MST for a given graph.

### 6. `RBTree.c` and `RBTree.h`
- **Description**: Implements a Red-Black Tree (RBT), a self-balancing binary search tree. It maintains balance through rotations and color changes during insertions.
- **Key Functions**:
  - `TreeInsert`: Inserts a node into the Red-Black Tree.
  - `rotateLeft` / `rotateRight`: Performs tree rotations to maintain balance.
- **Usage**: Include both `RBTree.c` and `RBTree.h` in your project to use a Red-Black Tree for efficient data storage and retrieval.

### 7. `tripView.c`
- **Description**: Implements a timetable system using a graph structure to store train stations and their connections. It provides a depth-first search (DFS) to find possible routes between stations.
- **Key Functions**:
  - `findPaths`: Finds all possible paths between two stations using DFS.
  - `insertEdgeofG`: Inserts an edge (connection) between two stations.
- **Usage**: Compile and run to simulate a train scheduling system.

### 8. `vertexCover.c`
- **Description**: Contains a heuristic algorithm for approximating the vertex cover of a graph. The vertex cover is a set of vertices that covers all edges in the graph.
- **Key Functions**:
  - `approxVertexCover`: Finds an approximate solution to the vertex cover problem.
- **Usage**: Compile and run to find the vertex cover of a given graph.

## Compilation and Execution

To compile and run the programs:

```bash
# Compile any file (example for BST.c)
gcc -o bst BST.c

# Run the compiled program
./bst
