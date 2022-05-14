#pragma once

#include <cmath>
#include <iostream>

class vec4
{
public:
	vec4() : e{0.0f, 0.0f, 0.0f, 0.0f} { }
	vec4(float e0, float e1, float e2, float e3) : e {e0, e1, e2, e3} { }

	float x() const { return e[0]; }
	float y() const { return e[1]; }
	float z() const { return e[2]; }
	float w() const { return e[3]; }

	float r() const { return e[0]; }
	float g() const { return e[1]; }
	float b() const { return e[2]; }
	float a() const { return e[3]; }

	vec4 operator-() const { return vec4(-e[0], -e[1], -e[2], -e[3]); }
	float operator[](int i) const { return e[i]; }
	float& operator[](int i) { return e[i]; }

	vec4& operator+=(const vec4& v)
	{
		e[0] += v.e[0];
		e[1] += v.e[1];
		e[2] += v.e[2];
		e[3] += v.e[3];
		return *this;
	}

	vec4& operator*=(const float t)
	{
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
		e[3] *= t;
		return *this;
	}

	vec4& operator/=(const float t)
	{
		return *this *= 1 / t;
	}

public:
	float e[4];
};

using point4 = vec4;
using colorRGBA = vec4;

inline std::ostream& operator<<(std::ostream& out, const vec4& v)
{
	return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2] << ' ' << v.e[3];
}

inline vec4 operator+(const vec4& u, const vec4& v)
{
	return vec4(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2], u.e[3] + v.e[3]);
}

inline vec4 operator-(const vec4& u, const vec4& v)
{
	return vec4(u.e[0] - u.e[0], u.e[1] - u.e[1], u.e[2] - u.e[2], u.e[3] - u.e[3]);
}

inline vec4 operator*(const vec4& u, const vec4& v)
{
	return vec4(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2], u.e[3] * v.e[3]);
}

inline vec4 operator*(float t, const vec4& v)
{
	return vec4(t * v.e[0], t * v.e[1], t * v.e[2], t * v.e[3]);
}

inline vec4 operator*(const vec4& v, float t)
{
	return t * v;
}

inline vec4 operator/(vec4& v, float t)
{
	return (1 / t) * v;
}