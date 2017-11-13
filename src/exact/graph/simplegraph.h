#ifndef __SIMPLEGRAPH_H__
#define __SIMPLEGRAPH_H__

#include <stddef.h>
#include <stdbool.h>

#include <libaeds/memory/allocator.h>

#include "vertexset.h"


typedef struct SimpleGraph SimpleGraph;


SimpleGraph* new_simplegraph(const Allocator*, Vertex order);
SimpleGraph* new_complete_simplegraph(const Allocator*, Vertex order);

void delete_simplegraph(SimpleGraph**);

Vertex simplegraph_order(SimpleGraph*);

bool* simplegraph_edge(SimpleGraph*, Vertex, Vertex);


VertexSet simplegraph_vset(SimpleGraph*);

VertexSet simplegraph_neighborset(SimpleGraph*, Vertex);





#endif /* __SIMPLEGRAPH_H__ */
