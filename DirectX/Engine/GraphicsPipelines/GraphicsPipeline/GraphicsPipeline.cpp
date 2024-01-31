#include "GraphicsPipeline.h"
#include "Engine/Base/DirectXBase/DirectXBase.h"
#include <cassert>
#include "Engine/Base/DebugLog/DebugLog.h"
#include <format>



void GraphicsPipeline::Initialize()
{

	device_ = DirectXBase::GetInstance()->GetDevice();
	commandList_ = DirectXBase::GetInstance()->GetCommandList();

	InitializeDXC();

	InitializePSO();

}

void GraphicsPipeline::PreDraw()
{
	blendMode_ = BlendMode::kBlendModeNormal;

	//RootSignatureを設定。PSOに設定しているけど別途設定が必要
	commandList_->SetGraphicsRootSignature(rootSignature_.Get());
	commandList_->SetPipelineState(graphicsPipelineStates_[blendMode_].Get()); // PSOを設定
	//形状を設定。PSOに設定しているものとは別。同じものを設定すると考えておけばいい
	commandList_->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

}

void GraphicsPipeline::SetBlendMode(uint32_t blendMode)
{
	if (static_cast<uint32_t>(blendMode_) != blendMode) {

		switch (blendMode)
		{
		case 0:
			blendMode_ = BlendMode::kBlendModeNone;
			break;
		case 1:
			blendMode_ = BlendMode::kBlendModeNormal;
			break;
		case 2:
			blendMode_ = BlendMode::kBlendModeAdd;
			break;
		case 3:
			blendMode_ = BlendMode::kBlendModeSubtract;
			break;
		case 4:
			blendMode_ = BlendMode::kBlendModeMultiply;
			break;
		case 5:
			blendMode_ = BlendMode::kBlendModeScreen;
			break;
		default:
			blendMode_ = BlendMode::kBlendModeNormal;
			break;
		}

		commandList_->SetPipelineState(graphicsPipelineStates_[blendMode_].Get());
	}
}

void GraphicsPipeline::InitializeDXC()
{

	//DXCの初期化
	HRESULT hr = DxcCreateInstance(CLSID_DxcUtils, IID_PPV_ARGS(dxcUtils_.GetAddressOf()));
	assert(SUCCEEDED(hr));
	hr = DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(dxcCompiler_.GetAddressOf()));
	assert(SUCCEEDED(hr));

	//現時点ではincludeはしないが、includeに対応するための設定を行っておく
	hr = dxcUtils_->CreateDefaultIncludeHandler(includeHandler_.GetAddressOf());
	assert(SUCCEEDED(hr));

}

IDxcBlob* GraphicsPipeline::CompileShader(const std::wstring& filePath, const wchar_t* profile, IDxcUtils* dxcUtils, IDxcCompiler3* dxcCompiler, IDxcIncludeHandler* includeHandler)
{
	// 1. hlslファイルを読む
	//これからシェーダーをコンパイルする旨をログに出す
	DebugLog::Log(DebugLog::ConvertString(std::format(L"Begin CompileShader,path:{},profile:{}\n", filePath, profile)));
	//hlslファイルを読む
	IDxcBlobEncoding* shaderSource = nullptr;
	HRESULT hr = dxcUtils->LoadFile(filePath.c_str(), nullptr, &shaderSource);
	//読めなかったら止める
	assert(SUCCEEDED(hr));
	//見込んだファイルの内容を設定する
	DxcBuffer shaderSourceBuffer;
	shaderSourceBuffer.Ptr = shaderSource->GetBufferPointer();
	shaderSourceBuffer.Size = shaderSource->GetBufferSize();
	shaderSourceBuffer.Encoding = DXC_CP_UTF8;//UTF8の文字コードであることを通知

	// 2. compileする
	LPCWSTR arguments[] = {
		filePath.c_str(),//コンパイル対象のhlslファイル名
		L"-E",L"main",//エントリーポイントの指定。基本的にmain以外にはしない
		L"-T",profile,//ShaderProfileの設定
		L"-Zi",L"-Qembed_debug",//デバッグ用の情報を読み込む
		L"-Od",//最適化を外しておく
		L"-Zpr",//メモリレイアウトは優先
	};
	//実際にshaderをコンパイルする
	IDxcResult* shaderResult = nullptr;
	hr = dxcCompiler->Compile(
		&shaderSourceBuffer,//読み込んだファイル
		arguments,          //コンパイルオプション
		_countof(arguments),//コンパイルオプションの数
		includeHandler,     //includeが含まれた諸々
		IID_PPV_ARGS(&shaderResult)//コンパイル結果
	);
	//コンパイルエラーではなくdxcが起動できないなど致命的な状況
	assert(SUCCEEDED(hr));

	// 3. 警告・エラーが出ていないか確認する
	IDxcBlobUtf8* shaderError = nullptr;
	hr = shaderResult->GetOutput(DXC_OUT_ERRORS, IID_PPV_ARGS(&shaderError), nullptr);
	if (shaderError != nullptr && shaderError->GetStringLength() != 0) {
		DebugLog::Log(shaderError->GetStringPointer());
		assert(false);
	}

	// 4. compile結果を受け取って返す
	//コンパイル結果から実行用のバイナリ部分を取得
	IDxcBlob* shaderBlob = nullptr;
	hr = shaderResult->GetOutput(DXC_OUT_OBJECT, IID_PPV_ARGS(&shaderBlob), nullptr);
	assert(SUCCEEDED(hr));
	//成功したログを出す
	DebugLog::Log(DebugLog::ConvertString(std::format(L"Compile Succeeded, path:{}, prefile:{}\n", filePath, profile)));
	//もう使わないリソースを開放
	shaderSource->Release();
	shaderResult->Release();
	//実行用のバイナリを返却
	return shaderBlob;
}
