#pragma once
#include "SurfacePoint.h"
#include "Triangulation.h"
#include<vector>
using namespace Geometry;
class BoundingBox {
public:
    double xMin;
    double xMax;
    double yMin;
    double yMax;
    double zMin;
    double zMax;
    


    BoundingBox();
    ~BoundingBox();

    void findMinMax(Triangulation& triangulation);


    std::vector<SurfacePoint> generateTriangles();


};