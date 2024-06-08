#include "wall.h"
#include "color.h"

Wall::Wall(){
    std::vector<float> triangle1Pos = {};
    std::vector<float> triangle2Pos = {};

    TriangleMesh *triangle1 = new TriangleMesh(triangle1Pos, BLACK);
}