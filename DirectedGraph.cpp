#include "DirectedGraph.h"
using namespace std;
DirectedGraph::DirectedGraph(int _nrNodes): Graph(_nrNodes) {}

void DirectedGraph::addEdge(int node, int neighbour, double cost)
{
    this -> setEdge(node, neighbour, cost);
}

vector<vector<int>> DirectedGraph::getStronglyConnected()
{ // initializing everything we need for the Tarjan algorithm
    vector<vector<int>> scc;
    stack<int> nodeStack;
    vector<bool> onStack(this -> getNrNodes()+1, false);
    vector<int> lowestLink(this -> getNrNodes()+1, -1);
    vector<int> nodeID(this -> getNrNodes()+1, -1);
    int counterID = 0;
    for(int node = 1; node <= this -> getNrNodes(); ++node)
        if(nodeID[node] == -1)
            TarjanDFS(node, counterID, nodeStack,
                      onStack, scc, nodeID, lowestLink);
    /*
     * scc = strongly connected component
     * TarjanDFS() modifies vector<vector<int>> scc
     * so vector<vector<int>> scc will contain all the needed components
     */

    return scc;
}

void DirectedGraph::TarjanDFS(int node, int& counterID,
                              stack<int>&nodeStack,
                              vector<bool>& onStack,
                              vector<vector<int>>&scc,
                              vector<int> &nodeID,
                              vector<int>&lowestLink)
{
    vector<int> component;
    nodeID[node] = counterID;
    lowestLink[node] = counterID++;
    nodeStack.push(node);
    onStack[node] = true;

    for(auto it: this->getNeighbours(node))
    {
        int neighbour = it.first; // node -> first; cost -> second
        if(nodeID[neighbour] == -1)         // if neighbour not visited
            TarjanDFS(neighbour, counterID, nodeStack,
                      onStack, scc, nodeID,
                      lowestLink);
        if(onStack[neighbour])          //if neighbour is on stack
            lowestLink[node] = min(lowestLink[node], lowestLink[neighbour]);
    }

    if(lowestLink[node] == nodeID[node])  // if this is true then node is the beginning of a scc
    {
        while(!nodeStack.empty())
        {
            int nodeToPop = nodeStack.top();
            component.push_back(nodeToPop);
            onStack[nodeToPop] = false;
            nodeStack.pop();
            if(nodeToPop == node)
                break;
        }

        scc.push_back(component);
        component.clear();
    }
}


DirectedGraph::~DirectedGraph() {}

stack<int> DirectedGraph::TopologicalSorting()
{
    stack<int> sorted;
    vector<bool> visited(this->getNrNodes() + 1, false);
    for(int node = 1; node < visited.size(); ++node)
        if(!visited[node])
            TopologicalDFS(node, sorted, visited);
    /*
     * -> TopologicalDFS() modifies the sorted vector
     * -> the sorted nodes are the nodes' times in descending order
     */
    return sorted;
}

void DirectedGraph::TopologicalDFS(int node, stack<int>&sorted,
                                   vector<bool>&visited)
{
   visited[node] = true;
   for(auto it: this->getNeighbours(node))
   {
       int neighbour = it.first;
       if (!visited[neighbour])
           TopologicalDFS(neighbour, sorted, visited);

   }
   sorted.push(node);
}
