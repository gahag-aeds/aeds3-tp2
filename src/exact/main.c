#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include <libaeds/memory/allocator.h>

#include "bron-kerbosch.h"
#include "graph/simplegraph.h"
#include "graph/vertex.h"
#include "graph/vertexset.h"


int main() {
  const Allocator allocator = std_allocator(abort);
  
  Vertex corners;
  uint16_t neighbors;
  
  
  scanf("%hhu %hu", &corners, &neighbors);
  
  
  uint32_t* demands = al_alloc(&allocator, corners, sizeof(uint32_t));
  
  for (uint8_t i = 0; i < corners; i++)
    scanf("%u", &demands[i]);
  
  
  SimpleGraph* g = new_complete_simplegraph(&allocator, corners);
  
  for (unsigned long i = 0; i < neighbors; i++) {
    unsigned short from, to;
    
    scanf("%hu %hu", &from, &to);
    from--;
    to--;
    
    *simplegraph_edge(g, from, to) = false; // Complement graph
  }
  
  OptimumMaxClique omc = optimum_bronkerbosch(g, demands);
  
  printf("%" PRIu8 " %" PRIu64 "\n", omc.order, omc.sum);
  for (Vertex v = vset_first(omc.clique), top = vset_last(omc.clique); v <= top; v++) {
    if (!vset_in(omc.clique, v))  // v is not in the set
      continue;
    
    printf("%" PRIu8 " ", v + 1);
  }
  puts("");
  
  delete_simplegraph(&g);
  al_dealloc(&allocator, demands);
    
  return 0;
}
