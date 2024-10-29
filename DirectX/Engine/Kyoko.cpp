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
#include "GraphicsPipelineSystem/GraphicsPiplineManager/GraphicsPiplineManager.h"
#include "AudioManager/AudioManager.h"
#include "FrameInfo/FrameInfo.h"
#include "SkinningModel/SkinningModel.h"
#include "BasePostEffect/BasePostEffect.h"
#include "LightSingleton/LightSingleton.h"
#include "Drawers/IDrawer/IDrawer.h"
#include "VolumeManager/VolumeManager.h"
#include "Audio.h"
#include "GlobalVariables/GlobalVariableUser.h"
#include "ParticleManager.h"
#include "Drawers/DrawManager/DrawManager.h"
#include "Drawers/IDrawManager/IDrawManager.h"
#include "LevelDataLoader/LevelDataLoader.h"
#include "ComputePipelineSystem/ComputePipelineManager/ComputePipelineManager.h"
#include "InstancingModels/InstancingResourceManager.h"
#include "MMD/CameraVMD/CameraVMDDataManager.h"

static ResourceLeackChecker leakCheck;

DirectXBase* dxBase;
WindowsInfo* winInfo;
GraphicsPipelineManager* gpoManager;
AudioManager* audioManager;
Input* inputManager;
GlobalVariables* globalVariables;
VolumeManager* volumeManager;
DrawManager* drawManager;

void Kyoko::Engine::Initialize(const char* windowName, int width, int height)
{
	// ウィンドウの初期化
	HRESULT hr = CoInitializeEx(0, COINIT_MULTITHREADED);
	SUCCEEDED(hr);
	winInfo = WindowsInfo::GetInstance();
	winInfo->CreateGameWindow(windowName, width, height);

	// DirectXの初期化
	dxBase = DirectXBase::GetInstance();
	dxBase->Initialize();

	// ImGuiの初期化
	Kyoko::ImGuiManager::Initialize();

	// テクスチャマネージャの初期化
	TextureManager::GetInstance()->Initialize();

	// パイプラインの初期化
	gpoManager = GraphicsPipelineManager::GetInstance();
	gpoManager->Initialize();
	ComputePipelineManager::GetInstance()->Initialize();

	// グローバル変数の初期化
	globalVariables = GlobalVariables::GetInstance();
	globalVariables->Initialize();
	globalVariables->LoadFiles();
	GlobalVariableUser::StaticInitialize();

	// 描画関係の初期化
	ModelDataManager::GetInstance()->Initialize();
	IDrawer::StaticInitialize();
	IDrawManager::StaticInitialize();
	BasePostEffect::StaticInitialize();
	ParticleManager::GetInstance()->FirstInitialize();
	drawManager = DrawManager::GetInstance();
	drawManager->Initialize();
	SkinningModel::StaticInitialize();
	LightSingleton::GetInstance()->Initialize();
	CameraVMDDataManager::GetInstance()->Initialize();

	// レベルデータのロード
	LevelDataLoader::GetInstance()->LoadFiles();

	// オーディオ関係の初期化
	audioManager = AudioManager::GetInstance();
	audioManager->Initialize();
	volumeManager = VolumeManager::GetInstance();
	volumeManager->Initialize();
	Audio::StaticInitialize();

	// 入力の初期化
	inputManager = Input::GetInstance();
	inputManager->Initialize();

	// フレーム関係の初期化
	FrameInfo::GetInstance()->Initialize();

#ifdef _DEBUG
	ID3D12InfoQueue* infoQueue = nullptr;
	if (SUCCEEDED(dxBase->GetDevice()->QueryInterface(IID_PPV_ARGS(&infoQueue)))) {
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

const bool Kyoko::Engine::ProcessMessage()
{
	return winInfo->ProcessMessage();
}

void Kyoko::Engine::FirstUpdateInLoop()
{
#ifdef _DEBUG
	// ImGuiの毎フレームの初期化
	ImGuiManager::Begin();
	// グローバル変数の更新
	globalVariables->Update();
	// ボリュームの更新
	volumeManager->Update();
#endif // _DEBUG
	// 入力の更新
	inputManager->Update();
	// オーディオの更新
	audioManager->Update();
	// 描画マネージャのリセット
	drawManager->Reset();
}

void Kyoko::Engine::PreDraw()
{
	// ImGuiの描画前処理
	ImGuiManager::End();
	// 描画前処理
	dxBase->PreDraw();
	// グラフィックスパイプラインオブジェクトの描画前処理
	gpoManager->PreDraw();
}

void Kyoko::Engine::PostDraw()
{
	// ImGuiの描画
	ImGuiManager::Draw();
	// 描画後処理
	dxBase->PostDraw();
}

void Kyoko::Engine::Finalize()
{
#pragma region 基盤システムの終了
#ifdef _DEBUG
	globalVariables->Finalize();
#endif // _DEBUG
	// 解放、終了処理
	ImGuiManager::Finalize();
	CoUninitialize();
	audioManager->Finalize();
	InstancingResourceManager::GetInstance()->Finalize();
	TextureManager::GetInstance()->Finalize();
	ModelDataManager::GetInstance()->Finalize();
	DescriptorHeapManager::GetInstance()->Finalize();
	dxBase->Finalize();
	winInfo->Finalize();

#pragma endregion 基盤システムの終了
}