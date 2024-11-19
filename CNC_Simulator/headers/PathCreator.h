#pragma once
#include<vector>
#include"SurfacePoint.h"
#include "Triangulation.h"
using namespace Geometry;
class PathCreator
{
private:
	std::vector<Triangle> sortTriangles( std::vector<Triangle>&); //sort triangles according to the edges
	//sort boundaryPoints according to the plane
	std::vector<SurfacePoint> sortPoints(std::vector<Triangle>& sortedPoints, Triangulation& triangulation, double yAxis);
public:
	PathCreator();
	~PathCreator();
	//path of the boundary Points which starts from ymax to ymin
	std::vector<std::vector<SurfacePoint>> createPath(Triangulation& triangulation, double yMax, double yMin);
	
};

