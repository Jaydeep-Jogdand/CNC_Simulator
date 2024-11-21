
#pragma once

#include "SurfacePoint.h"
#include "Triangulation.h"
#include <vector>
#include <algorithm> // For std::min and std::max
using namespace Geometry;

class BoundingBox {

private:
   
    // Bounding box limits
    double  xMin;
    double  yMin;
    double  zMin;
    double  xMax;
    double  yMax;
    double  zMax;

    // Helper function to update the bounding box bounds
    void updateBounds(double x, double y, double z);

public:
 
    BoundingBox();

    ~BoundingBox();

    // Calculates the minimum and maximum bounds for the given triangulation
    void findMinMax(const Triangulation& triangulation);
    // Generates the vertices of the bounding box
    std::vector<SurfacePoint> generateVertices() const;

};