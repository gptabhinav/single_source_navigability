#ifndef ADJACENCY_H
#define ADJACENCY_H

#include <vector>
#include <cstddef> // size_t

// Single-layer adjacency using raw byte blocks.
// Block layout per node (int = 4 bytes typically):
// [ degree:int ][ neighbor0:int ][ neighbor1:int ] ... [ neighbor(M-1):int ]
class SingleLayerAdj {
public:
    explicit SingleLayerAdj(int M);

    // add a new node; returns its id
    int add_node();

    // add directed edge u -> v (no duplicates check for now; capacity-limited by M)
    void add_neighbor(int u, int v);

    // number of nodes
    int size() const { return (int)num_nodes_; }

    // capacity per node
    int M() const { return M_; }

    // current degree (out-degree) of node u
    int degree(int u) const;

    // pointer to the neighbor array of node u (length = degree(u), capacity = M)
    // usage: int* nbrs = neighbors(u); for (int i=0;i<degree(u);++i) use nbrs[i];
    int* neighbors(int u);
    const int* neighbors(int u) const;

private:
    int M_;                    // max neighbors per node
    size_t block_size_bytes_;  // (1 + M_) * sizeof(int)
    size_t num_nodes_ = 0;     // how many nodes currently

    std::vector<char> storage_; // raw contiguous memory: num_nodes_ * block_size_bytes_

    // internal helpers
    char* block_ptr(int u) { return storage_.data() + u * block_size_bytes_; }
    const char* block_ptr(int u) const { return storage_.data() + u * block_size_bytes_; }
};

#endif // ADJACENCY_H
