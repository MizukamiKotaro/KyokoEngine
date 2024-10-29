#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include "CameraVMDData.h"

class CameraVMDDataManager {
public:
	static CameraVMDDataManager* GetInstance();

	void Initialize();
	const CameraVMDData* LoadVMDData(const std::string& filePath);

private:
	CameraVMDDataManager() = default;
	~CameraVMDDataManager() = default;
	CameraVMDDataManager(const CameraVMDDataManager&) = delete;
	CameraVMDDataManager& operator=(const CameraVMDDataManager&) = delete;

private:
	const std::string directoryPath_ = "Resources/CameraAnimation/";
	std::unordered_map<std::string, std::unique_ptr<CameraVMDData>> dataMap_;
};