#pragma once
#include <utility>
#include <array>

using namespace std;

class Shapes
{
public:
    pair<array<float, 36>, array<unsigned int, 6>> getSampleRectangleData();
    array<float, 180> getSampleCubeVerts();
};