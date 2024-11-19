#include "Triangulation.h"
using namespace Geometry;
using namespace std;

class Intersector
{
private:
	//This returns the boundary point where the intersection takes place
	SurfacePoint* isIntersecting(const Point& p1, const Point& p2, double yAxis, const vector<double>& uniqueValues);
public:
	Intersector();
	~Intersector();
	
	vector<SurfacePoint> intersectTriangleWithPlane(const Triangle& triangle, double yAxis, const Triangulation& triangulation);

};
