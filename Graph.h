#ifndef CLASA_GRAF_GRAPH_H
#define CLASA_GRAF_GRAPH_H
#include <vector>
#include <stack>
#include<iostream>
using namespace std;

class Graph {
    int nrNodes; //number of nodes
    vector<vector< pair<int, double>> > edges; // list of connections between nodes
public:
    Graph(int _nrNodes);
    int getNrNodes() const;
    void setEdge(int node, int neighbour, double cost);
    vector<pair<int, double>>getNeighbours(int node);
    int nrConnectedComponents();
    void printEdges();
    vector<int> minDistanceBFS(int start);
    ~Graph();
private:
    void DFS(int node, vector<int>& visited);

};


#endif //CLASA_GRAF_GRAPH_H
