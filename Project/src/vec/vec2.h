#pragma once

#include <cmath>
#include <iostream>

class vec2
{
public:
	vec2() : e{ 0.0f, 0.0f } { }
	vec2(float e0, float e1) : e{ e0, e1 } { }

	float x() const { return e[0]; }
	float y() const { return e[1]; }

	vec2 operator-() const { return vec2(-e[0], -e[1]); }
	float operator[](int i) const { return e[i]; }
	float& operator[](int i) { return e[i]; }

	vec2& operator+=(const vec2& v)
	{
		e[0] += v.e[0];
		e[1] += v.e[1];
		return *this;
	}

	vec2& operator*=(const float t)
	{
		e[0] *= t;
		e[1] *= t;
		return *this;
	}

	vec2& operator/=(const float t)
	{
		return *this *= 1 / t;
	}

	float Length() const
	{
		return sqrt(LengthSquared());
	}

	float LengthSquared() const
	{
		return e[0] * e[0] + e[1] * e[1];
	}

public:
	float e[2];
};

using point2 = vec2;

inline std::ostream& operator<<(std::ostream& out, const vec2& v)
{
	return out << v.e[0] << ' ' << v.e[1];
}

inline vec2 operator+(const vec2& u, const vec2& v)
{
	return vec2(u.e[0] + v.e[0], u.e[1] + v.e[1]);
}

inline vec2 operator-(const vec2& u, const vec2& v)
{
	return vec2(u.e[0] - u.e[0], u.e[1] - u.e[1]);
}

inline vec2 operator*(const vec2& u, const vec2& v)
{
	return vec2(u.e[0] * v.e[0], u.e[1] * v.e[1]);
}

inline vec2 operator*(float t, const vec2& v)
{
	return vec2(t * v.e[0], t * v.e[1]);
}

inline vec2 operator*(const vec2& v, float t)
{
	return t * v;
}

inline vec2 operator/(vec2& v, float t)
{
	return (1 / t) * v;
}