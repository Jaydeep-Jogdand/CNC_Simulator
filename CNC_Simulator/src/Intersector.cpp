#include "Intersector.h"

Intersector::Intersector()
{
}

Intersector::~Intersector()
{
}

SurfacePoint* Intersector::isIntersecting(const Point& p1, const Point& p2, double yAxis, const vector<double>& uniqueValues)
{
    // check if the edge intersects the y-axis of the plane
    if ((uniqueValues[p1.Y()] - yAxis) * (uniqueValues[p2.Y()] - yAxis) <= 0) {
        double ty = (yAxis - uniqueValues[p1.Y()]) / (uniqueValues[p2.Y()] - uniqueValues[p1.Y()]);//calculate interplolation factor ty
        double x_ = uniqueValues[p1.X()] + ty * (uniqueValues[p2.X()] - uniqueValues[p1.X()]);
        double z_ = uniqueValues[p1.Z()] + ty * (uniqueValues[p2.Z()] - uniqueValues[p1.Z()]);
        return new SurfacePoint(x_, yAxis, z_);
    }
    return nullptr;//if no intersection is there then return nullptr
}

vector<SurfacePoint> Intersector::intersectTriangleWithPlane(const Triangle& t, double yAxis, const Triangulation& tri)
{
    vector<SurfacePoint> intersectingPts;

    Point p1 = t.P1();
    Point p2 = t.P2();
    Point p3 = t.P3();
    // Check for intersection between each edge and the plane along the yAxis
    SurfacePoint* ptOnEdge1 = isIntersecting(p1, p2, yAxis, tri.uniqueNumbers);
    SurfacePoint* ptOnEdge2 = isIntersecting(p3, p2, yAxis, tri.uniqueNumbers);
    SurfacePoint* ptOnEdge3 = isIntersecting(p1, p3, yAxis, tri.uniqueNumbers);
    
    // Lambda function to add a unique intersection point to the result vector
    auto addUniquePoint = [&intersectingPts](SurfacePoint* pt) 
       
        {
            if (pt) 
            {
                // Check if the point is already in the list to avoid duplicates
                if (find(intersectingPts.begin(), intersectingPts.end(), *pt) == intersectingPts.end()) 
                {
                    intersectingPts.push_back(*pt);
                }
            }
        };

    // Add the intersection points of each edge if they are valid and unique
    addUniquePoint(ptOnEdge1);
    addUniquePoint(ptOnEdge2);
    addUniquePoint(ptOnEdge3);

    return intersectingPts;
}