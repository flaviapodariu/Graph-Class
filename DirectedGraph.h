#ifndef CLASA_GRAF_DIRECTEDGRAPH_H
#define CLASA_GRAF_DIRECTEDGRAPH_H

#include "Graph.h"

class DirectedGraph: public Graph {
    void TarjanDFS(int start, int& counterID,
                          stack<int>&nodeStack, vector<bool>&onStack,
                          vector<vector<int>>&scc,
                          vector<int>&nodeID, vector<int>&lowestLink);
    void TopologicalDFS(int node, stack<int>&sorted,
                        vector<bool>&visited);
public:
    DirectedGraph(int _nrNodes);
    void addEdge(int node, int neighbour, double cost);
    vector<vector<int>> getStronglyConnected();
    stack<int> TopologicalSorting();
   ~DirectedGraph();
};


#endif //CLASA_GRAF_DIRECTEDGRAPH_H
