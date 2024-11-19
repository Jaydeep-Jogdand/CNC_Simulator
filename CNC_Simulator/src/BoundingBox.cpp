#include "BoundingBox.h"

BoundingBox::BoundingBox()
    :xMin(DBL_MAX), yMin(DBL_MAX), zMin(DBL_MAX), xMax(DBL_MIN), yMax(DBL_MIN), zMax(DBL_MIN)
{
}

BoundingBox::~BoundingBox()
{
}

void BoundingBox::findMinMax(Triangulation& triangulation)
{
    for (Triangle triangle : triangulation.Triangles)
    {
        xMin = std::min(xMin, triangulation.uniqueNumbers[triangle.P1().X()]);
        yMin = std::min(yMin, triangulation.uniqueNumbers[triangle.P1().Y()]);
        zMin = std::min(zMin, triangulation.uniqueNumbers[triangle.P1().Z()]);

        xMax = std::max(xMax, triangulation.uniqueNumbers[triangle.P1().X()]);
        yMax = std::max(yMax, triangulation.uniqueNumbers[triangle.P1().Y()]);
        zMax = std::max(zMax, triangulation.uniqueNumbers[triangle.P1().Z()]);

        xMin = std::min(xMin, triangulation.uniqueNumbers[triangle.P2().X()]);
        yMin = std::min(yMin, triangulation.uniqueNumbers[triangle.P2().Y()]);
        zMin = std::min(zMin, triangulation.uniqueNumbers[triangle.P2().Z()]);

        xMax = std::max(xMax, triangulation.uniqueNumbers[triangle.P2().X()]);
        yMax = std::max(yMax, triangulation.uniqueNumbers[triangle.P2().Y()]);
        zMax = std::max(zMax, triangulation.uniqueNumbers[triangle.P2().Z()]);

        xMin = std::min(xMin, triangulation.uniqueNumbers[triangle.P3().X()]);
        yMin = std::min(yMin, triangulation.uniqueNumbers[triangle.P3().Y()]);
        zMin = std::min(zMin, triangulation.uniqueNumbers[triangle.P3().Z()]);

        xMax = std::max(xMax, triangulation.uniqueNumbers[triangle.P3().X()]);
        yMax = std::max(yMax, triangulation.uniqueNumbers[triangle.P3().Y()]);
        zMax = std::max(zMax, triangulation.uniqueNumbers[triangle.P3().Z()]);
    }
}


std::vector<SurfacePoint> BoundingBox::generateTriangles()
{
    std::vector<SurfacePoint> boundingBox;
    SurfacePoint v0(xMin, yMin, zMin);
    boundingBox.push_back(v0);
    SurfacePoint v1(xMin, yMin, zMax);
    boundingBox.push_back(v1);
    SurfacePoint v2(xMin, yMax, zMin);
    boundingBox.push_back(v2);
    SurfacePoint v3(xMin, yMax, zMax);
    boundingBox.push_back(v3);
    SurfacePoint v4(xMax, yMin, zMin);
    boundingBox.push_back(v4);
    SurfacePoint v5(xMax, yMin, zMax);
    boundingBox.push_back(v5);
    SurfacePoint v6(xMax, yMax, zMin);
    boundingBox.push_back(v6);
    SurfacePoint v7(xMax, yMax, zMax);
    boundingBox.push_back(v7);

    return boundingBox;
}
