#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include "Graph.h"
//#include <sys/resource.h>
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
        ug.addEdge(x, y, 0);
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
        dg.addEdge(x, y, 0);
    }
    vector<int> ans = dg.minDistanceBFS(s);
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
        dg.addEdge(x, y, 0);
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
        dg.addEdge(x, y, 0);
    }
    vector<int> ans = dg.topologicalSorting();
    for(int i = ans.size()-1; i >= 0; i--)
        fout << ans.at(i)<< " ";

}
//void BCC_INFO_ARENA()
//{
//    const rlim_t new_stackSize = 20000000;
//    struct rlimit limit;
//    getrlimit(RLIMIT_STACK, &limit);
//    limit.rlim_cur = new_stackSize;
//    setrlimit(RLIMIT_STACK, &limit);
//
//    ifstream fin("biconex.in");
//    ofstream fout("biconex.out");
//    int n, m, x, y;
//    fin >> n >> m;
//    UndirectedGraph ug(n);
//    for(int i = 1; i <= m; i++)
//    {
//        fin >> x >> y;
//        ug.addEdge(x, y, 0);
//    }
//    vector<vector<int>> ans = ug.biconnectedComponents();
//
//    fout << ans.size()<< " ";
//    for(auto &comp: ans)
//    {
//        for(auto &elem: comp)
//            fout << elem << " ";
//        fout << "\n";
//    }
//}
vector<vector<int>> CRITICAL_CONN_LEETCODE(int n, vector<vector<int>>& connections)
{
    UndirectedGraph ug(n);
    int m = connections.size();
    for(int i = 0; i < m ; ++i)
        ug.addEdge(connections[i][0], connections[i][1], 0);

    return ug.criticalEdges();

}
void HAVEL_HAKIMI()
{
    int n, d;
    cin >> n;
    UndirectedGraph ug(n);
    vector<int>degrees;
    for(int i = 0; i < ug.getNrNodes(); i++)
    {
        cin >> d;
        degrees.push_back(d);
    }
    cout << ug.havelHakimi(degrees);
}
void MIN_SPANNING_TREE_INFO_ARENA()
{
    ifstream fin("apm.in");
    ofstream fout("apm.out");
    int n, m, x, y, c;
    cin >> n >> m;
    Graph ug(n);
    for(int i = 1; i <= m; i++)
    {
        cin >> x >> y>> c;
        ug.setEdge(x, y, c);
        ug.setEdge(y, x, c);
    }
    int costMST = 0;
    vector<int> ans = ug.PrimMST(costMST);

    cout << costMST << "\n";
    cout << n - 1 << "\n";
    for(int i = 2; i < ans.size(); i++)
        cout<< ans[i] << " "<< i << "\n";
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

    vector<int> ans = dg.Dijkstra();
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
    Graph ug(n);
    for(int i = 1; i <= m; i++)
    {
        fin >> x >> y>> c;
        ug.setEdge(x, y, c);
    }

    vector<int> ans = ug.BellmanFord();
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
    Graph dg(n);
    vector<bool> sameGroup;
    vector<int> root(n+1);

    for(int i = 1; i <= n; i++)
        root[i] = i;

    for(int i = 1; i <= m; i++)
    {
        fin >> op >>x >> y;
        dg.disjointSets(op, x, y, sameGroup, root);
    }
    for(int i = 0; i < sameGroup.size(); i++)
        if(sameGroup[i])
            fout << "DA" << "\n";
        else
            fout << "NU" << "\n";
}
int main()
{
   DISJOINT_SETS_INFO_ARENA();
    return 0;
}