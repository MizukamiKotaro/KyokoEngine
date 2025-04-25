#include "ImGuiManager.h"

#ifdef _DEBUG
#pragma comment(lib, "winmm.lib")
#include "Engine/Base/DirectXBase/DirectXBase.h"
#include "Engine/Base/WindowsInfo/WindowsInfo.h"
#include "Engine/Base/Descriptor/DescriptorHeapManager/DescriptorHeapManager.h"
#include "Descriptor/DescriptorHeap/DescriptorHeap.h"
#include "Externals/imgui/imgui_impl_dx12.h"
#include "Externals/imgui/imgui_impl_win32.h"
#include "Externals/imgui/ImGuizmo.h"
bool isDrawMonitor = false;
#endif // _DEBUG

void Kyoko::ImGuiManager::Initialize()
{
#ifdef _DEBUG
	Kyoko::Descriptor::DescriptorHeap* srvHeap = Kyoko::Descriptor::DescriptorHeapManager::GetInstance()->GetSRVDescriptorHeap();

	const Kyoko::Descriptor::DescriptorHandles* handles = srvHeap->GetNewDescriptorHandle();

	//ImGuiの初期化
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(WindowsInfo::GetInstance()->GetHwnd());
	ImGui_ImplDX12_Init(DirectXBase::GetInstance()->GetDevice(),
		2,
		DXGI_FORMAT_R8G8B8A8_UNORM_SRGB,
		srvHeap->GetHeap(),
		handles->cpuHandle,
		handles->gpuHandle);

	// 日本語対応
	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF("Resources/Font/GenShinGothic-Heavy.ttf", 16.0f, nullptr, ImGui::GetIO().Fonts->GetGlyphRangesJapanese());
	io.ConfigFlags = ImGuiConfigFlags_DockingEnable;

	// ギズモの設定
	ImGuizmo::SetImGuiContext(ImGui::GetCurrentContext());
	Vector2 size = WindowsInfo::GetInstance()->GetWindowSize();
	ImGuizmo::SetOrthographic(false);
	ImGuizmo::SetRect(0, 0, size.x, size.y);
#endif // _DEBUG
}

void Kyoko::ImGuiManager::Finalize()
{
#ifdef _DEBUG
	//解放処理
	ImGui_ImplDX12_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
#endif // _DEBUG
}

void Kyoko::ImGuiManager::Begin()
{
#ifdef _DEBUG
	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ImGuizmo::BeginFrame();
#endif // _DEBUG
}

void Kyoko::ImGuiManager::End()
{
#ifdef _DEBUG
	//ImGuiの内部コマンドを生成する
	ImGui::Render();
#endif // _DEBUG
}

void Kyoko::ImGuiManager::Draw()
{
#ifdef _DEBUG
	//実際のcommandListのImGuiの描画コマンドを積む。描画処理の終わったタイミング
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), DirectXBase::GetInstance()->GetCommandList());
#endif // _DEBUG
}