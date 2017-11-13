#include "bron-kerbosch.h"

#include <assert.h>


static void bronkerbosch(
  SimpleGraph* g,
  uint32_t* weights,
  OptimumMaxClique* omc,
  VertexSet R,
  VertexSet P,
  VertexSet X
) {
  if (P == vset_empty) {
    if (X == vset_empty) { // P and X are empty: report R as a maximal clique.
      uint64_t sum = 0;
      for (Vertex v = vset_first(R), top = vset_last(R); v <= top; v++) {
        if (!vset_in(R, v))  // v is not in R
          continue;
        
        sum += weights[v];
      }
    
      if (sum > omc->sum)
        *omc = (OptimumMaxClique) {
          .order  = vset_order(R),
          .sum    = sum,
          .clique = R
        };
    }
    
    return; // P is empty, just return.
  }
  
  // P is not empty:
  for (Vertex v = vset_first(P), top = vset_last(P); v <= top; v++) {
    if (!vset_in(P, v))  // v is not in P
      continue;
    
    VertexSet N = simplegraph_neighborset(g, v);
    
    bronkerbosch(
      g, weights, omc,
      vset_add(R, v),
      vset_intersect(P, N),
      vset_intersect(X, N)
    );
    
    P = vset_sub(P, v);
    X = vset_add(X, v);
  }
}

OptimumMaxClique optimum_bronkerbosch(SimpleGraph* g, uint32_t* weights) {
  assert(g != NULL);
  assert(weights != NULL);
  
  OptimumMaxClique omc = {
    .order  = 0,
    .sum    = 0,
    .clique = vset_empty
  };
  
  bronkerbosch(g, weights, &omc, vset_empty, simplegraph_vset(g), vset_empty);
  
  return omc;
}
