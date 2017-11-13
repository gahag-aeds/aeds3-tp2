#ifndef __VERTEXSET_H__
#define __VERTEXSET_H__

#include <stdbool.h>
#include <stdint.h>

#include "vertex.h"


typedef uint32_t VertexSet;


extern const VertexSet vset_empty;
extern const VertexSet vset_full;

bool vset_in(VertexSet, Vertex);

Vertex vset_order(VertexSet);
Vertex vset_first(VertexSet);
Vertex vset_last(VertexSet);

VertexSet vset_cons(Vertex);

VertexSet vset_comp(VertexSet);

VertexSet vset_add(VertexSet, Vertex);
VertexSet vset_sub(VertexSet, Vertex);

VertexSet vset_minus(VertexSet, VertexSet);
VertexSet vset_union(VertexSet, VertexSet);
VertexSet vset_intersect(VertexSet, VertexSet);


#endif /* __VERTEXSET_H__ */
