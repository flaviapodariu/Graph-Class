#ifndef CLASA_GRAF_UNDIRECTEDGRAPH_H
#define CLASA_GRAF_UNDIRECTEDGRAPH_H

#include "Graph.h"

class UndirectedGraph: public Graph{
public:
    UndirectedGraph(int _nrNodes);
    void addEdge(int node, int neighbour, int cost);
    ~UndirectedGraph() = default;

    vector<vector<int>> biconnectedComponents();
    vector<vector<int>> criticalEdges();
    bool havelHakimi(vector<int>degrees);

private:
    void biconnectedDFS(int node, int father, vector<int>& lowestLink,
                        vector<int>& nodeID, stack<int>& nodeStack,
                        vector<vector<int>>& bcc);

    void addBiconnected(stack<int>& nodeStack, int node, int neighbour,
                        vector<vector<int>>& bcc);

    void criticalEdgeDFS(int node, int father,vector<int>& lowestLink,
                         vector<int>& nodeID, vector<vector<int>>& critical);
};


#endif //CLASA_GRAF_UNDIRECTEDGRAPH_H
