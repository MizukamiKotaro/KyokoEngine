#include "HighLumi.h"

HighLumi::HighLumi()
{
	piplineType_ = GraphicsPiplineManager::PiplineType::HIGH_LUMI;

	CreatePostEffect();
}

HighLumi::~HighLumi()
{
	
}

