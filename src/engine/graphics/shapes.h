#pragma once
#include <array>
#include <utility>
#include <vector>

using namespace std;

class Shapes {
public:
    pair<vector<float>,vector<unsigned int>> getSampleRectangleData();
    array<float, 180> getSampleCubeVerts();
};