#pragma once
#include <d3d12.h>
#include <stdint.h>
class GraphicsPipelineManager;

/// <summary>
/// 描画マネージャーの基底クラス
/// </summary>
class DrawManagerBase {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	static void StaticInitialize();
	/// <summary>
	/// 描画数のリセット
	/// </summary>
	void Reset();
protected:
	static ID3D12GraphicsCommandList* commandList_; // コマンドリスト
	static GraphicsPipelineManager* psoManager_; // コマンドリスト
	int32_t drawNo_; // 描画数
};