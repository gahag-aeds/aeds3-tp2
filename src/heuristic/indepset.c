#include "indepset.h"

#include <assert.h>
#include <stdbool.h>
#include <string.h>

#include <libaeds/data/resources/memory.h>


struct IndepSet {
  const Allocator* allocator;
  
  uint32_t order
         , sum;
  
  bool vertexes[];
};


IndepSet* new_indepset_complete(const Allocator* al, uint32_t order) {
  assert(al != NULL);
  assert(order > 0);
  
  IndepSet* set = al_alloc_fma(al, sizeof(IndepSet), order, sizeof(bool));
  
  *set = (IndepSet) {
    .allocator = al,
    
    .order = order,
    .sum = 0,
  };
  
  memset(set->vertexes, true, order * sizeof(bool));
  
  return set;
}

ResourceDisposer indepset_disposer(const IndepSet* set) {
  assert(set != NULL);
  return rs_disposer_al(set->allocator);
}


uint32_t* indepset_order(IndepSet* set) {
  assert(set != NULL);
  return &set->order;
}

uint32_t* indepset_sum(IndepSet* set) {
  assert(set != NULL);
  return &set->sum;
}

bool* indepset_vertex(IndepSet* set, uint32_t index) {
  assert(set != NULL);
  
  return &set->vertexes[index];
}
