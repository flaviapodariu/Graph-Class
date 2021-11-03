#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include "Graph.h"
#include "DirectedGraph.h"
#include "UndirectedGraph.h"
using namespace std;


int main()
{
    int n, m, x, y,s;
    cin >> n >> m;
    UndirectedGraph *ug = new UndirectedGraph(n);
    for(int i = 1; i <= m; i++)
    {
        cin >> x >> y;
        ug -> addEdge(x, y, 0);
    }

    vector<vector<int>> bcc = ug -> biconnectedComponents();
    cout << bcc.size()<< "\n";
   for(auto it : bcc)
   {
       for(auto itt: it)
           cout << itt << " ";
       cout << "\n";
   }
//vector<int> sorted = ug ->TopologicalSorting();
//    for(int i = sorted.size(); i>=1; i--)
//        cout << sorted[i]<< " ";
    return 0;

}