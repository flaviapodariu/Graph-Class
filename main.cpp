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
    DirectedGraph *ug = new DirectedGraph(n);
    for(int i = 1; i <= m; i++)
    {
        cin >> x >> y;
        ug -> addEdge(x, y, 0);
    }

    stack<int> sorted = ug -> TopologicalSorting();
    while(!sorted.empty())
    {
        cout << sorted.top()<< " ";
        sorted.pop();
    }
//vector<int> sorted = ug ->TopologicalSorting();
//    for(int i = sorted.size(); i>=1; i--)
//        cout << sorted[i]<< " ";
    return 0;

}