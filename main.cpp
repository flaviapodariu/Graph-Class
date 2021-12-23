#include <iostream>
#include <fstream>
#include <vector>
#include "Graph.h"
#include <sys/resource.h> // posix header
#include "DirectedGraph.h"
#include "UndirectedGraph.h"
using namespace std;

void DFS_INFO_ARENA()
{
    ifstream fin("dfs.in");
    ofstream fout("dfs.out");
    int n, m, x, y;
    fin >> n >> m;
    UndirectedGraph ug(n);
    for(int i = 1; i <= m; i++)
    {
        fin >> x >> y;
        ug.addEdge(x, y);
    }
    fout << ug.nrConnectedComponents();
}



void BFS_INFO_ARENA()
{
    ifstream fin("bfs.in");
    ofstream fout("bfs.out");
    int n, m, x, y, s;
    fin >> n >> m >> s;
    DirectedGraph dg(n);
    for(int i = 1; i <= m; i++)
    {
        fin >> x >> y;
        dg.addEdge(x, y);
    }
    vector<int> ans = dg.getDistancesBFS(s);
    for(int i = 1 ; i <= dg.getNrNodes(); i++)
        fout << ans[i] << " ";
}



void SCC_INFO_ARENA()
{
    ifstream fin("ctc.in");
    ofstream fout("ctc.out");
    int n, m, x, y;
    fin >> n >> m;
    DirectedGraph dg(n);
    for(int i = 1; i <= m; i++)
    {
        fin >> x >> y;
        dg.addEdge(x, y);
    }
    vector<vector<int>> scc = dg.getStronglyConnected();
    fout << scc.size()<< "\n";

    for(auto &comp: scc)
    {
        for(auto &elem: comp)
            fout << elem << " ";
        fout << "\n";
    }
}



void TOPOLOGICAL_SORT_INFO_ARENA()
{
    ifstream fin("sortaret.in");
    ofstream fout("sortaret.out");
    int n, m, x, y;
    fin >> n >> m;
    DirectedGraph dg(n);
    for(int i = 1; i <= m; i++)
    {
        fin >> x >> y;
        dg.addEdge(x, y);
    }
    vector<int> ans = dg.topologicalSorting();
    for(int i = ans.size()-1; i >= 0; i--)
        fout << ans.at(i)<< " ";

}



void BCC_INFO_ARENA()
{
    const rlim_t new_stackSize = 20000000;
    struct rlimit limit;
    getrlimit(RLIMIT_STACK, &limit);
    limit.rlim_cur = new_stackSize;
    setrlimit(RLIMIT_STACK, &limit);

    ifstream fin("biconex.in");
    ofstream fout("biconex.out");
    int n, m, x, y;
    fin >> n >> m;
    UndirectedGraph ug(n);
    for(int i = 1; i <= m; i++)
    {
        fin >> x >> y;
        ug.addEdge(x, y);
    }
    vector<vector<int>> ans = ug.biconnectedComponents();

    fout << ans.size()<< " ";
    for(auto &comp: ans)
    {
        for(auto &elem: comp)
            fout << elem << " ";
        fout << "\n";
    }
}



vector<vector<int>> CRITICAL_CONN_LEETCODE(int n, vector<vector<int>>& connections)
{
    UndirectedGraph ug(n);
    int m = connections.size();
    for(int i = 0; i < m ; ++i)
        ug.addEdge(connections[i][0], connections[i][1]);

    return ug.criticalEdges();

}



void HAVEL_HAKIMI()
{
    int n, d;
    cout << "Insert the number of nodes: ";
    cin >> n;
    cout << "\n";
    cout << "Insert the degree of each node: ";
    UndirectedGraph ug(n);
    vector<int>degrees;
    for(int i = 0; i < ug.getNrNodes(); i++)
    {
        cin >> d;
        degrees.push_back(d);
    }
    cout << "\n";
    cout << ug.havelHakimi(degrees);
}



void MIN_SPANNING_TREE_INFO_ARENA()
{
    ifstream fin("apm.in");
    ofstream fout("apm.out");
    int n, m, x, y, c;
    fin >> n >> m;
    UndirectedGraph ug(n);
    for(int i = 1; i <= m; i++)
    {
        fin >> x >> y>> c;
        ug.addEdge(x, y, c);
    }
    int costMST = 0;
    vector<int> ans = ug.Graph::PrimMST(costMST);

    fout << costMST << "\n";
    fout << n - 1 << "\n";
    for(int i = 2; i < ans.size(); i++)
        fout<< ans[i] << " "<< i << "\n";
}



