#include <vector>
#include "Triangle.h"
using namespace Geometry;
Triangle::Triangle(Point normal, Point p1, Point p2, Point p3)
    : p1(p1), p2(p2), p3(p3), normal(normal),
    e1(p1, p2), e2(p2, p3), e3(p3, p1)
{
}

Triangle::~Triangle()
{

}

Point Triangle::P1() const
{
    return p1;
}

Point Triangle::P2() const
{
    return p2;
}

Point Triangle::P3() const
{
    return p3;
}

Point Triangle::Normal() const
{
    return normal;
}

vector<Edge> Triangle::getEdges()
{
    return edges;
}

std::vector<Point> Triangle::Points()
{
    std::vector<Point> points;
    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);
    return points;
}

bool Geometry::Triangle::areAdjacent(Triangle& other)
{
    vector<Edge> edges1 = this->getEdges();
    vector<Edge> edges2 = other.getEdges();

    for (Edge e1 : edges1)
    {
        for (Edge e2 : edges2)
        {
            if (e1 == e2) {
                return true;
            }
        }
    }
    return false;
}

