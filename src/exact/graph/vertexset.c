#include "vertexset.h"

#include <libaeds/data/bits.h>


const VertexSet vset_empty = 0;
const VertexSet vset_full = -1;


bool vset_in(VertexSet s, Vertex v) {
  return testbit_32(s, v);
}


Vertex vset_order(VertexSet s) {
  return popcount_32(s);
}

Vertex vset_first(VertexSet s) {
  return lsb_32(s);
}

Vertex vset_last(VertexSet s) {
  return msb_32(s);
}


VertexSet vset_cons(Vertex v) {
  return 1 << v;
}


VertexSet vset_comp(VertexSet s) {
  return ~s;
}


VertexSet vset_add(VertexSet s, Vertex v) {
  return vset_union(s, vset_cons(v));
}

VertexSet vset_sub(VertexSet s, Vertex v) {
  return vset_minus(s, vset_cons(v));
}


VertexSet vset_minus(VertexSet s1, VertexSet s2) {
  return vset_intersect(s1, vset_comp(s2));
}

VertexSet vset_union(VertexSet s1, VertexSet s2) {
  return s1 | s2;
}

VertexSet vset_intersect(VertexSet s1, VertexSet s2) {
  return s1 & s2;
}
