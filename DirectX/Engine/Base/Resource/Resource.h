#pragma once
#include <wrl.h>
#include <d3d12.h>

// 響子
namespace Kyoko {
	/// <summary>
	/// 基底リソース
	/// </summary>
	class BaseResource
	{
	public:

		virtual ~BaseResource() = default;

		/// <summary>
		/// バッファリソースの生成
		/// </summary>
		/// <param name="sizeInBytes">サイズ</param>
		/// <param name="resourceFlags">リソースフラグ</param>
		void CreateResource(size_t sizeInBytes, D3D12_RESOURCE_FLAGS resourceFlags = D3D12_RESOURCE_FLAG_NONE);

		/// <summary>
		/// マッピング
		/// </summary>
		/// <param name="ppData">ポインタ</param>
		/// <param name="Subresource">サブリソースのインデックス</param>
		/// <param name="pReadRange">範囲</param>
		void Map(void** ppData, UINT subresource = 0, const D3D12_RANGE* pReadRange = nullptr);

		/// <summary>
		/// GPUアドレスの取得
		/// </summary>
		/// <returns>GPUアドレス</returns>
		const D3D12_GPU_VIRTUAL_ADDRESS GetGPUVirtualAddress() const;

		/// <summary>
		/// ComPtrの取得
		/// </summary>
		/// <returns>ComPtr</returns>
		ID3D12Resource* Get() const;

		/// <summary>
		/// ポインタのアドレスの取得
		/// </summary>
		/// <returns>ポインタのアドレス</returns>
		ID3D12Resource** GetAddressOf();

	protected:
		Microsoft::WRL::ComPtr<ID3D12Resource> resource_;
	};

	/// <summary>
	/// 手動で解放するリソース
	/// </summary>
	class ResourceManualRelease : public BaseResource
	{
	public:
		~ResourceManualRelease() override;
	};
	/// <summary>
	/// 自動で開放されるリソース
	/// </summary>
	class ResourceAutoRelease : public BaseResource
	{
	public:
		~ResourceAutoRelease() override;
	};
}