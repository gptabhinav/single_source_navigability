#include <iostream>
#include "distance.h"
using namespace std;

vector<float> d1 = {1.0, 2.0, 3.0};
vector<float> d2 = {4.0, 5.0, 6.0};

int main() {
    int dimension = 3;
    float distance = l2_sq(d1, d2, dimension);
    cout << "L2 squared distance: " << distance << endl;
    return 0;
}

