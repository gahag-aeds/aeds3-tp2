#include "simplegraph.h"

#include <assert.h>
#include <string.h>


struct SimpleGraph {
  const Allocator* allocator;
  
  Vertex order;
  bool edges[]; // Adjacency triangle.
};


SimpleGraph* new_simplegraph(const Allocator* allocator, Vertex order) {
  assert(allocator != NULL);
  assert(order > 1);
  
  const size_t max_size = (order * order - order) / 2;
  SimpleGraph* g = al_alloc_clear_fma(
    allocator,
    sizeof(SimpleGraph),
    max_size,
    sizeof(bool)
  );
  
  *g = (SimpleGraph) {
    .allocator = allocator,
    
    .order    = order,
  };
  
  return g;
}

SimpleGraph* new_complete_simplegraph(const Allocator* allocator, Vertex order) {
  assert(allocator != NULL);
  assert(order > 1);
  
  const size_t max_size = (order * order - order) / 2;
  SimpleGraph* g = al_alloc_fma(
    allocator,
    sizeof(SimpleGraph),
    max_size,
    sizeof(bool)
  );
    
  *g = (SimpleGraph) {
    .allocator = allocator,
    
    .order    = order,
  };
  
  memset(g->edges, true, sizeof(bool[max_size]));
  
  return g;
}


void delete_simplegraph(SimpleGraph** g) {
  assert(g != NULL);
  
  if (*g != NULL) {
    al_dealloc((*g)->allocator, *g);
    *g = NULL;
  }
}


Vertex simplegraph_order(SimpleGraph* g) {
  assert(g != NULL);
  return g->order;
}


bool* simplegraph_edge(SimpleGraph* g, Vertex i, Vertex j) {
  assert(g != NULL);
  assert(i < simplegraph_order(g) && j < simplegraph_order(g));
  
  if (i > j) {  // Swap.
    Vertex tmp = i;
    i = j;
    j = tmp;
  }
  
  const size_t vertices = simplegraph_order(g);
  // Indexing for the adjacency triangle:
  const size_t index = (2*i*vertices + 2*j - i*i - 3*i - 2) / 2;
  
  return &g->edges[index];
}



VertexSet simplegraph_vset(SimpleGraph* g) {
  assert(g != NULL);
  return vset_full >> (32 - simplegraph_order(g));
}

VertexSet simplegraph_neighborset(SimpleGraph* g, Vertex v) {
  assert(g != NULL);
  assert(v < simplegraph_order(g));
  
  VertexSet set = vset_empty;
  
  for (Vertex i = 0; i < simplegraph_order(g); i++)
    if (i != v && *simplegraph_edge(g, v, i))
        set = vset_add(set, i);
  
  return set;
}
