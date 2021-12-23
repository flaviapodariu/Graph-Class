#include "DirectedGraph.h"

DirectedGraph::DirectedGraph(int _nrNodes): Graph(_nrNodes) {}


void DirectedGraph::addEdge(int node, int neighbour, int cost, int capacity)
{
   this -> setEdge(node, neighbour, cost, capacity);
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
                              stack<int>& nodeStack,
                              vector<bool>& onStack,
                              vector<vector<int>>& scc,
                              vector<int>& nodeID,
                              vector<int>& lowestLink)
{
    vector<int> component;
    nodeID[node] = counterID;
    lowestLink[node] = counterID++;
    nodeStack.push(node);
    onStack[node] = true;

    for(auto &it: this->getNeighbours(node))
    {
        int neighbour = it.neighbour; // node -> first; cost -> second
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


vector<int> DirectedGraph::topologicalSorting()
{
    vector<int> sorted;
    vector<bool> visited(this->getNrNodes() + 1, false);
    for(int node = 1; node < visited.size(); ++node)
        if(!visited[node])
            topologicalDFS(node, sorted, visited);
    /*
     * -> TopologicalDFS() modifies the sorted vector
     * -> the sorted nodes are the nodes' times in descending order
     */
    return sorted;
}


void DirectedGraph::topologicalDFS(int node, vector<int>&sorted,
                                   vector<bool>&visited)
{
   visited[node] = true;
   for(auto &it: this->getNeighbours(node))
   {
       int neighbour = it.neighbour;
       if (!visited[neighbour])
           topologicalDFS(neighbour, sorted, visited);

   }
   sorted.push_back(node);
}


int DirectedGraph::getMaxFlow(const int& start, const int& sink,
                              vector<vector<int>>& capacities)
{
    int maxFlow = 0;
    vector<int>path;
    while(int bottleneck = EdmondsKarpBFS(start, sink, path, capacities))
    {
        maxFlow += bottleneck;
        int curr = sink;
        while(curr != start)
        {
            int prev = path[curr];
            capacities[prev][curr] -= bottleneck;
            capacities[curr][prev] += bottleneck; //back arch for augmented paths
            curr = prev;
        }

    }
    return maxFlow;
}


int DirectedGraph::EdmondsKarpBFS(const int &start, const int &sink,
                                  vector<int>& path, vector<vector<int>>& capacities)
{

    queue<pair<int, int>> toBeVisited;
    toBeVisited.push({start, INT_MAX}); //edge to start does not exist
    path.clear(); //starting fresh new path
    path.resize(getNrNodes()+1, -1);

    while(!toBeVisited.empty())
    {
        int node = toBeVisited.front().first;
        int capacity = toBeVisited.front().second;
        toBeVisited.pop();

        for(auto& next: getNeighbours(node))
        {
            int cpc = capacities[node][next.neighbour];
            if(cpc && path[next.neighbour] == -1)
            {
                path[next.neighbour] = node;
                int bottleneck = min(capacity, cpc);
                if(next.neighbour == sink)
                    return bottleneck;
                toBeVisited.push({next.neighbour, bottleneck});

            }
        }
    }

    return 0;
}



