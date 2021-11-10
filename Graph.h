#ifndef CLASA_GRAF_GRAPH_H
#define CLASA_GRAF_GRAPH_H
#include <vector>
#include <stack>
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

class Graph {
    int nrNodes; //number of nodes
    vector<vector<pair<int, double>>> edges; // list of connections between nodes
public:
    Graph(int _nrNodes);
    int getNrNodes() const;
    void setEdge(int node, int neighbour, double cost);
    void printEdges() const;
    int nrConnectedComponents();
    const vector<pair<int, double>>& getNeighbours(int node);
    virtual ~Graph() = default;
private:
    void DFS(int node, vector<int>& visited);
};


#endif //CLASA_GRAF_GRAPH_H
