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
    cin >> n >> m>> s;
    DirectedGraph *ug = new DirectedGraph(n);
    for(int i = 1; i <= m; i++)
    {
        cin >> x >> y;
        ug -> addEdge(x, y);
    }
   vector<int>d = ug->minDistanceBFS(s);
    for(auto it: d)
        cout << it<< " ";
//     ug -> printEdges(36);
    return 0;

}