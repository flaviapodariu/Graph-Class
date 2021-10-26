#include "Graph.h"
#include <iostream>
#include <queue>
using namespace std;

Graph::Graph(int _nrNodes)
{
    this -> nrNodes = _nrNodes;
    this -> edges.resize(this -> nrNodes + 1, vector<int>());
    /*
     * Nodes start at 1, but index starts at 0
     */
}

int Graph::getNrNodes() const
{
    return this -> nrNodes;
}

int Graph::nrConnectedComponents()
{
    int ans = 0;
    vector<int>visited(this -> nrNodes+1, 0);
    for(int i = 1 ; i <= this -> nrNodes; ++i)
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
    for(int i = 0; i < edges[start].size(); ++i)
    {
        int neighbour = edges[start][i];
        if(visited[neighbour] == 0)
        {
//            visited[neighbour] = 1;
            DFS(neighbour, visited);
        }
    }
}

Graph::~Graph()
{
    this -> nrNodes = 0;
    for(int i = 1; i <= edges.size(); ++i)
        this -> edges[i].clear();
}

void Graph::printEdges()
{
  for(int i = 1; i < edges.size(); i++)
  {
      cout << i<< ": ";
      for(auto it: edges[i])
          cout << it<< " ";
      cout << "\n";
  }
}

void Graph::setEdge(int node, int neighbour)
{
   this ->edges[node].push_back(neighbour);
}

vector<int> Graph::minDistanceBFS(int start)
{
    vector<int>distances(this->nrNodes + 1, -1);
    distances[start] = 0;

    queue<int>toBeVisited;
    toBeVisited.push(start);

    while(!toBeVisited.empty())
    {
        int x = toBeVisited.front();
        toBeVisited.pop();

        for(auto it: this->edges[x])
            if(distances[it] == -1)
            {
                distances[it] = distances[x] + 1;
                toBeVisited.push(it);
            }


    }     //while loop ended

    return distances;
}

