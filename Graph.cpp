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

void Graph::setEdge(int node, int neighbour, int cost, int capacity)
{
    struct edge tmp{};
    tmp.neighbour = neighbour;
    tmp.cost = cost;
    tmp.capacity = capacity;
    this -> edges[node].push_back(tmp);
}


const vector<edge>& Graph::getNeighbours(int node)
{
    return this -> edges[node];
}


int Graph::nrConnectedComponents()
{
    int ans = 0;
    vector<bool> visited(this -> nrNodes+1, false);
    for(int i = 1 ; i <= this -> nrNodes; i++)
        if(!visited[i])
        {
            DFS(i, visited);
            ++ans;
        }
    return ans;
}


vector<int> Graph::getDistancesBFS(const int& start)
{
    vector<int>distances(this->nrNodes + 1, -1);
    distances[start] = 0;

    queue<int>toBeVisited;
    toBeVisited.push(start);

    while(!toBeVisited.empty())
    {
        int x = toBeVisited.front();
        toBeVisited.pop();

        for(auto& it: this->edges[x])
            if(distances[it.neighbour] == -1)
            {
                distances[it.neighbour] = distances[x] + 1;
                toBeVisited.push(it.neighbour);
            }

    }

    return distances;
}

vector<bool> Graph::DFS(const int &start)
{
    vector<bool> visited(this->nrNodes + 1, false);
    DFS(start, visited);

    return visited;
}


vector<int> Graph::PrimMST(int& costMST)
{
    vector<int> parent(this->nrNodes+1, 0);
    vector<int> minCost(this->nrNodes+1, INT_MAX);
    vector<bool> inMST(this -> nrNodes+1, false);
    priority_queue<pair<int, int>,vector<pair<int, int>> ,greater<>>edgePQ;
    minCost[1] = 0;
    edgePQ.push(make_pair(0, 1)); //cost has to be first for greater<> to work

    while(!edgePQ.empty())
    {
        int currCost = edgePQ.top().first;
        int node = edgePQ.top().second;
        edgePQ.pop();

        if(inMST[node])
            continue;

        inMST[node] = true;
        costMST += currCost;

        for(auto& it: edges[node])
        {
            int neighbour = it.neighbour;
            int cost = it.cost;
            if(!inMST[neighbour] && minCost[neighbour] > cost)
            {
               minCost[neighbour] = cost;
               parent[neighbour] = node;
               edgePQ.push(make_pair(minCost[neighbour], neighbour));
            }
        }
    }
    return parent;
}


