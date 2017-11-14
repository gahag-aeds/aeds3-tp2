#include "simplegraph.h"

#include <assert.h>
#include <stddef.h>
#include <string.h>


void simplegraph_complete(SimpleGraph* g) {
  assert(g != NULL);
  
  for (Vertex i = 0; i < g->order; i++)
    g->neighbors[i] = vset_sub(vset_full, i); // All but the self loop.
  
  memset(g->degree, g->order, sizeof(g->degree));
}


bool simplegraph_get_edge(SimpleGraph* g, Vertex i, Vertex j) {
  assert(g != NULL);
  assert(i < g->order && j < g->order);
  assert(i != j);
  
  return vset_in(g->neighbors[i], j);
}

void simplegraph_add_edge(SimpleGraph* g, Vertex i, Vertex j) {
  assert(g != NULL);
  assert(i < g->order && j < g->order);
  assert(i != j);
  
  g->neighbors[i] = vset_add(g->neighbors[i], j);
  g->neighbors[j] = vset_add(g->neighbors[j], i);
  
  g->degree[i]++;
  g->degree[j]++;
}

void simplegraph_rem_edge(SimpleGraph* g, Vertex i, Vertex j) {
  assert(g != NULL);
  assert(i < g->order && j < g->order);
  assert(i != j);
  
  g->neighbors[i] = vset_sub(g->neighbors[i], j);
  g->neighbors[j] = vset_sub(g->neighbors[j], i);
  
  g->degree[i]--;
  g->degree[j]--;
}


Vertex simplegraph_degree(SimpleGraph* g, Vertex v) {
  assert(g != NULL);
  assert(v < g->order);
  
  return g->degree[v];
}



VertexSet simplegraph_vset(const SimpleGraph* g) {
  assert(g != NULL);
  return vset_full >> (sizeof(vset_full) * 8 - g->order);
}

VertexSet simplegraph_neighborset(const SimpleGraph* g, Vertex v) {
  assert(g != NULL);
  assert(v < g->order);
  
  return g->neighbors[v];
}