void DIJKSTRA_INFO_ARENA()
{
    ifstream fin("dijkstra.in");
    ofstream fout("dijkstra.out");
    int n, m, x, y, c;
    fin >> n >> m;
    Graph dg(n);
    for(int i = 1; i <= m; i++)
    {
        fin >> x >> y>> c;
        dg.setEdge(x, y, c);
    }

    vector<int> ans = dg.Dijkstra(1);
    for(unsigned i = 2; i < ans.size(); i++)
        if(ans[i] != INT_MAX)
          fout << ans[i]<< " ";
        else
          fout << 0 << " ";
}



void BELLMAN_FORD_INFO_ARENA()
{
    ifstream fin("bellmanford.in");
    ofstream fout("bellmanford.out");
    int n, m, x, y, c;
    fin >> n >> m;
    Graph g(n);
    for(int i = 1; i <= m; i++)
    {
        fin >> x >> y>> c;
        g.setEdge(x, y, c);
    }

    vector<int> ans = g.BellmanFord(1);
    if(ans[0] == -1)
        fout << "Ciclu negativ!";
    else
    for(unsigned i = 2; i < ans.size(); i++)
        fout << ans[i]<< " ";
}



 void DISJOINT_SETS_INFO_ARENA()
{
    ifstream fin("disjoint.in");
    ofstream fout("disjoint.out");
    int n, m, x, y, op;
    fin >> n >> m;
    vector<bool> sameGroup;
    vector<int> root(n+1);

    for(int i = 1; i <= n; i++)
        root[i] = i;

    for(int i = 1; i <= m; i++)
    {
        fin >> op >>x >> y;
        Graph::disjointSets(op, x, y, sameGroup, root);
    }
    for(int i = 0; i < sameGroup.size(); i++)
        if(sameGroup[i])
            fout << "DA" << "\n";
        else
            fout << "NU" << "\n";
}



void ROY_FLOYD_INFO_ARENA()
{
    ifstream fin("royfloyd.in");
    ofstream fout("royfloyd.out");
    int n, cost;
    fin >> n;
    Graph g(n);

    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
        {
            fin >> cost;
            g.setEdge(i, j, cost);
            //setEdge will push_back j starting from index 0!
        }
    vector<vector<int>> ans = g.getMinCostMatrix();
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
            fout << ans[i][j] << " ";
        fout << "\n";
    }

}



void TREE_DIAMETER_INFO_ARENA()
{
    ifstream fin("darb.in");
    ofstream fout("darb.out");
    int n, x, y;
    fin >> n;
    UndirectedGraph ug(n);
    for(int i = 1; i < n; i++)
    {
        fin >> x >> y;
        ug.addEdge(x, y);
    }
    fout <<  ug.Graph::getTreeDiameter(1);

}



void MAX_FLOW_INFO_ARENA()  //60p
{
    ifstream fin("maxflow.in");
    ofstream fout("maxflow.out");
    int n, m, x, y, capacity;
    fin >> n >> m;
    DirectedGraph dg(n);

    for(int i = 0; i < m; i++)
    {
        fin >> x >> y >> capacity;
        dg.addEdge(x, y, 0, capacity);
    }
    vector<vector<int>> cap;
    cap.resize(n+1);

    for(int i = 1; i <= n; i++)
    {
        cap[i].resize(n+1, 0);
        for(auto& it: dg.getNeighbours(i))
            cap[i][it.neighbour] = it.capacity;
    }

    fout << dg.getMaxFlow(1, n, cap);

}



void TRAVELLING_SALESMAN_INFO_ARENA()
{
    ifstream fin("hamilton.in");
    ofstream fout("hamilton.out");
    int n, m, x, y, cost;
    fin >> n >> m;
    DirectedGraph dg(n);
    vector<vector<int>> costs(n);
    for(int i = 0; i < n; i++)
        costs[i].resize(n, -1);

    for(int i = 0; i < m; i++)
    {
        fin >> x >> y >> cost;
        dg.addEdge(x, y, cost);
        costs[y][x] = cost;
    }

   int ans = dg.Graph::getMinSalesmanCost(0, costs[0]); // start, costs[start]
   if(ans != -1)
       fout << ans;
   else
       fout << "Nu exista solutie";
}
int main()
{
    // Run a problem solver or make one yourself
    return 0;
}