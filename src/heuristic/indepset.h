#ifndef __INDEPSET_H__
#define __INDEPSET_H__

#include <stdint.h>

#include <libaeds/memory/allocator.h>
#include <libaeds/data/resources/resource.h>


// A independent set in a graph.
typedef struct IndepSet IndepSet;


// Create a independent set with all vertices for a graph of the given order.
IndepSet* new_indepset_complete(const Allocator*, uint32_t order);
ResourceDisposer indepset_disposer(const IndepSet*);

uint32_t* indepset_order(IndepSet*); // The order of the independent set.
uint32_t* indepset_sum(IndepSet*);   // The sum of the weights of the vertexes in the set.
bool* indepset_vertex(IndepSet*, uint32_t index); // Pointer to the bool that defines
                                                  // whether the given vertex is in the set.

#endif /* __INDEPSET_H__ */
