#include "Graph.h"

Graph::Graph(int _nrNodes)
{
    this -> nrNodes = _nrNodes;
    this -> edges.resize(_nrNodes+1);
    /*
     * Nodes start at 1, but index starts at 0
     */
}

int Graph::getNrNodes() const
{
    return this -> nrNodes;
}

void Graph::setEdge(int node, int neighbour, double cost)
{
    this -> edges[node].push_back({make_pair(neighbour, cost)});
}

const vector<pair<int, double>>& Graph::getNeighbours(int node)
{
    return this -> edges[node];
}

int Graph::nrConnectedComponents()
{
    int ans = 0;
    vector<int> visited(this -> nrNodes+1, 0);
    for(int i = 1 ; i <= this -> nrNodes; i++)
        if(visited[i] == 0)
        {
            DFS(i, visited);
            ++ans;
        }
    return ans;
}


void Graph::DFS(int start, vector<int>& visited)
{
    visited[start] = 1;
    for(auto &it: this ->edges[start])
    {
        int neighbour = it.first; // get neighbour without cost
        if(visited[neighbour] == 0)
        {
            visited[neighbour] = 1;
            DFS(neighbour, visited);
        }
    }
}

void Graph::printEdges() const
{
  for(int i = 1; i <= this->getNrNodes(); i++)
  {
      cout << i<< ": ";
      for(auto &it: edges[i])
          cout << it.first<< " ";
      cout << "\n";
  }
}







