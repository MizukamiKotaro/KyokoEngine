#include "Kyoko.h"
#include "Engine/Base/WindowsInfo/WindowsInfo.h"
#include "Engine/Base/ResourceLeakChecker.h"
#include "Engine/Base/DirectXBase/DirectXBase.h"
#include "Input/Input.h"
#include "TextureManager/TextureManager.h"
#include "ImGuiManager/ImGuiManager.h"
#include "GlobalVariables/GlobalVariables.h"
#include "Engine/Base/DescriptorHeapManager/DescriptorHeapManager.h"
#include "ModelDataManager.h"
#include "Utils/RandomGenerator/RandomGenerator.h"
#include "GraphicsPipelines/GraphicsPiplineManager/GraphicsPiplineManager.h"
#include "Audio.h"
#include "Light/Light.h"
#include "FrameInfo/FrameInfo.h"

void Kyoko::Initialize(const char* windowName, int width, int height)
{
	static ResourceLeackChecker leakCheck;

	HRESULT hr = CoInitializeEx(0, COINIT_MULTITHREADED);
	SUCCEEDED(hr);

#pragma region 基盤システムの初期化

	WindowsInfo::GetInstance()->CreateGameWindow(windowName, width, height);

	DirectXBase* dxCommon = DirectXBase::GetInstance();
	dxCommon->Initialize();

	TextureManager::GetInstance()->Initialize();

	GraphicsPiplineManager::GetInstance()->Initialize();

	AudioManager::GetInstance()->Initialize();

	Input::GetInstance()->Initialize();

	LightSingleton::GetInstance()->Initialize();

	GlobalVariables::GetInstance()->LoadFiles();

	FrameInfo::GetInstance()->Initialize();

	ImGuiManager::Initialize();

#pragma endregion 基盤システムの初期化

#ifdef _DEBUG
	ID3D12InfoQueue* infoQueue = nullptr;
	if (SUCCEEDED(dxCommon->GetDevice()->QueryInterface(IID_PPV_ARGS(&infoQueue)))) {
		//ヤバいエラーの時に止まる
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, true);
		//エラーのときに止まる
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, true);
		//警告時に止まる
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING, true);

		//抑制するメッセージのID
		D3D12_MESSAGE_ID denyIds[] = {
			//windows11でのDXGIデバッグレイヤーとDX12デバッグレイヤーの相互作用バグによるエラーバグ
			//https:://stackoverflow.com/question/69805245/directx-12-application-is-crashing-in-windows-11
			D3D12_MESSAGE_ID_RESOURCE_BARRIER_MISMATCHING_COMMAND_LIST_TYPE
		};
		//抑制するレベル
		D3D12_MESSAGE_SEVERITY severities[] = { D3D12_MESSAGE_SEVERITY_INFO };
		D3D12_INFO_QUEUE_FILTER filter{};
		filter.DenyList.NumIDs = _countof(denyIds);
		filter.DenyList.pIDList = denyIds;
		filter.DenyList.NumSeverities = _countof(severities);
		filter.DenyList.pSeverityList = severities;
		//指定したメッセージの表示を抑制する
		infoQueue->PushStorageFilter(&filter);

		//解放
		infoQueue->Release();
	}
#endif // _DEBUG
}

const bool Kyoko::ProcessMessage()
{
	return WindowsInfo::GetInstance()->ProcessMessage();
}

void Kyoko::FirstUpdateInLoop()
{
	ImGuiManager::Begin();
	Input::GetInstance()->Update();
	AudioManager::GetInstance()->Update();

	GlobalVariables::GetInstance()->Update();
}

void Kyoko::PreDraw()
{
	ImGuiManager::End();

	// 描画前処理
	DirectXBase::GetInstance()->PreDraw();

	GraphicsPiplineManager::GetInstance()->PreDraw();
}

void Kyoko::PostDraw()
{
	ImGuiManager::Draw();

	// 描画後処理
	DirectXBase::GetInstance()->PostDraw();
}

void Kyoko::Finalize()
{
#pragma region 基盤システムの終了
	ImGuiManager::Finalize();

	CoUninitialize();
	AudioManager::GetInstance()->Finalize();
	TextureManager::GetInstance()->Finalize();
	ModelDataManager::GetInstance()->Finalize();
	DescriptorHeapManager::GetInstance()->Finalize();
	DirectXBase::GetInstance()->Finalize();
	WindowsInfo::GetInstance()->Finalize();

#pragma endregion 基盤システムの終了

}
