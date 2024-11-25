#include "Sphere.h"

void Sphere::Initialize(const Vector3& center, float radius) {
	center_ = center;
	scale_ = { 1.0f,1.0f,1.0f };
	rotate_ = {};
	radius_ = radius;
}

void Sphere::Initialize(const Vector3& center, const Vector3& rotate, float radius) {
	center_ = center;
	scale_ = { 1.0f,1.0f,1.0f };
	rotate_ = rotate;
	radius_ = radius;
}

void Sphere::Initialize(const Vector3& center, const Vector3& scale, const Vector3& rotate, float radius) {
	center_ = center;
	scale_ = scale;
	rotate_ = rotate;
	radius_ = radius;
}