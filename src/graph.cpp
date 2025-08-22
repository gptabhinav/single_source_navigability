#include "graph.h"
#include <cassert>

int Graph::add_point(const std::vector<float>& vec) {
    assert((int)vec.size() == dim_ && "vector dimension must match graph dim");
    int id = (int)data_.size();
    data_.push_back(vec);
    adj_.add_node(); // allocate adjacency block for this node
    return id;
}
