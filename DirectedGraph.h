#ifndef CLASA_GRAF_DIRECTEDGRAPH_H
#define CLASA_GRAF_DIRECTEDGRAPH_H

#include "Graph.h"

class DirectedGraph: public Graph {
public:
    DirectedGraph(int _nrNodes);
    void addEdge(int node, int neighbour, int cost=0, int capacity=0);
    ~DirectedGraph() = default;

    vector<vector<int>> getStronglyConnected();
    vector<int> topologicalSorting();
    int getMaxFlow(const int& start, const int& sink,
                   vector<vector<int>>& capacities);

private:
    void TarjanDFS(int start, int& counterID,
                          stack<int>& nodeStack, vector<bool>& onStack,
                          vector<vector<int>>& scc,
                          vector<int>& nodeID, vector<int>& lowestLink);

    void topologicalDFS(int node, vector<int>& sorted,
                        vector<bool>& visited);
    int EdmondsKarpBFS(const int& start, const int& sink, vector<int>& path,
                       vector<vector<int>>& capacities);

};


#endif //CLASA_GRAF_DIRECTEDGRAPH_H
