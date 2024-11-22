#include "DrawManagerBase.h"
#include "DirectXBase/DirectXBase.h"
#include "GraphicsPipelineSystem/GraphicsPiplineManager/GraphicsPiplineManager.h"

ID3D12GraphicsCommandList* DrawManagerBase::commandList_ = nullptr;
GraphicsPipelineManager* DrawManagerBase::psoManager_ = nullptr;

void DrawManagerBase::StaticInitialize()
{
	commandList_ = DirectXBase::GetInstance()->GetCommandList();
	psoManager_ = GraphicsPipelineManager::GetInstance();
}

void DrawManagerBase::Reset()
{
	drawNo_ = 0;
}
