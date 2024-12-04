#pragma once

#include <wrl.h>
#include <dxcapi.h>
#pragma comment(lib, "dxcompiler.lib")
#include <string>
#include <d3d12.h>
#include <unordered_map>
#include <memory>
#include <vector>

class ComputePipeline
{
public:
	// namespace省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

	void Initialize();

	/// <summary>
	/// コマンドリストの更新
	/// </summary>
	static void BeginFrame();

	void PreCompute();

	virtual ~ComputePipeline() = default;
protected:

	void InitializeDXC();

	virtual void InitializePSO() = 0;

	void CreatePSO();

	//コンパイル用関数
	IDxcBlob* CompileShader(
		//compilerするShaderファイルへパス
		const std::wstring& filePath,
		//compilerに使用するprofile
		const wchar_t* profile,
		//初期化で生成したもの3つ
		IDxcUtils* dxcUtils,
		IDxcCompiler3* dxcCompiler,
		IDxcIncludeHandler* includeHandler);
protected:

	ID3D12Device* device_ = nullptr;
	static ID3D12GraphicsCommandList* commandList_;

	ComPtr<IDxcUtils> dxcUtils_;
	ComPtr<IDxcCompiler3> dxcCompiler_;
	ComPtr<IDxcIncludeHandler> includeHandler_;

	ComPtr<ID3DBlob> signatureBlob_;
	ComPtr<ID3DBlob> errorBlob_;
	ComPtr<ID3D12RootSignature> rootSignature_;

	ComPtr<IDxcBlob> computeShaderBlob_;

	ComPtr<ID3D12PipelineState> computePipelineStates_;
};

