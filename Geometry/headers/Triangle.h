#pragma once
#include <vector>
#include "Point.h"
#include "Edge.h"
using namespace std;
namespace Geometry
{
    class Triangle
    {
        // Three points representing the vertices of the triangle
    private:
        Point p1;
        Point p2;
        Point p3;
        Point normal;
        Edge e1;
        Edge e2;
        Edge e3;
        std::vector<Edge> edges = { e1,e2,e3 };

    public:
        Triangle(Point normal, Point p1, Point p2, Point p3);
        ~Triangle();

        // Getter functions to access the private members 
        Point P1() const;
        Point P2() const;
        Point P3() const;
        Point Normal() const;

        std::vector<Edge> getEdges();

        vector<Point> Points();
        bool areAdjacent(Triangle&);
    };
}
