#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "adjacency.h"

class Graph {
public:
    Graph(int dim, int M) : dim_(dim), adj_(M) {}

    // add a point; returns node id
    int add_point(const std::vector<float>& vec);

    // add directed edge u -> v
    void add_edge(int u, int v) { adj_.add_neighbor(u, v); }

    // accessors
    int dim() const { return dim_; }
    int size() const { return (int)data_.size(); }

    const std::vector<float>& vec(int id) const { return data_[id]; }
    int degree(int u) const { return adj_.degree(u); }
    const int* neighbors(int u) const { return adj_.neighbors(u); }
    int* neighbors(int u) { return adj_.neighbors(u); } // if you want to mutate

private:
    int dim_;
    std::vector<std::vector<float>> data_; // simple per-node storage for now
    SingleLayerAdj adj_;                   // raw-block adjacency
};

#endif // GRAPH_H
