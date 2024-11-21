
#include "BoundingBox.h"
#include <limits> // For std::numeric_limits

BoundingBox::BoundingBox()
    : xMin(std::numeric_limits<double>::max()),
    yMin(std::numeric_limits<double>::max()),
    zMin(std::numeric_limits<double>::max()),
    xMax(std::numeric_limits<double>::lowest()),
    yMax(std::numeric_limits<double>::lowest()),
    zMax(std::numeric_limits<double>::lowest())
{
}

BoundingBox::~BoundingBox()
{
}
// Helper function to update the bounding box bounds
void BoundingBox::updateBounds(double x, double y, double z) 
{
    xMin = std::min(xMin, x);
    yMin = std::min(yMin, y);
    zMin = std::min(zMin, z);

    xMax = std::max(xMax, x);
    yMax = std::max(yMax, y);
    zMax = std::max(zMax, z);
}

// Calculates the minimum and maximum bounds for the given triangulation
void BoundingBox::findMinMax(const Triangulation& triangulation) {
    for (const Triangle& triangle : triangulation.Triangles) {
        updateBounds(triangulation.uniqueNumbers[triangle.P1().X()],
            triangulation.uniqueNumbers[triangle.P1().Y()],
            triangulation.uniqueNumbers[triangle.P1().Z()]);

        updateBounds(triangulation.uniqueNumbers[triangle.P2().X()],
            triangulation.uniqueNumbers[triangle.P2().Y()],
            triangulation.uniqueNumbers[triangle.P2().Z()]);

        updateBounds(triangulation.uniqueNumbers[triangle.P3().X()],
            triangulation.uniqueNumbers[triangle.P3().Y()],
            triangulation.uniqueNumbers[triangle.P3().Z()]);
    }
}

// Generates the vertices of the bounding box
std::vector<SurfacePoint> BoundingBox::generateVertices() const {
    std::vector<SurfacePoint> boundingBox;
    boundingBox.reserve(8); // Reserve space for 8 vertices

    boundingBox.emplace_back(xMin, yMin, zMin);
    boundingBox.emplace_back(xMin, yMin, zMax);
    boundingBox.emplace_back(xMin, yMax, zMin);
    boundingBox.emplace_back(xMin, yMax, zMax);
    boundingBox.emplace_back(xMax, yMin, zMin);
    boundingBox.emplace_back(xMax, yMin, zMax);
    boundingBox.emplace_back(xMax, yMax, zMin);
    boundingBox.emplace_back(xMax, yMax, zMax);

    return boundingBox;
}