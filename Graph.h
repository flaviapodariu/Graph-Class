#ifndef CLASA_GRAF_GRAPH_H
#define CLASA_GRAF_GRAPH_H
#include <vector>
#include <stack>
#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

struct edge
{
    int node;
    int neighbour;
    long cost;
    int capacity;
};

class Graph {
    int nrNodes; //number of nodes
    vector<vector<edge>> edges; // list of connections between nodes
public:
    Graph(int _nrNodes);
    int getNrNodes() const;
    void setEdge(int node, int neighbour, int cost=0, int capacity=0);
    void printEdges() const;
    const vector<edge>& getNeighbours(int node);
    virtual ~Graph() = default;

    int nrConnectedComponents();
    vector<int> getDistancesBFS(const int& start);
    vector<int> PrimMST(int& costMST);
    vector<int> Dijkstra(const int& start);
    vector<int> BellmanFord(const int& start);
    void disjointSets(int op, int node1, int node2,
                      vector<bool>& sameGroup, vector<int>& root);
    int minCost(int node1, int node2);
    vector<vector<int>> getMinCostMatrix();
    int getTreeDiameter(const int& start);
    int getMinSalesmanCost(const int& start, vector<int>& costs);

private:
    void DFS(int node, vector<int>& visited);
    int findGroup(int node, vector<int>& root); //with path compression
    void unifyGroups(int node1, int node2, vector<int>& root);
    vector<vector<int>> RoyFloyd();
};


#endif //CLASA_GRAF_GRAPH_H
