#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include <libaeds/data/resources/memory.h>
#include <libaeds/data/resources/resource.h>
#include <libaeds/memory/allocator.h>

#include "graph/bron-kerbosch.h"
#include "graph/simplegraph.h"
#include "graph/vertex.h"
#include "graph/vertexset.h"


int main() {
  const Allocator allocator = std_allocator(abort);
  Resources res = new_resources(&allocator);
  
  Vertex corners;
  uint16_t neighbors;
  
  
  if (scanf("%" SCNu8 " %" SCNu16, &corners, &neighbors) != 2)
    return delete_resources(&res), -1;
  
  
  uint32_t* demands = rs_register_alloc(
    &allocator, corners, sizeof(uint32_t),
    rs_disposer_al(&allocator),
    &res
  );
  
  for (uint8_t i = 0; i < corners; i++)
    if (scanf("%" SCNu32, &demands[i]) != 1)
      return delete_resources(&res), -1;;
  
  
  SimpleGraph* g = new_complete_simplegraph(&allocator, corners); {
    rs_register(&g, simplegraph_disposer(), &res);
  }
  
  for (uint16_t i = 0; i < neighbors; i++) {
    Vertex from, to;
    
    if (scanf("%" SCNu8 " %" SCNu8, &from, &to) != 2)
      return delete_resources(&res), -1;
    
    from--; // Input is 1-indexed.
    to--;
    
    *simplegraph_edge(g, from, to) = false; // Complement graph
  }
  
  
  OptimumMaxClique omc = optimum_bronkerbosch(g, demands);
  
  
  printf("%" PRIu8 " %" PRIu64 "\n", omc.order, omc.sum);
  VertexSet s = omc.clique;
  for ( // Iterate over the bits in the clique set.
    Vertex v = vset_first(s);
    s != vset_empty;
    s = vset_sub(s, v), v = vset_first(s)
  ) {
    if (printf("%" PRIu8 " ", v + 1) < 1)
      return delete_resources(&res), -1;
  }
  if (puts("") < 0)
    return delete_resources(&res), -1;
  
  
  return delete_resources(&res), 0;
}
