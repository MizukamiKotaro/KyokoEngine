#pragma once
#include <list>
#include <wrl.h>
#include <d3d12.h>

// 響子
namespace Kyoko {
	/// <summary>
	/// リソースの解放クラス
	/// </summary>
	class ResourceReleaser {
	public:
		/// <summary>
		/// インスタンスの取得
		/// </summary>
		/// <returns>インスタンス</returns>
		static ResourceReleaser* GetInstance();
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
		/// <summary>
		/// 手動リリースするリソースの追加
		/// </summary>
		/// <param name="resource">リソース</param>
		void AddManualResource(Microsoft::WRL::ComPtr<ID3D12Resource>&& resource);

	private:
		ResourceReleaser() = default;
		~ResourceReleaser() = default;
		ResourceReleaser(const ResourceReleaser&) = delete;
		ResourceReleaser& operator=(const ResourceReleaser&) = delete;

	private:
		std::list<Microsoft::WRL::ComPtr<ID3D12Resource>> list_; // リスト
		std::list<Microsoft::WRL::ComPtr<ID3D12Resource>> manualList_; // 手動リリースするリスト
	};
}
