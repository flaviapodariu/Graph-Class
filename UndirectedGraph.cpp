#include "UndirectedGraph.h"
using namespace std;
UndirectedGraph::UndirectedGraph(int _nrNodes): Graph(_nrNodes){}

void UndirectedGraph::addEdge(int node, int neighbour, double cost)
{
    this -> setEdge(node, neighbour, cost);
    this -> setEdge(neighbour, node, cost);
}

UndirectedGraph::~UndirectedGraph() {}

vector<vector<int>> UndirectedGraph::biconnectedComponents()
{
    vector<vector<int>>bcc(this->getNrNodes()+1);
    stack<int> nodeStack;
    vector<int> lowestLink(this -> getNrNodes()+1, -1);
    vector<int> nodeID(this -> getNrNodes()+1, -1);
    int counterID = 0;
    for(int node = 1; node <= this -> getNrNodes(); ++node)
        if(nodeID[node] == -1)
        {
            nodeStack.push(node);
            biconnectedDFS(node, counterID,
                           lowestLink, nodeID,
                           nodeStack, bcc, -1);
        }

    return bcc;
}

void UndirectedGraph::biconnectedDFS(int node, int& counterID,
                                     vector<int> &lowestLink,
                                     vector<int> &nodeID,
                                     stack<int> &nodeStack,
                                     vector<vector<int>> &bcc,
                                     int father)
{
    nodeID[node] = counterID;
    lowestLink[node] = counterID++;
    nodeStack.push(node);
    for (auto it: this->getNeighbours(node))
    {
        int neighbour = it.first;
        if (nodeID[neighbour] == -1 && neighbour != father)
        {

            biconnectedDFS(neighbour, counterID,
                           lowestLink, nodeID,
                           nodeStack, bcc, node);
            lowestLink[node] = min(lowestLink[node], lowestLink[neighbour]);

            if (lowestLink[neighbour] >= nodeID[node]) //node is an articulation point
              addBiconnected(nodeStack, bcc, neighbour, node);
        }
        else if (neighbour != father)
            lowestLink[node] = min(lowestLink[node], nodeID[neighbour]);


    }
}
void UndirectedGraph::addBiconnected(stack<int> &nodeStack, vector<vector<int>>&bcc,
                                            int neighbour, int node)
{
    /*
     * we stop popping at neighbour because between
     * neighbour and node (child and parent) there
     * might be other children of parent.
     * we then add neighbour and node to component
     * leaving node on stack as it might be part of
     * other components
     */
    vector<int>component;
    while (nodeStack.top() != neighbour)
    {
        component.push_back(nodeStack.top());
        nodeStack.pop();
    }
    nodeStack.pop();
    component.push_back(neighbour);
    component.push_back(node);
    bcc.push_back(component);
    component.clear();
}

vector<vector<int>> UndirectedGraph::criticalEdges()
{
    vector<vector<int>>critical;
    stack<int> nodeStack;
    vector<bool> onStack(this -> getNrNodes()+1, false);
    vector<int> lowestLink(this -> getNrNodes()+1, -1);
    vector<int> nodeID(this -> getNrNodes()+1, -1);
    int counterID = 0;
    for(int node = 1; node <= this -> getNrNodes(); ++node)
        if(nodeID[node] == -1)
        {
            nodeStack.push(node);
            criticalEdgeDFS(node, counterID,
                           lowestLink, nodeID,
                           nodeStack, critical, -1);
        }

    return critical;
}

void UndirectedGraph::criticalEdgeDFS(int node, int counterID,
                                      vector<int> &lowestLink,
                                      vector<int> &nodeID,
                                      stack<int> &nodeStack,
                                      vector<vector<int>> &critical, int father)
{
    nodeID[node] = counterID;
    lowestLink[node] = counterID++;
    nodeStack.push(node);
    for (auto it: this->getNeighbours(node))
    {
        int neighbour = it.first;
        if (nodeID[neighbour] == -1 && neighbour != father)
        {
            criticalEdgeDFS(neighbour, counterID,
                            lowestLink, nodeID,
                            nodeStack, critical, node);
            lowestLink[node] = min(lowestLink[node], lowestLink[neighbour]);

            if (lowestLink[neighbour] > nodeID[node]) //node is an articulation point
                critical.push_back({node, neighbour});
        }

        else if (neighbour != father)
            lowestLink[node] = min(lowestLink[node], nodeID[neighbour]);
    }
}




