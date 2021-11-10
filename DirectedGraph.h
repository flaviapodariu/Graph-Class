#ifndef CLASA_GRAF_DIRECTEDGRAPH_H
#define CLASA_GRAF_DIRECTEDGRAPH_H

#include "Graph.h"

class DirectedGraph: public Graph {
public:
    DirectedGraph(int _nrNodes);
    void addEdge(int node, int neighbour, double cost);
    ~DirectedGraph() = default;

    vector<vector<int>> getStronglyConnected();
    stack<int> topologicalSorting();
    vector<int> minDistanceBFS(int start);

private:

    void TarjanDFS(int start, int& counterID,
                          stack<int>& nodeStack, vector<bool>& onStack,
                          vector<vector<int>>& scc,
                          vector<int>& nodeID, vector<int>& lowestLink);

    void topologicalDFS(int node, stack<int>& sorted,
                        vector<bool>& visited);

};


#endif //CLASA_GRAF_DIRECTEDGRAPH_H
