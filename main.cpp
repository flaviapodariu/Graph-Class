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
    stack<int> ans = dg.topologicalSorting();
    while(!ans.empty())
    {
        fout << ans.top()<< " ";
        ans.pop();
    }
}
void BCC_INFO_ARENA()
{
    const rlim_t new_stacksize = 20000000;
    struct rlimit limit;
    getrlimit(RLIMIT_STACK, &limit);
    limit.rlim_cur = new_stacksize;
    setrlimit(RLIMIT_STACK, &limit);

    ifstream fin("biconex.in");
    ofstream fout("biconex.out");
    int n, m, x, y;
    fin >> n >> m;
    UndirectedGraph ug(n);
    for(int i = 1; i <= m; i++)
    {
        fin >> x >> y;
        ug.addEdge(x, y, 0);
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
        ug.addEdge(connections[i][0], connections[i][1], 0);

    return ug.criticalEdges();

}
void HAVEL_HAKIMI()
{
    int n;
    cin >> n;
    UndirectedGraph ug(n);
    cout << ug.havelHakimiAnswer();
}

int main()
{



    return 0;

}