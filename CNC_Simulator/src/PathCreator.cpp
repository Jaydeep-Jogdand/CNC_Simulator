#include "PathCreator.h"
#include "Intersector.h"
#include <unordered_map>
#include<stdexcept>
#include <iostream>
using namespace std;
PathCreator::PathCreator()
{
}

PathCreator::~PathCreator()
{
}

std::vector<std::vector<SurfacePoint>> PathCreator::createPath(Triangulation& triangulation, double y_max, double y_min)
{
	vector<vector<SurfacePoint>> path;
	double y = y_max;
	Intersector in;

	for (; y >= y_min; y = y - 0.1)
	{
		vector<Triangle> yIntersecingTrs;//consider triangles for one plane
		for (auto t : triangulation.Triangles)
		{
			bool intersect = false;

			Point p1 = t.P1();
			Point p2 = t.P2();
			Point p3 = t.P3();

			//taking real points from triangulation getRealPoints function
			SurfacePoint sp1 = triangulation.getRealPoint(p1);
			SurfacePoint sp2 = triangulation.getRealPoint(p2);
			SurfacePoint sp3 = triangulation.getRealPoint(p3);

			//checking y-axis of realPoints with y-axis of plane
			if ((sp1.Y() <= y && sp2.Y() > y) ||  
				(sp1.Y() > y && sp2.Y() <= y) ||
				(sp1.Y() <= y && sp3.Y() > y) ||
				(sp1.Y() > y && sp3.Y() <= y) ||
				(sp2.Y() <= y && sp3.Y() > y) ||
				(sp2.Y() > y && sp3.Y() <= y))
			{
				intersect = true;
			}
			if (intersect)
			{
				yIntersecingTrs.push_back(t);
			}
		}
		vector<Triangle> sortedTriangles = sortTriangles(yIntersecingTrs);
		vector<SurfacePoint> sortedPoints = sortPoints(sortedTriangles, triangulation, y);
		path.push_back(sortedPoints);
	}
	return path;
}

vector<Triangle> PathCreator::sortTriangles(vector<Triangle>& coplanarTriangles)
{
	if (coplanarTriangles.empty()) {
		return {};
	}

	vector<Triangle> sortedTriangles;
	sortedTriangles.push_back(coplanarTriangles.front());
	coplanarTriangles.erase(coplanarTriangles.begin());

	//traversing vector of triangles lies on same y-axis
	while (!coplanarTriangles.empty()) {
		bool foundNext = false;

		for (auto it = coplanarTriangles.begin(); it != coplanarTriangles.end(); ++it) {
			if (sortedTriangles.back().areAdjacent(*it)) { //if they have a similar edge then push that triangle into sortedtriangle
				sortedTriangles.push_back(*it);
				coplanarTriangles.erase(it);//after adding we erase that triangle to eleminate repetition
				foundNext = true;
				break;
			}
		}

		if (!foundNext) {
			throw runtime_error("Triangles do not form a closed loop!");
		}
	}

	if (!sortedTriangles.front().areAdjacent(sortedTriangles.back())) {
		throw runtime_error("The sorted triangles do not form a closed loop!");
	}

	return sortedTriangles;
}

vector<SurfacePoint> PathCreator::sortPoints(vector<Triangle>& sortedTriangles, Triangulation& triangulation, double yAxis)
{
	vector<vector<SurfacePoint>> intersectionPoints;//takes vector of boundary points for each plane
	vector<SurfacePoint> sortedPoints; // sortedPoints is for storing boundaryPoints
	unordered_map<SurfacePoint, int, SurfacePoint> map; //map for eleminate duplication

	Intersector intersector;
	for (auto t : sortedTriangles)
	{
		intersectionPoints.push_back(intersector.intersectTriangleWithPlane(t, yAxis, triangulation));
	}

	for (auto intersection : intersectionPoints)
	{
		for (int i = 0; i < intersection.size(); i++)
		{
			auto pair = map.find(intersection[i]);
			if (pair == map.end())
			{
				sortedPoints.push_back(intersection[i]);
				map[intersection[i]] = sortedPoints.size() - 1;
			}
		}
	}
	return sortedPoints;
}