#pragma once
#include <list>
#include <wrl.h>
#include <d3d12.h>

/// <summary>
/// リソースのマネージャー
/// </summary>
class ResourceManager {
public:
	/// <summary>
	/// インスタンスの取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static ResourceManager* GetInstance();
	/// <summary>
	/// フレームの最初の処理、リソースの削除
	/// </summary>
	void BeginFrame();
	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();
	/// <summary>
	/// リソースの追加
	/// </summary>
	/// <param name="resource">リソース</param>
	void AddResource(Microsoft::WRL::ComPtr<ID3D12Resource>&& resource);

private:
	ResourceManager() = default;
	~ResourceManager() = default;
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;

private:
	std::list<Microsoft::WRL::ComPtr<ID3D12Resource>> list_; // リスト
};