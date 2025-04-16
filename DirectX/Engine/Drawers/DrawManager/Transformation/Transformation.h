#pragma once
#include "Matrix4x4.h"
#include <wrl.h>
#include <d3d12.h>
#include "Resource/Resource.h"

/// <summary>
/// 変換行列データ
/// GPUに送るデータ
/// </summary>
class Transformation
{
public:
	Transformation();
	/// <summary>
	/// 変換行列
	/// </summary>
	struct TransformationMatrix {
		Matrix4x4 WVP; // wvp行列
		Matrix4x4 World; // ワールド行列
		Matrix4x4 WorldInverse; // ワールド逆行列
	};
	Kyoko::ResourceManualRelease transformationResource; // リソース
	TransformationMatrix* transformationData; // データ
};