void Graph::DFS(int start, vector<bool>& visited)
{
    visited[start] = true;
    for(auto &it: this ->edges[start])
    {
        int neighbour = it.neighbour;
        if(!visited[neighbour])
        {
            visited[neighbour] = true;
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
          cout << it.neighbour<< " ";
      cout << "\n";
  }
}


vector<int> Graph::Dijkstra(const int& start)
{
    vector<int> minCost(this->nrNodes+1, INT_MAX);
    vector<bool> extracted(this -> nrNodes+1, false);
    priority_queue<pair<int, int>,vector<pair<int, int>> ,greater<>>edgePQ;
    minCost[start] = 0;
    edgePQ.push(make_pair(0, start)); //cost has to be first for greater<> to work

    while(!edgePQ.empty())
    {
        int node = edgePQ.top().second;
        edgePQ.pop();

        if(extracted[node])
            continue;

        extracted[node] = true;

        for(auto& it: edges[node])
        {
            int neighbour = it.neighbour;
            int cost = it.cost;
            if(minCost[node] + cost < minCost[neighbour])
            {
                minCost[neighbour] = minCost[node] + cost;
                edgePQ.push(make_pair(minCost[neighbour], neighbour));
            }
        }
    }
    return minCost;
}


vector<int> Graph::BellmanFord(const int& start)
{
    vector<int> minCost(this->nrNodes+1, INT_MAX);
    queue<int> activeNodes;
    vector<bool> inQueue(this ->nrNodes+1, false);
    vector<int> nodeOptimizations(this->nrNodes+1, 0);
    minCost[start] = 0;
    activeNodes.push(start);
    inQueue[start] = true;
    nodeOptimizations[start] = 1;

    while(!activeNodes.empty())
    {
        int node = activeNodes.front();
        activeNodes.pop();
        inQueue[node] = false;

        for(auto& it: this -> edges[node])
        {
            int neighbour = it.neighbour;
            int cost = it.cost;
            if(minCost[node] + cost < minCost[neighbour])
            {
                minCost[neighbour] = minCost[node] + cost;
                if(!inQueue[neighbour])
                {
                    activeNodes.push(neighbour);
                    inQueue[neighbour] = true;
                    nodeOptimizations[neighbour]++;
                }
                if(nodeOptimizations[neighbour] >= this->nrNodes)
                    return {-1};

            }
        }
    }

    return minCost;
}


void Graph::disjointSets(int op, int node1, int node2,
                         vector<bool>& sameGroup, vector<int>& root)
{
    if(op == 1)
        unifyGroups(node1, node2, root);
    else
    {
        int group1 = findGroup(node1, root);
        int group2 = findGroup(node2, root);
        sameGroup.push_back(group1 == group2);
    }


}


int Graph::findGroup(int node, vector<int>& root)
{
    int temp = node;
    while(temp != root[temp])
        temp = root[temp];

    while(node != temp) //temp is root now
    {
        int next = root[node];
        root[node] = temp;
        node = next;
    }
    return temp;
}


void Graph::unifyGroups(int node1, int node2, vector<int>& root)
{
    int root1 = findGroup(node1, root);
    int root2 = findGroup(node2, root);
    if(root1 == root2)
        return; // nodes are in the same group
    else
        root[root1] = root2;
}


vector<vector<int>> Graph::getMinCostMatrix()
{
    int n = this -> nrNodes;
    vector<vector<int>> dp;
    dp.resize(n+1);
    int infinity = INT_MAX / 4; //avoid overflow

    for(int i = 1; i <= n; i++)
    {   dp[i].resize(n+1);
        for (int j = 1; j <= n; j++)
            if (i != j && this->edges[i][j-1].cost == 0)
                dp[i][j] = infinity;
            else
                dp[i][j] = this->edges[i][j-1].cost;
    }

    for(int k = 1; k <= n; k++)
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
                if(dp[i][k] + dp[k][j] < dp[i][j])
                    dp[i][j] = dp[i][k] + dp[k][j];

    return dp;
}


int Graph::getTreeDiameter(const int &start)
{
    int maxDist = -1;
    int endpoint;
    vector<int> dist = getDistancesBFS(start);

    for(int i = 1; i <= this -> nrNodes; i++)
        if(dist[i] > maxDist)
        {
            maxDist = dist[i];
            endpoint = i;
        }

    dist = getDistancesBFS(endpoint);
    maxDist = -1;

    for(int i = 1; i <= this -> nrNodes; i++)
        if(dist[i] > maxDist)
            maxDist = dist[i];

    return maxDist + 1;
    // +1 bc the diameter is the max no of nodes on te longest chain in the tree
   // that is the no of edges + 1
}


int Graph::getMinSalesmanCost(const int &start, vector<int>& costs)
{
    int n = this -> nrNodes;
    vector<vector<int>> dp(n);
    for(int i = 0; i < n; i++)
    {
        dp[i].resize(1 << n);
        for(int j = 0; j < (1 << n); j++)
            dp[i][j] = INT_MAX;
    }
    dp[start][1] = 0;

    for(int mask = 0; mask < (1 << n); mask++)
    {
        for(int node = 0; node < n; node++)
        {
            if(dp[node][mask] == INT_MAX)
                continue;

            for(auto& edge: edges[node])
            {
                int neighbour = edge.neighbour;
                int cost = edge.cost;

                if(mask & (1 << neighbour))
                    continue; // neighbour already on this path

                int new_mask = mask | (1 << neighbour);
                if(dp[neighbour][new_mask] > dp[node][mask] + cost)
                    dp[neighbour][new_mask] = dp[node][mask] + cost;
            }
        }
    }
    int ans = INT_MAX;
    for(int i = 0; i < n; i++)
        if(dp[i][(1 << n) - 1] != INT_MAX && costs[i] != -1)
           ans = min(ans, dp[i][(1 << n) - 1] + costs[i]);

    if(ans == INT_MAX)
        return -1;
    return ans;
}
















