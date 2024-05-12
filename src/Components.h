#pragma once
#include "Animation.h"
#include "Assets.h"
#include "Vec2.h"

class Component
{
public:
	bool has = false;
};


class CTransform : public Component
{
public:
	Vec2 pos		= { 0.0, 0.0 };
	Vec2 prevPos	= { 0.0, 0.0 };
	Vec2 scale		= { 1.0, 1.0 };
	Vec2 velocity	= { 0.0, 0.0 };
	float angle		= 0;
	
	CTransform() {}
	CTransform(const Vec2 & p)
		: pos(p) {}
	CTransform(const Vec2 & p, const Vec2 & sp, const Vec2 & sc, float a)
		: pos(p), prevPos(p), velocity(sp), scale(sc), angle(a) {}
};

class CLifeSpan : public Component
{
public:
	int lifespan		= 0;
	int frameCreated	= 0;
	CLifeSpan() {}
	CLifeSpan(int duration, int frame)
		: lifespan(duration), frameCreated(frame) {}
};

class CInput : public Component
{
public:
	bool up			= false;
	bool down		= false;
	bool left		= false;
	bool right		= false;
	bool shoot		= false;
	bool jump		= false;

	CInput(){}
};

class CAnimation : public Component
{
public:
	Animation animation;
	bool repeat = false;
	CAnimation() {}
	CAnimation(const Animation & animation, bool r)
		: animation(animation), repeat(r) {}
};

class CBoundingBox : public Component
{
public:
	float radius = -1.f;
	Vec2 size;
	Vec2 halfSize;
	CBoundingBox() {}
	CBoundingBox(const Vec2& s)
		: size(s), halfSize(s.x / 2, s.y / 2) {}
};

class CForce : public Component
{
public:
	float gravity = 0.f;
	float friction = 0.f;
	float x = 0.f;
	float y = 0.f;
	CForce() {}
	CForce(float g, float f, float x, float y)
		: gravity(g), friction(f), x(x), y(y) {}
};

class CState : public Component
{
public:
	std::string state = "";
	CState() {}
	CState(const std::string & s)
		: state(s) {}
};

class CShape : public Component
{
public:
	sf::RectangleShape shape;
	sf::CircleShape circle;

	CShape() {}
	CShape(sf::RectangleShape s)
		: shape(s)
	{
	}
};