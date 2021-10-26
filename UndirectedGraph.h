#ifndef CLASA_GRAF_UNDIRECTEDGRAPH_H
#define CLASA_GRAF_UNDIRECTEDGRAPH_H

#include "Graph.h"

class UndirectedGraph: public Graph{

public:
    UndirectedGraph(int _nrNodes);
    void addEdge(int, int);
    ~UndirectedGraph();
};


#endif //CLASA_GRAF_UNDIRECTEDGRAPH_H
