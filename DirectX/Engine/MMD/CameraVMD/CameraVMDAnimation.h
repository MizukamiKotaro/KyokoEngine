#pragma once
#include "CameraVMDData.h"
#include <string>

class CameraVMDAnimation
{
public:
	CameraVMDAnimation(const std::string& path);
	void LoadVMDAnimationData(const std::string& path);
	void Initialize();
	void Update(const float& deltaTime);
	const CameraVMDFrame& GetState() const;
	void SetTime(const float& time);

private:
	float Interpolation(const std::vector<uint8_t>& bezier, const float& t);
	void SetBezier(std::vector<uint8_t> bezier, const uint8_t& start, const size_t& num);

	CameraVMDFrame state_;
	size_t num_;
	const CameraVMDData* data_;
};

