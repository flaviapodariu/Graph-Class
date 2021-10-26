#include "UndirectedGraph.h"

UndirectedGraph::UndirectedGraph(int _nrNodes): Graph(_nrNodes){}

void UndirectedGraph::addEdge(int node, int neighbour) {
    this -> setEdge(node, neighbour);
    this -> setEdge(neighbour, node);
}

UndirectedGraph::~UndirectedGraph() {}

