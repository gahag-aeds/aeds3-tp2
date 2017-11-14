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
      VertexSet S = R;
      for ( // Iterate over the bits in R.
        Vertex v = vset_first(S);
        S != vset_empty;
        S = vset_sub(S, v), v = vset_first(S)
      )
        sum += weights[v];
      
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
  
  // Choose the pivot u in P as the vertex with most neighbors.
  Vertex u = vset_first(P);
  VertexSet S = vset_sub(P, u);
  for ( // Iterate over the bits in P.
    Vertex v = vset_first(S);
    S != vset_empty;
    S = vset_sub(S, v), v = vset_first(S)
  )
    if (simplegraph_degree(g, v) > simplegraph_degree(g, u))
      u = v;
  
  S = vset_minus(P, simplegraph_neighborset(g, u));
  for ( // Iterate over the bits in P.
    Vertex v = vset_first(S);
    S != vset_empty;
    S = vset_sub(S, v), v = vset_first(S)
  ) {
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
