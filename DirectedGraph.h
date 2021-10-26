#ifndef CLASA_GRAF_DIRECTEDGRAPH_H
#define CLASA_GRAF_DIRECTEDGRAPH_H

#include "Graph.h"

class DirectedGraph: public Graph {

public:
    DirectedGraph(int _nrNodes);
    void addEdge(int node, int neighbour);
    vector<vector<int>> getStronglyConnected(int node);
   ~DirectedGraph();
};


#endif //CLASA_GRAF_DIRECTEDGRAPH_H
