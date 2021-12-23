#include "UndirectedGraph.h"

UndirectedGraph::UndirectedGraph(int _nrNodes): Graph(_nrNodes){}

void UndirectedGraph::addEdge(int node, int neighbour, int cost, int capacity)
{
    this -> setEdge(node, neighbour, cost, capacity);
    this -> setEdge(neighbour, node, cost, capacity);
}


vector<vector<int>> UndirectedGraph::biconnectedComponents()
{
    vector<vector<int>> bcc;
    stack<int> nodeStack;
    vector<int> lowestLink(this -> getNrNodes()+1, -1);
    vector<int> nodeID(this -> getNrNodes()+1, -1);

    for(int node = 1; node <= this -> getNrNodes(); node++)
    {
        if (nodeID.at(node) == -1)
            biconnectedDFS(node, 0, lowestLink,
                           nodeID, nodeStack, bcc);
    }
    return bcc;
}


void UndirectedGraph::biconnectedDFS(int node, int father,
                                     vector<int>& lowestLink,
                                     vector<int>& nodeID,
                                     stack<int>& nodeStack,
                                     vector<vector<int>>& bcc)
{
    nodeID[node] = nodeID[father]+1;
    lowestLink[node] = nodeID[father]+1;
    nodeStack.push(node);

    for (auto &it: this->getNeighbours(node))
    {
        int neighbour = it.neighbour;
        if (nodeID[neighbour] != -1 && neighbour != father)
            lowestLink[node] = min(lowestLink[node], nodeID[neighbour]);

        else if (neighbour != father)
        {
            biconnectedDFS(neighbour, node,
                           lowestLink, nodeID,
                           nodeStack, bcc);
            lowestLink[node] = min(lowestLink[node], lowestLink[neighbour]);

            if (lowestLink[neighbour] >= nodeID[node]) //node is an articulation point
                addBiconnected(nodeStack, node, neighbour, bcc);
        }

    }
}


void UndirectedGraph::addBiconnected(stack<int>& nodeStack, int node,
                                     int neighbour, vector<vector<int>>& bcc)
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
}


vector<vector<int>> UndirectedGraph::criticalEdges()
{
    vector<vector<int>> critical;
    vector<int> lowestLink(this -> getNrNodes()+1, -1);
    vector<int> nodeID(this -> getNrNodes()+1, -1);
    for(int node = 0; node < this -> getNrNodes(); ++node)
        if(nodeID[node] == -1)
        {
            criticalEdgeDFS(node, 0, lowestLink, nodeID,critical);
        }

    return critical;
}


void UndirectedGraph::criticalEdgeDFS(int node, int father,
                                      vector<int>& lowestLink,
                                      vector<int>& nodeID,
                                      vector<vector<int>>& critical)
{
    nodeID[node] = nodeID[father]+1;
    lowestLink[node] = nodeID[father]+1;

    for (auto &it: this->getNeighbours(node))
    {
        int neighbour = it.neighbour;
        if (nodeID[neighbour] == -1 && neighbour != father)
        {
            criticalEdgeDFS(neighbour, node, lowestLink,
                            nodeID,critical);
            lowestLink[node] = min(lowestLink[node], lowestLink[neighbour]);

            if (lowestLink[neighbour] > nodeID[node]) //node is an articulation point
                critical.push_back({node, neighbour});
        }
        else if (neighbour != father)
            lowestLink[node] = min(lowestLink[node], nodeID[neighbour]);
    }
}


bool UndirectedGraph::havelHakimi(vector<int> degrees)
{
    int loops = 0;
    while(true)
    {
        sort(degrees.begin(), degrees.end(), greater<>());

        if(degrees[0] == 0)
            return true;

        if(degrees[0] > degrees.size() - loops)
            return false;

        for(int i = 1; i <= degrees[0]; ++i)
            if(--degrees[i] < 0)
                return false;
        degrees[0] = 0;
        loops++;
    }
}


