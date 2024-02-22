#pragma once

#include "Vec2.h"
#include <vector>


// circle and circle collision
bool detectCollision(Vec2 center1, Vec2 center2, float radius1, float radius2, Vec2& overlap);
// AABB collision
bool detectCollision(Vec2 center1, Vec2 center2, Vec2 size1, Vec2 size2, Vec2& overlap);
// circle and recatangle collision
bool detectCollision(Vec2 center1, Vec2 center2, Vec2 size, float radius, Vec2& overlap);

// polygon and polygon collision or oriented bounding box
bool detectCollision(int nVertices1, int nVertices2, std::vector<Vec2> vertices1, std::vector<Vec2> vertices2, Vec2& overlap);

void getSeparatingAxes(int nVertices, std::vector<Vec2> vertices, std::vector<Vec2>& axes);
Vec2 projection(int nVertices, std::vector<Vec2> vertices, Vec2 axis);