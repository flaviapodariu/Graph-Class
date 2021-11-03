#include "UndirectedGraph.h"

UndirectedGraph::UndirectedGraph(int _nrNodes): Graph(_nrNodes){}

void UndirectedGraph::addEdge(int node, int neighbour, double cost)
{
    this -> setEdge(node, neighbour, cost);
    this -> setEdge(neighbour, node, cost);
}

UndirectedGraph::~UndirectedGraph() {}

vector<vector<int>> UndirectedGraph::biconnectedComponents()
{
    vector<vector<int>>bcc;
    stack<int> nodeStack;
    vector<bool> onStack(this -> getNrNodes()+1, false);
    vector<int> lowestLink(this -> getNrNodes()+1, -1);
    vector<int> nodeID(this -> getNrNodes()+1, -1);
    int counterID = 0;
    for(int node = 1; node <= this -> getNrNodes(); ++node)
        if(nodeID[node] == -1)
        {
            nodeStack.push(node);
            BiconnectedDFS(node, counterID,
                           lowestLink, nodeID,
                           nodeStack, bcc, -1);
        }
    return bcc;
}

void UndirectedGraph::BiconnectedDFS(int node, int counterID,
                                     vector<int> lowestLink,
                                     vector<int> nodeID,
                                     stack<int> nodeStack,
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

            BiconnectedDFS(neighbour, counterID,
                           lowestLink, nodeID,
                           nodeStack, bcc, node);

            if (lowestLink[neighbour] >= nodeID[node])
                addBiconnected(nodeStack, bcc, node);
        }
        else if (neighbour != father)
            lowestLink[node] = min(lowestLink[node], lowestLink[neighbour]);


    }
}
void UndirectedGraph::addBiconnected(stack<int> &nodeStack, vector<vector<int>>&bcc,
                                            int node)
{
    vector<int>component;
    while (nodeStack.top() != node)
    {
        component.push_back(nodeStack.top());
        nodeStack.pop();
    }
    component.push_back(nodeStack.top());
    nodeStack.pop();
    bcc.push_back(component);
    component.clear();
}




