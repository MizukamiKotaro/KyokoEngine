#pragma once
#include <wrl.h>
#include <string>
#include <vector>
#include <memory>
#include "DescriptorHeapManager/Descriptor/Descriptor.h"

/// <summary>
/// ディスクリプターヒープ
/// </summary>
class DescriptorHeap {
public:
	// namespace省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	~DescriptorHeap();
public:
	/// <summary>
	/// ディスクリプターの削除
	/// </summary>
	/// <param name="handle">ハンドル</param>
	void DeleteDescriptor(const DescriptorHandles* handle);
	/// <summary>
	/// ディスクリプターヒープの取得
	/// </summary>
	/// <returns>ディスクリプターヒープ</returns>
	ID3D12DescriptorHeap* GetHeap() { return heap_.Get(); }
	/// <summary>
	/// 新しいディスクリプターハンドルの取得
	/// </summary>
	/// <returns>ハンドル</returns>
	const DescriptorHandles* GetNewDescriptorHandle();
	/// <summary>
	/// 新しいテクスチャ用のディスクリプターハンドルの取得
	/// </summary>
	/// <returns>ハンドル</returns>
	const DescriptorHandles* GetNewTextureDescriptorHandle();
	/// <summary>
	/// テクスチャ用の最初のGPUハンドルの取得
	/// </summary>
	/// <returns>GPUハンドル</returns>
	const D3D12_GPU_DESCRIPTOR_HANDLE& GetTextureFirstHandle();
	/// <summary>
	/// ディスクリプターヒープの作成
	/// </summary>
	/// <param name="device,">デバイス</param>
	/// <param name="heapType">ヒープタイプ</param>
	/// <param name="numDescriptors">ディスクリプターの数</param>
	/// <param name="shaderVisible">SHADER_VISIBLEにするか</param>
	/// <returns>ディスクリプターヒープ</returns>
	static ID3D12DescriptorHeap* CreateDescriptorHeap(ID3D12Device* device, D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescriptors, bool shaderVisible);
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="numDescriptors">ディスクリプターの数</param>
	void Initialize(UINT numDescriptors);
	/// <summary>
	/// テクスチャのナンバーの取得
	/// </summary>
	/// <param name="handle">ハンドル</param>
	/// <returns>テクスチャのナンバー</returns>
	uint32_t GetTextureNo(const DescriptorHandles* handle);

protected:

	ComPtr<ID3D12DescriptorHeap> heap_; // ディスクリプターヒープ
	D3D12_DESCRIPTOR_HEAP_TYPE heapType_; // ヒープタイプ
	std::vector<std::unique_ptr<Descriptor>> descriptors_; // ディスクリプターズ
};