#pragma once

#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include <vector>
#include <chrono>

class WindowsInfo;
class DescriptorHandles;

// DirectXの基盤クラス
class DirectXBase
{
public: // メンバ関数

	// namespace省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

	/// <summary>
	/// インスタンスの取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static DirectXBase* GetInstance();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();

	/// <summary>
	/// 描画前処理
	/// </summary>
	void PreDraw();

	/// <summary>
	/// 描画後処理
	/// </summary>
	void PostDraw();

	/// <summary>
	/// デバイスの取得
	/// </summary>
	/// <returns>デバイス</returns>
	ID3D12Device* GetDevice() const { return device_.Get(); }

	/// <summary>
	/// コマンドリストの取得
	/// </summary>
	/// <returns>コマンドリスト</returns>
	ID3D12GraphicsCommandList* GetCommandList() const { return commandList_.Get(); }

	/// <summary>
	/// バッファリソースの生成
	/// </summary>
	/// <param name="sizeInBytes">サイズ</param>
	/// <param name="resourceFlags">リソースフラグ</param>
	/// /// <returns>バッファリソース</returns>
	static ID3D12Resource* CreateBufferResource(size_t sizeInBytes, D3D12_RESOURCE_FLAGS resourceFlags = D3D12_RESOURCE_FLAG_NONE);

private:

	/// <summary>
	/// FPS固定初期値
	/// </summary>
	void InitializeFixFPS();

	/// <summary>
	/// FPS固定更新
	/// </summary>
	void UpdateFixFPS();


private: // メンバ変数

	WindowsInfo* windowInfo_ = nullptr;
	ComPtr<ID3D12Debug1> debugController_;
	ComPtr<IDXGIFactory7> dxgiFactory_;
	ComPtr<ID3D12Device> device_;
	ComPtr<IDXGIAdapter4> useAdapter_;
	ComPtr<ID3D12CommandQueue> commandQueue_;
	ComPtr<ID3D12CommandAllocator> commandAllocator_; 
	ComPtr<ID3D12GraphicsCommandList> commandList_;
	ComPtr<IDXGISwapChain4> swapChain_;
	std::vector<ComPtr<ID3D12Resource>> backBuffers_;
	ComPtr<ID3D12Resource> depthStencilResource_;
	ComPtr<ID3D12Fence> fence_;
	uint64_t fenceValue_ = 0;

	std::vector<const DescriptorHandles*> rtvHandles_;
	const DescriptorHandles* dsvHandles_ = nullptr;

	// 記録時間(FPS固定)
	std::chrono::steady_clock::time_point reference_;

private: // メンバ関数
	DirectXBase() = default;
	~DirectXBase() = default;
	DirectXBase(const DirectXBase&) = delete;
	const DirectXBase& operator=(const DirectXBase&) = delete;
	/// <summary>
	/// デバッグコントローラーの初期化
	/// </summary>
	void InitializeDebugController();

	/// <summary>
	/// DXGIデバイス初期化
	/// </summary>
	void InitializeDXGIDevice();

	/// <summary>
	/// スワップチェーンの生成
	/// </summary>
	void CreateSwapChain();

	/// <summary>
	/// コマンド関連初期化
	/// </summary>
	void InitializeCommand();

	/// <summary>
	/// レンダーターゲット生成
	/// </summary>
	void CreateFinalRenderTargets();

	/// <summary>
	/// 深度バッファ生成
	/// </summary>
	void CreateDepthBuffer();

	/// <summary>
	/// ディプスリソースの生成
	/// </summary>
	/// <param name="width">横幅</param>
	/// <param name="height">縦幅</param>
	/// /// <returns>ディプスリソース</returns>
	ID3D12Resource* CreateDepthStencilTextureResource(int32_t width, int32_t height);

	/// <summary>
	/// フェンス生成
	/// </summary>
	void CreateFence();
};