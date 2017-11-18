#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include <libaeds/memory/allocator.h>
#include <libaeds/data/resources/resource.h>
#include <libaeds/data/resources/memory.h>

#include "indepset.h"


int main() {
  const Allocator allocator = std_allocator(abort);
  Resources res = new_resources(&allocator);
  
  
  uint32_t corners;
  uint64_t neighbors;
  
  if (scanf("%" SCNu32 " %" SCNu64, &corners, &neighbors) != 2)
    return delete_resources(&res), -1;
  
  
  IndepSet* iset = new_indepset_complete(&allocator, corners);
  rs_register(iset, indepset_disposer(iset), &res);
  
  
  uint32_t* demands = rs_register_alloc(
    &allocator, corners, sizeof(*demands),
    rs_disposer_al(&allocator),
    &res
  );
  
  for (uint32_t i = 0; i < corners; i++) {
    if (scanf("%" SCNu32, &demands[i]) != 1)
      return delete_resources(&res), -1;
    
    *indepset_sum(iset) += demands[i];
  }
  
  
  while (neighbors > 0) {
    uint32_t from, to;
    
    if (scanf("%" SCNu32 " %" SCNu32, &from, &to) != 2)
      return delete_resources(&res), -1;
    
    from--; // Input is 1-indexed.
    to--;
    
    if (*indepset_vertex(iset, from) && *indepset_vertex(iset, to)) {
      // Neighbors detected, must remove one:
      *indepset_vertex(iset, to) = false;
      *indepset_order(iset) -= 1;
      *indepset_sum(iset) -= demands[to];
    }
    
    neighbors--;
  }
  
  
  printf("%" PRIu8 " %" PRIu32 "\n", *indepset_order(iset), *indepset_sum(iset));
  for (uint32_t i = 0; i < corners; i++)
    if (*indepset_vertex(iset, i))
      if (printf("%" PRIu8 " ", i + 1) < 1)
        return delete_resources(&res), -1;
  
  if (puts("") < 0)
    return delete_resources(&res), -1;
  
  
  return delete_resources(&res), 0;
}
