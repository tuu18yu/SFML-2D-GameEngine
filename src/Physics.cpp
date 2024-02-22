
#include "Physics.h"
#include <iostream>

bool detectCollision(Vec2 c1, Vec2 c2, float r1, float r2, Vec2& overlap)
{
	float distance = (c1 - c2).getLength();
	float radiusOverlap = (r1 + r2) - distance;
	overlap.x = (r1 + r2) - abs(c1.x - c2.x);
	overlap.y = (r1 + r2) - abs(c1.y - c2.y);
	if (radiusOverlap >= 0) { return true; }
	return false;
}

bool detectCollision(Vec2 c1, Vec2 c2, Vec2 s1, Vec2 s2, Vec2& overlap)
{
	// the origin of the object is the center
	overlap.x = (s1.x / 2 + s2.x / 2) - abs(c1.x - c2.x);
	overlap.y = (s1.y / 2 + s2.y / 2) - abs(c1.y - c2.y);

	if ((overlap.x >= 0) && (overlap.y >= 0)) { return true; }
	return false;
}

bool detectCollision(Vec2 c1, Vec2 c2, Vec2 size, float radius, Vec2& overlap)
{
	overlap.x = (size.x / 2 + radius) - abs(c1.x - c2.x);
	overlap.y = (size.y / 2 + radius) - abs(c1.y - c2.y);

	if ((overlap.x >= 0) && (overlap.y >= 0)) { return true; }
	return false;
}

void getSeparatingAxes(int nVertices, std::vector<Vec2> vertices, std::vector<Vec2>& axes)
{
	for (int i = 0; i < nVertices; i++)
	{
		Vec2 p1 = vertices[i];
		Vec2 p2 = vertices[i + 1 == nVertices ? 0 : i + 1];

		Vec2 edge = p1 - p2;
		// in 2D, getting the perpendicular vector is (y, x) or (-y, x) 
		Vec2 normal(-edge.y, edge.x);
		
		// it's not necessary to normalize unless looking for the exact location of the projection
		// normal.normalize();
		
		axes.push_back(normal);
	}
}

Vec2 projection(int nVertices, std::vector<Vec2> vertices, Vec2 axis)
{
	float min = axis.dot_product(vertices[0]);
	float max = min;

	for (int i = 1; i < nVertices; i++)
	{
		float p = axis.dot_product(vertices[i]);
		if (p < min) { min = p; }
		else if (p > max) { max = p; }

	}

	return Vec2(min, max);
}

bool detectCollision(int nVertices1, int nVertices2, std::vector<Vec2> vertices1, std::vector<Vec2> vertices2, Vec2& overlap)
{
	std::vector<Vec2> axes1, axes2;
	Vec2 p1, p2;
	// get all possible seperating axes
	getSeparatingAxes(nVertices1, vertices1, axes1);
	getSeparatingAxes(nVertices2, vertices2, axes2);

	// loop through all the axes in axes1
	for (int i = 0; i < nVertices1; i++)
	{
		// project each polygon to the axis and get its min and max
		p1 = projection(nVertices1, vertices1, axes1[i]);
		p2 = projection(nVertices2, vertices2, axes1[i]);

		// x is the minimum, and y is the maximum
		// if there exists an axis there two polygons do not overlap then they did not collide
		if ((p1.y < p2.x) || (p2.y < p1.x)) { return false; }

	}

	// loop through all the axes in axes2
	for (int i = 0; i < nVertices2; i++)
	{
		p1 = projection(nVertices1, vertices1, axes2[i]);
		p2 = projection(nVertices2, vertices2, axes2[i]);

		if ((p1.y < p2.x) || (p2.y < p1.x)) { return false; }
	}

	// if there is no separating axis then there is collision between two polygons
	// find the overlap in x-axis and y-axis and store in the overlap vector

	// Note: axis must be unit vector as dot product as |A||B|cos(theta) where |A|cos(theta) is the projection of A onto B
	// So if |B| = 1 then we can get |A|cos(theta) which is the location of the projection
	p1 = projection(nVertices1, vertices1, Vec2(1.f, 0.f));
	p2 = projection(nVertices2, vertices2, Vec2(1.f, 0.f));
	overlap.x = p1.x <= p2.x ? p1.y - p2.x : p2.y - p1.x;

	p1 = projection(nVertices1, vertices1, Vec2(0.f, 1.f));
	p2 = projection(nVertices2, vertices2, Vec2(0.f, 1.f));
	overlap.y = p1.x <= p2.x ? p1.y - p2.x : p2.y - p1.x;

	return true;
}