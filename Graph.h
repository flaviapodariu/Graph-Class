#ifndef CLASA_GRAF_GRAPH_H
#define CLASA_GRAF_GRAPH_H
#include <vector>
using namespace std;

class Graph {
    int nrNodes; //number of nodes
    vector<vector<int>> edges; // list of connections between nodes
public:
    Graph(int _nrNodes);
    int getNrNodes() const;
    void setEdge(int, int);
    int nrConnectedComponents();
    void printEdges();
    vector<int> minDistanceBFS(int start);
    ~Graph();
private:
    void DFS(int node, vector<int>& visited);

};


#endif //CLASA_GRAF_GRAPH_H
