#ifndef CLASA_GRAF_DIRECTEDGRAPH_H
#define CLASA_GRAF_DIRECTEDGRAPH_H

#include "Graph.h"

class DirectedGraph: public Graph {
public:
    DirectedGraph(int _nrNodes);
    void addEdge(int node, int neighbour, int cost);
    ~DirectedGraph() = default;

    vector<vector<int>> getStronglyConnected();
    vector<int> topologicalSorting();

private:

    void TarjanDFS(int start, int& counterID,
                          stack<int>& nodeStack, vector<bool>& onStack,
                          vector<vector<int>>& scc,
                          vector<int>& nodeID, vector<int>& lowestLink);

    void topologicalDFS(int node, vector<int>& sorted,
                        vector<bool>& visited);

};


#endif //CLASA_GRAF_DIRECTEDGRAPH_H
