#pragma once
#include <d3d12.h>
#include <string>
#include <unordered_map>
#include <memory>
#include "Externals/DirectXTex/DirectXTex.h"

class Texture;
class DescriptorHeap;

// テクスチャマネージャ
class TextureManager {
public:
	/// <summary>
	/// インスタンスの取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static TextureManager* GetInstance();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// コマンドリストの取得
	/// </summary>
	void BeginFrame();

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();

	/// <summary>
	/// テクスチャのロード
	/// </summary>
	/// <param name="filePath">テクスチャファイル名</param>
	/// <returns>テクスチャ</returns>
	const Texture* LoadTexture(const std::string& filePath);

private:
	TextureManager() = default;
	~TextureManager() = default;
	TextureManager(const TextureManager&) = delete;
	TextureManager& operator=(const TextureManager&) = delete;

	/// <summary>
	/// テクスチャファイルの読み込み
	/// </summary>
	/// <param name="filePath">テクスチャファイルパス</param>
	/// <returns>ミップイメージ</returns>
	DirectX::ScratchImage Load(const std::string& filePath);

	/// <summary>
	/// テクスチャリソースの作成
	/// </summary>
	/// <param name="metadata">メタデータ</param>
	/// /// <returns>テクスチャリソース</returns>
	ID3D12Resource* CreateTextureResource(const DirectX::TexMetadata& metadata);

	/// <summary>
	/// テクスチャデータのアップロード
	/// </summary>
	/// <param name="texture">テクスチャ</param>
	/// <param name="mipImages">ミップイメージ</param>
	/// <returns>インターメディエイトリソース</returns>
	ID3D12Resource* UploadTextureData(ID3D12Resource* texture, const DirectX::ScratchImage& mipImages);

private:
	const std::string directoryPath_ = "Resources/Texture/";

	ID3D12Device* device_ = nullptr;
	ID3D12GraphicsCommandList* commandList_ = nullptr;
	DescriptorHeap* srvHeap_ = nullptr;

	std::unordered_map<std::string, std::unique_ptr<Texture>> textureMap_;
};