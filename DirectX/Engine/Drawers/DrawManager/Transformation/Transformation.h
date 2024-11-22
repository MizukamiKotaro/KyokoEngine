#pragma once
#include "Matrix4x4.h"
#include <wrl.h>
#include <d3d12.h>

/// <summary>
/// 変換行列データ
/// GPUに送るデータ
/// </summary>
class Transformation
{
public:
	Transformation();
	~Transformation();
	/// <summary>
	/// 変換行列
	/// </summary>
	struct TransformationMatrix {
		Matrix4x4 WVP; // wvp行列
		Matrix4x4 World; // ワールド行列
		Matrix4x4 WorldInverse; // ワールド逆行列
	};
	Microsoft::WRL::ComPtr<ID3D12Resource> transformationResource; // リソース
	TransformationMatrix* transformationData; // データ
};