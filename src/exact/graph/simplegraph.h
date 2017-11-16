#ifndef __SIMPLEGRAPH_H__
#define __SIMPLEGRAPH_H__

#include "vertex.h"
#include "vertexset.h"


#define simplegraph_maxorder 64

// A simple graph is an unweighted, undirected
// graph containing no loops or multiple edges.
// This implementation uses an adjacency list to store the edges.
// The list is represented using integers bitwise.
// The maximum supported order is 64.
// Space complexity: O(n)
typedef struct SimpleGraph {
  Vertex order;
  VertexSet neighbors[simplegraph_maxorder];
  Vertex degree[simplegraph_maxorder];
} SimpleGraph;


// Create a complete SimpleGraph. That is, a SimpleGraph with all possible edges.
// Complexity: O(n)
void simplegraph_complete(SimpleGraph*);

// Query a edge in the SimpleGraph. `v` must be different from `w`.
bool simplegraph_get_edge(SimpleGraph*, Vertex v, Vertex w);
// Add a edge to the SimpleGraph. `v` must be different from `w`.
void simplegraph_add_edge(SimpleGraph*, Vertex v, Vertex w);
// Remove a edge from the SimpleGraph. `v` must be different from `w`.
void simplegraph_rem_edge(SimpleGraph*, Vertex v, Vertex w);

// Get the degree of a vertex in the SimpleGraph.
Vertex simplegraph_degree(SimpleGraph*, Vertex);


// Get the VertexSet containing all the vertices of the graph.
VertexSet simplegraph_vset(const SimpleGraph*);

// Get the VertexSet of the neighbors of the given vertex.
VertexSet simplegraph_neighborset(const SimpleGraph*, Vertex);


#endif /* __SIMPLEGRAPH_H__ */
