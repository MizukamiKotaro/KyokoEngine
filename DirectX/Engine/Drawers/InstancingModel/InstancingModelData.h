#pragma once
#include "Matrix4x4.h"
#include "Vector4.h"
#include "ModelData/ModelData.h"
#include "GraphicsPipelineSystem/BlendModeConfig.h"

/// <summary>
/// インスタンシング用個別のデータ
/// </summary>
class InstancingModelData {
public:
	Matrix4x4 matrix_; // 行列
	Matrix4x4 uvMatrix_; // uv行列
	Vector4 color_ = { 1.0f,1.0f,1.0f,1.0f }; // 色
};

/// <summary>
/// インスタンシング用のまとまったデータ
/// </summary>
class InstancingGroupData {
public:
	const std::string tag_; // タグ
	const ModelData* modelData_; // モデルデータ
	const Texture* texture_; // テクスチャ
	BlendMode blendMode_; // ブレンドモード
};