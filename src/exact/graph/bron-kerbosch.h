#ifndef __BRON_KERBOSCH_H__
#define __BRON_KERBOSCH_H__

#include <stddef.h>
#include <stdint.h>

#include "simplegraph.h"


// A optimum maximum clique is the maxiaml clique in a
// graph in which the sum of the vertices' weights is optimal.
typedef struct OptimumMaxClique {
  Vertex order;     // The order of the clique.
  uint64_t sum;     // The sum of the vertices's weights.
  VertexSet clique; // The clique set.
} OptimumMaxClique;


// The Bron-Kerbosch algorithm to list all maximal cliques in a graph,
// modified to find the OptimumMaxClique.
// Complexity: worst case O(3^(n/3))
OptimumMaxClique optimum_bronkerbosch(SimpleGraph* g, uint32_t* weights);


#endif /* __BRON_KERBOSCH_H__ */
