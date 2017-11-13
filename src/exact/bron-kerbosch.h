#ifndef __BRON_KERBOSCH_H__
#define __BRON_KERBOSCH_H__

#include <stddef.h>
#include <stdint.h>

#include "graph/simplegraph.h"


typedef struct OptimumMaxClique {
  Vertex order;
  uint64_t sum;
  VertexSet clique;
} OptimumMaxClique;


OptimumMaxClique optimum_bronkerbosch(SimpleGraph* g, uint32_t* weights);


#endif /* __BRON_KERBOSCH_H__ */
