#include "DirectedGraph.h"

DirectedGraph::DirectedGraph(int _nrNodes): Graph(_nrNodes) {}

void DirectedGraph::addEdge(int node, int neighbour)
{
    this -> setEdge(node, neighbour);
}



DirectedGraph::~DirectedGraph() {}
