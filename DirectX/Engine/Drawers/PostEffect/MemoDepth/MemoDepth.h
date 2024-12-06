#pragma once
#include "BasePostEffect/BasePostEffect.h"

class Camera;

class MemoDepth : public BasePostEffect
{
public:
	MemoDepth(const Vector2& size = windowSize_);
	~MemoDepth() override;

	const DescriptorHandles& GetDepthHandle() { return *depthHandles_; }
	void ToReadBarrier();
	void ToWriteBarrier();
private:
	void CreateDepthRes();
	void CreateResources() override;
private:
	const DescriptorHandles* depthHandles_;
};