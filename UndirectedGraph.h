#ifndef CLASA_GRAF_UNDIRECTEDGRAPH_H
#define CLASA_GRAF_UNDIRECTEDGRAPH_H

#include "Graph.h"

class UndirectedGraph: public Graph{
public:
    UndirectedGraph(int _nrNodes);
    void addEdge(int node, int neighbour, double cost);
    ~UndirectedGraph() = default;

    vector<vector<int>> biconnectedComponents();
    vector<vector<int>> criticalEdges();
    string havelHakimiAnswer();

private:
    void biconnectedDFS(int node, int father, vector<int>& lowestLink,
                        vector<int>& nodeID, stack<int>& nodeStack,
                        vector<vector<int>>& bcc);

    void addBiconnected(stack<int>& nodeStack, int node, int neighbour,
                        vector<vector<int>>& bcc);

    void criticalEdgeDFS(int node, int father,vector<int>& lowestLink,
                         vector<int>& nodeID, vector<vector<int>>& critical);

    bool havelHakimi(vector<int>degrees);
};


#endif //CLASA_GRAF_UNDIRECTEDGRAPH_H
