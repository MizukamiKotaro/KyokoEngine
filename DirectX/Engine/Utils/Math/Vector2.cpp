#include "Vector2.h"
#include <cmath>


Vector2& Vector2::operator=(const Vector2& other) noexcept
{
	this->x = other.x;
	this->y = other.y;
	return *this;
}

Vector2& Vector2::operator+=(const Vector2& other) noexcept
{
	this->x += other.x;
	this->y += other.y;
	return *this;
}

Vector2& Vector2::operator-=(const Vector2& other) noexcept
{
	this->x -= other.x;
	this->y -= other.y;
	return *this;
}

Vector2& Vector2::operator*=(float scalar) noexcept
{
	this->x *= scalar;
	this->y *= scalar;
	return *this;
}

Vector2& Vector2::operator/=(float scalar)
{
	this->x /= scalar;
	this->y /= scalar;
	return *this;
}

bool Vector2::operator==(const Vector2& other) const noexcept
{
	return this->x == other.x && this->y == other.y;
}

bool Vector2::operator!=(const Vector2& other) const noexcept
{
	return !(*this == other);
}


Vector2 operator+(const Vector2& v1, const Vector2& v2) {
	Vector2 tmp = {};
	tmp.x = v1.x + v2.x;
	tmp.y = v1.y + v2.y;
	return tmp;
}

Vector2 operator-(const Vector2& v1, const Vector2& v2) {
	Vector2 tmp = {};
	tmp.x = v1.x - v2.x;
	tmp.y = v1.y - v2.y;
	return tmp;
}

Vector2 operator*(const Vector2& v, float scalar) {
	Vector2 tmp = {};
	tmp.x = v.x * scalar;
	tmp.y = v.y * scalar;
	return tmp;
}

Vector2 operator*(float scalar, const Vector2& v) {
	return v * scalar;
}


Vector2 operator/(const Vector2& v, float scalar) {
	Vector2 tmp = {};

	tmp.x = v.x / scalar;
	tmp.y = v.y / scalar;
	return tmp;
}

float Vector2::Length() const
{
	float result = static_cast<float>(sqrt(powf(this->x, 2) + powf(this->y, 2)));
	return result;
}

Vector2 Vector2::Normalize() const
{
	float length = Length();
	Vector2 result = {};

	if (length != 0) {
		result = { this->x / length, this->y / length };
	}
	return result;
}
