#include "DrawerBase.h"
#include "DirectXBase/DirectXBase.h"
#include "ModelDataManager.h"
#include "GraphicsPipelineSystem/GraphicsPiplineManager/GraphicsPiplineManager.h"
#include "TextureManager.h"
#include "Drawers/DrawManager/DrawManager.h"

ID3D12GraphicsCommandList* DrawerBase::commandList_ = nullptr;
GraphicsPipelineManager* DrawerBase::psoManager_ = nullptr;
ModelDataManager* DrawerBase::modelDataManager_ = nullptr;
TextureManager* DrawerBase::textureManager_ = nullptr;
DrawManager* DrawerBase::drawManager_ = nullptr;

void DrawerBase::StaticInitialize()
{
	commandList_ = DirectXBase::GetInstance()->GetCommandList();
	psoManager_ = GraphicsPipelineManager::GetInstance();
	modelDataManager_ = ModelDataManager::GetInstance();
	textureManager_ = TextureManager::GetInstance();
	drawManager_ = DrawManager::GetInstance();
	drawManager_->Initialize();
}

void DrawerBase::BeginFrame()
{
	commandList_ = DirectXBase::GetInstance()->GetCommandList();
}
