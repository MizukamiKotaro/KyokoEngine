#pragma once
#include <memory>

class DescriptorHeap;

/// <summary>
/// ディスクリプターヒープのマネージャー
/// </summary>
class DescriptorHeapManager {
public:
	/// <summary>
	/// インスタンスの取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static DescriptorHeapManager* GetInstance();
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// フレームの最初の処理、使用してないディスクリプターの削除
	/// </summary>
	void BeginFrame();
	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();
	/// <summary>
	/// SRV用ディスクリプターヒープの取得
	/// </summary>
	/// <returns>SRV用ディスクリプターヒープ</returns>
	DescriptorHeap* GetSRVDescriptorHeap() { return srvHeap_.get(); }
	/// <summary>
	/// RTV用ディスクリプターヒープのの取得
	/// </summary>
	/// <returns>RTV用ディスクリプターヒープ</returns>
	DescriptorHeap* GetRTVDescriptorHeap() { return rtvHeap_.get(); }
	/// <summary>
	/// DSV用ディスクリプターヒープの取得
	/// </summary>
	/// <returns>DSV用ディスクリプターヒープ</returns>
	DescriptorHeap* GetDSVDescriptorHeap() { return dsvHeap_.get(); }

private:
	DescriptorHeapManager() = default;
	~DescriptorHeapManager() = default;
	DescriptorHeapManager(const DescriptorHeapManager&) = delete;
	DescriptorHeapManager& operator=(const DescriptorHeapManager&) = delete;

private:
	std::unique_ptr<DescriptorHeap> srvHeap_; // SRV用ディスクリプターヒープ
	std::unique_ptr<DescriptorHeap> rtvHeap_; // RTV用ディスクリプターヒープ
	std::unique_ptr<DescriptorHeap> dsvHeap_; // DSV用ディスクリプターヒープ
};