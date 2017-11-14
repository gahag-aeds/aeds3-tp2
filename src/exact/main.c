#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include <libaeds/memory/allocator.h>

#include "graph/bron-kerbosch.h"
#include "graph/simplegraph.h"
#include "graph/vertex.h"
#include "graph/vertexset.h"


int main() {
  const Allocator allocator = std_allocator(abort);
  
  Vertex corners;
  uint16_t neighbors;
  
  if (scanf("%" SCNu8 " %" SCNu16, &corners, &neighbors) != 2)
    return -1;
  
  
  uint32_t* demands = al_alloc(&allocator, corners, sizeof(*demands));
  
  for (uint8_t i = 0; i < corners; i++)
    if (scanf("%" SCNu32, &demands[i]) != 1)
      return al_dealloc(&allocator, demands), -1;
  
  
  SimpleGraph g; {
    g.order = corners;
    simplegraph_complete(&g);
  }
  
  for (uint16_t i = 0; i < neighbors; i++) {
    Vertex from, to;
    
    if (scanf("%" SCNu8 " %" SCNu8, &from, &to) != 2)
      return al_dealloc(&allocator, demands), -1;
    
    from--; // Input is 1-indexed.
    to--;
    
    simplegraph_rem_edge(&g, from, to); // Complement graph
  }
  
  
  OptimumMaxClique omc = optimum_bronkerbosch(&g, demands);
  
  
  printf("%" PRIu8 " %" PRIu64 "\n", omc.order, omc.sum);
  VertexSet s = omc.clique;
  for ( // Iterate over the bits in the clique set.
    Vertex v = vset_first(s);
    s != vset_empty;
    s = vset_sub(s, v), v = vset_first(s)
  ) {
    if (printf("%" PRIu8 " ", v + 1) < 1)
      return al_dealloc(&allocator, demands), -1;
  }
  if (puts("") < 0)
    return al_dealloc(&allocator, demands), -1;
  
  
  return al_dealloc(&allocator, demands), 0;
}
