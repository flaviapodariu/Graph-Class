#ifndef CLASA_GRAF_GRAPH_H
#define CLASA_GRAF_GRAPH_H
#include <vector>
#include <stack>
#include <iostream>
#include <queue>
#include <algorithm>
#include <cfloat>
using namespace std;

struct edge
{
    int node;
    int neighbour;
    long cost;

};

class Graph {
    int nrNodes; //number of nodes
    vector<vector<edge>> edges; // list of connections between nodes
public:
    Graph(int _nrNodes);
    int getNrNodes() const;
    void setEdge(int node, int neighbour, int cost);
    void printEdges() const;
    const vector<edge>& getNeighbours(int node);
    virtual ~Graph() = default;

    int nrConnectedComponents();
    vector<int> minDistanceBFS(int start);
    vector<int> PrimMST(int& costMST);
    vector<int> Dijkstra();
    vector<int> BellmanFord();
    void disjointSets(int op, int node1, int node2,
                      vector<bool>& sameGroup, vector<int>& root);

private:
    void DFS(int node, vector<int>& visited);
    int findGroup(int node, vector<int>& root); //with path compression
    void unifyGroups(int node1, int node2, vector<int>& root);

};


#endif //CLASA_GRAF_GRAPH_H
