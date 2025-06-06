#pragma once
#ifdef _DEBUG
#include "Vector3.h"
#include "Matrix4x4.h"

namespace ImGuiCommon {
	enum class Type
	{
		TRANSLATE,
		SCALE
	};

	Vector3 ShowTransformGizmo(const ImGuiCommon::Type& type, const Matrix4x4& viewMatrix, const Matrix4x4& projectionMatrix, Matrix4x4& objectMatrix);
}
#endif // _DEBUG