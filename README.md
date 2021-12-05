# Graph-Class

This project aims to solve lots of the graph related problems in an OOP manner.

## General Ideas and Structure
 
* Graph
     * UndirectedGraph
     * DirectedGraph

 Both classes publicly inherit from the base class, Graph.

> For scalability reasons, the edges' properties are kept in a struct, that can be updated anytime with minimal changes:

```c++
struct edge
{
    int node;
    int neighbour;
    long cost;

};
``` 
The Graph class only has 2 data members:
   * `int nrNodes` = number of nodes 
   * `vector<vector<edge>> edges` = adjacency list of edges

## Creating a graph. Constructors
All the constructors are parameterized, and they only take the number of nodes that the graph will have. Using this number, it also allocates enough memory for the adjacency list.

For example:
   > `Graph g(5)` will create a graph with 5 nodes on the stack
   > 
The UndirectedGraph and DirectedGraph constructors just call the Graph's constructor, since they don't have specific data members.

Basically, calling `UndirectedGraph g(5)` would have the same behaviour as above, the only difference being the type of the object that is created.

## Setting edges
The directed and undirected graphs, are very similar to one another, the only difference being their adjacency list.
They both call the inherited method `setEdge(int source, int destination, int cost)`, but the undirected graph would need one more call with the first two parameters inverted, like so: `setEdge(int destination, int source , int cost)`

:exclamation: Note that the actual method for setting edges in a specific graph (directed/ undirected) is `addEdge(int source, int destination, int cost)`, implemented in a different way in both classes using the inherited methods just mentioned before.
