#ifndef CLASA_GRAF_UNDIRECTEDGRAPH_H
#define CLASA_GRAF_UNDIRECTEDGRAPH_H

#include "Graph.h"

class UndirectedGraph: public Graph{
private:
    void biconnectedDFS(int node, int& counterID,
                        vector<int>&lowestLink, vector<int>&nodeID,
                        stack<int>&nodeStack,vector<vector<int>>&bcc,
                        int father);
    void addBiconnected(stack<int>&nodeStack, vector<vector<int>>&bcc,
                               int node, int neighbour);
    void criticalEdgeDFS(int node, int counterID,
                         vector<int>&lowestLink, vector<int>&nodeID,
                         stack<int>&nodeStack,vector<vector<int>>&critical,
                         int father);
    bool havelHakimi(vector<int>degrees);
public:
    UndirectedGraph(int _nrNodes);
    void addEdge(int node, int neighbour, double cost);
    ~UndirectedGraph();
    vector<vector<int>>biconnectedComponents();
    vector<vector<int>>criticalEdges();
    string havelHakimiAnswer();
};


#endif //CLASA_GRAF_UNDIRECTEDGRAPH_H
