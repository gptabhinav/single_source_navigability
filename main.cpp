#include <iostream>
#include "graph.h"
#include "distance.h"

int main() {
    int dim = 3, M = 4;
    Graph G(dim, M);

    int a = G.add_point({1.0f, 2.0f, 3.0f});
    int b = G.add_point({2.0f, 4.0f, 5.0f});
    int c = G.add_point({0.5f, 0.0f, 1.0f});

    G.add_edge(a, b);
    G.add_edge(a, c);

    std::cout << "deg(a)=" << G.degree(a) << "\n";
    auto nb = G.neighbors(a);
    for (int i = 0; i < G.degree(a); ++i) std::cout << nb[i] << " ";
    std::cout << "\n";

    std::cout << "L2^2(a,b)=" << l2_sq(G.vec(a), G.vec(b), dim) << "\n";
    return 0;
}
