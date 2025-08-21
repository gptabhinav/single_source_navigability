#include "distance.h"
#include <vector>
using namespace std;

float l2_sq(const vector<float>& a, const vector<float>& b, int d) {
    float distance = 0.f;
    for (int i = 0; i < d; ++i) {
        float diff = a[i] - b[i];
        distance += diff * diff;
    }
    return distance;
}