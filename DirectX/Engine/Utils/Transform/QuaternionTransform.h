#pragma once
#include "Utils/Math/Vector3.h"
#include "Utils/Math/Matrix4x4.h"
#include "Quaternion.h"

class QuaternionTransform {
public:
	QuaternionTransform();

public:
	Vector3 scale_;
	Quaternion rotate_;
	Vector3 translate_;
};