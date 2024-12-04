#pragma once
#include <d3d12.h>

enum class PipelineType;
class GraphicsPipelineManager;
class TextureManager;
class ModelDataManager;
class DrawManager;

class DrawerBase {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	static void StaticInitialize();
	/// <summary>
	/// コマンドリストの取得
	/// </summary>
	static void BeginFrame();
protected:
	static ID3D12GraphicsCommandList* commandList_; // コマンドリスト
	static GraphicsPipelineManager* psoManager_; // グラフィックスパイプラインマネージャー
	static TextureManager* textureManager_; // テクスチャマネージャー
	static ModelDataManager* modelDataManager_; // モデルデータマネージャー
	static DrawManager* drawManager_; // 描画マネージャー
};