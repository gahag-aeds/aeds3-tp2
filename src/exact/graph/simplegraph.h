#ifndef __SIMPLEGRAPH_H__
#define __SIMPLEGRAPH_H__

#include <stddef.h>
#include <stdbool.h>

#include <libaeds/data/resources/resource.h>
#include <libaeds/memory/allocator.h>

#include "vertexset.h"


// A simple graph is an unweighted, undirected
// graph containing no graph loops or multiple edges.
// This implementation uses an adjacency triangle to store the edges.
// Space complexity: O(n²)
typedef struct SimpleGraph SimpleGraph;


// Create a SimpleGraph with no edges.
// Complexity: O(1)
SimpleGraph* new_simplegraph(const Allocator*, Vertex order);
// Create a complete SimpleGraph. That is, a SimpleGraph with all possible edges.
// Complexity: O(1)
SimpleGraph* new_complete_simplegraph(const Allocator*, Vertex order);

// Delete a SimpleGraph, deallocating the memory used via the
// allocator specified in new*_simplegraph.
// Complexity: O(1)
void delete_simplegraph(SimpleGraph**);
// The disposer for a simplegraph.
ResourceDisposer simplegraph_disposer(void);

// Get the order of a SimpleGraph.
Vertex simplegraph_order(const SimpleGraph*);

// Get the pointer to a given edge in the SimpleGraph.
// `v` must be different from `w`.
// The pointer allows to read and set the edge.
bool* simplegraph_edge(SimpleGraph*, Vertex v, Vertex w);


// Get the VertexSet containing all the vertices of the graph.
VertexSet simplegraph_vset(const SimpleGraph*);

// Get the VertexSet of the neighbors of the given vertex.
VertexSet simplegraph_neighborset(const SimpleGraph*, Vertex);


#endif /* __SIMPLEGRAPH_H__ */
