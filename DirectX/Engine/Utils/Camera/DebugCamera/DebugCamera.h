#pragma once
#include "Vector3.h"
#include "Vector2.h"
#include "Transform/Transform.h"

class Input;

class DebugCamera {
public:
	DebugCamera();

	void DebugUpdate(EulerTransform& transform);
	void Update(EulerTransform& transform);

	const bool& IsDebug() const { return isDebug_; }
	void StopDebug();

private:
	Input* input_;
	EulerTransform beforeDebugTransform_;
	bool isDebug_;
	bool isPreDebug_;
	bool is2D_;
	bool isMouseMove_;

	Vector3 subRotate_;
	Vector3 subTranslate_;
	Vector2 mousePos_;

	bool isTranslate_;
	bool isRotate_;
	bool isRotateTranslate_;
};