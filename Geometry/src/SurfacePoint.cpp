#include "SurfacePoint.h"
#include <cmath>
#define TOLERANCE 1e-12
using namespace Geometry;

SurfacePoint::SurfacePoint()
	:x(0.0),
	y(0.0),
	z(0.0)
{
}
 
SurfacePoint::SurfacePoint(double _x, double _y, double _z)
	:x(_x),
	y(_y),
	z(_z)
{
}

SurfacePoint::~SurfacePoint()
{
}
double SurfacePoint::X()
{
	return x;
}
 
double SurfacePoint::Y()
{
	return y;
}
 
double SurfacePoint::Z()
{
	return z;
}

bool Geometry::SurfacePoint::operator()(const SurfacePoint& other) const
{
	if (x > other.x) return true;
	if (x < other.x) return false;
	return z > other.z;
}
//bool Geometry::SurfacePoint::operator()(double a, double b) const {
//	// If the difference is greater than the tolerance, return the result of comparison
//	return fabs(a - b) > TOLERANCE ? a < b : false;
//}
//bool SurfacePoint::operator==(const SurfacePoint& other) const
//{
//	return x == other.x && y == other.y && z == other.z;
//}
//bool Geometry::SurfacePoint::operator()(const SurfacePoint& other) const {
//	// Compare the x, y, and z components with tolerance
//	return (fabs(x - other.x) < TOLERANCE) &&
//		(fabs(y - other.y) < TOLERANCE) &&
//		(fabs(z - other.z) < TOLERANCE);
//}
bool SurfacePoint::operator==(const SurfacePoint& other) const {
	constexpr double EPSILON = 1e-6; // Tolerance for floating-point comparison
	return (std::abs(x - other.x) < TOLERANCE) &&
		(std::abs(y - other.y) < TOLERANCE) &&
		(std::abs(z - other.z) < TOLERANCE);
}

bool SurfacePoint::operator!=(const SurfacePoint& other) const
{
	return !(*this == other);
}

std::ostream& Geometry::operator<<(std::ostream& os, const SurfacePoint& sp)
{
	os << sp.x << " " << sp.y << " " << sp.z << std::endl;
	return os;
}