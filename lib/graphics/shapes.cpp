#include "shapes.h"

using namespace std;

pair<array<float, 12>, array<unsigned int, 6>> Shapes::getSampleRectangleData()
{
    array<float, 12> vertices = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
    array<unsigned int, 6> indices = {
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };
    return make_pair(vertices, indices);
}