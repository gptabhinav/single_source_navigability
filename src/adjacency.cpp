#include "adjacency.h"
#include <cstring>   // std::memset
#include <cassert>

SingleLayerAdj::SingleLayerAdj(int M) : M_(M) {
    assert(M_ > 0);
    block_size_bytes_ = (size_t)(1 + M_) * sizeof(int);
    storage_.reserve(0); // will grow as nodes are added
}

int SingleLayerAdj::add_node() {
    // append a zeroed block: degree=0, neighbors are garbage but degree controls reads
    size_t old_bytes = storage_.size();
    storage_.resize(old_bytes + block_size_bytes_);
    std::memset(storage_.data() + old_bytes, 0, block_size_bytes_);
    return (int)num_nodes_++;
}

void SingleLayerAdj::add_neighbor(int u, int v) {
    assert(u >= 0 && (size_t)u < num_nodes_);
    assert(v >= 0 && (size_t)v < num_nodes_);
    // degree pointer is first int in block
    int* deg_ptr = reinterpret_cast<int*>(block_ptr(u));
    int deg = *deg_ptr;
    if (deg >= M_) {
        // capacity full — for now just ignore; later we’ll add pruning/diversification
        return;
    }
    int* nbrs = deg_ptr + 1; // neighbors array starts right after degree
    nbrs[deg] = v;
    *deg_ptr = deg + 1;
}

int SingleLayerAdj::degree(int u) const {
    assert(u >= 0 && (size_t)u < num_nodes_);
    const int* deg_ptr = reinterpret_cast<const int*>(block_ptr(u));
    return *deg_ptr;
}

int* SingleLayerAdj::neighbors(int u) {
    assert(u >= 0 && (size_t)u < num_nodes_);
    int* deg_ptr = reinterpret_cast<int*>(block_ptr(u));
    return deg_ptr + 1;
}

const int* SingleLayerAdj::neighbors(int u) const {
    assert(u >= 0 && (size_t)u < num_nodes_);
    const int* deg_ptr = reinterpret_cast<const int*>(block_ptr(u));
    return deg_ptr + 1;
}
