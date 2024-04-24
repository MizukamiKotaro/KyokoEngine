#include "QuaternionTransform.h"

QuaternionTransform::QuaternionTransform()
{
	scale_ = { 1.0f,1.0f,1.0f };
	rotate_ = Quaternion::Identity();
	translate_ = { 0.0f,0.0f,0.0f };
}

