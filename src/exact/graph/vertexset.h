#ifndef __VERTEXSET_H__
#define __VERTEXSET_H__

#include <stdbool.h>
#include <stdint.h>

#include "vertex.h"


// A set of vertexes is a binary number.
// The bit at position i indicates if the i vertex is in the set.
// Maximum set size, as specified: 30 vertexes. Therefore, 32 bits are enough.
typedef uint32_t VertexSet;


extern const VertexSet vset_empty; // The empty set
extern const VertexSet vset_full;  // The set with all vertices.

bool vset_in(VertexSet, Vertex); // Checks is a vertex is in the set. O(1)

Vertex vset_order(VertexSet); // The number of vertices in the set. O(1)
// The index of the vertex in the set with lowest index.
// The result is undefined if the set is empty.
// Complexity: O(1)
Vertex vset_first(VertexSet);
// The index of the vertex in the set with highest index.
// The result is undefined if the set is empty.
// Complexity: O(1)
Vertex vset_last(VertexSet);

VertexSet vset_cons(Vertex); // A unitary set containing the given vertex. O(1)

VertexSet vset_comp(VertexSet); // Set complement. O(1)

VertexSet vset_add(VertexSet, Vertex); // Add a vertex to a set. O(1)
VertexSet vset_sub(VertexSet, Vertex); // Remove a vertex from a set. O(1)

VertexSet vset_minus(VertexSet, VertexSet);     // Set minus. O(1)
VertexSet vset_union(VertexSet, VertexSet);     // Set union. O(1)
VertexSet vset_intersect(VertexSet, VertexSet); // Set intersection. O(1)


#endif /* __VERTEXSET_H__ */
