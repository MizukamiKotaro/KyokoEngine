#include "CameraVMDDataManager.h"
#include <filesystem>
#include <cassert>
#include <fstream>
#include "GlobalVariables/GlobalVariableComboNames.h"

CameraVMDDataManager* CameraVMDDataManager::GetInstance()
{
	static CameraVMDDataManager instance;
	return &instance;
}

void CameraVMDDataManager::Initialize()
{
	GlobalVariableComboNames* combo_ = GlobalVariableComboNames::GetInstance();

	std::filesystem::path dir(directoryPath_);
	for (const std::filesystem::directory_entry& entry : std::filesystem::recursive_directory_iterator(dir)) {
		const std::filesystem::path& filePath = entry.path();
		std::string fileName = filePath.stem().string();
		combo_->AddComboName(ComboNameType::kCameraAnimationVMD, fileName);
		LoadVMDData(fileName);
	}
}

const CameraVMDData* CameraVMDDataManager::LoadVMDData(const std::string& filePath)
{
	std::string path = filePath + ".vmd";
	if (dataMap_.find(path) != dataMap_.end()) {
		return dataMap_[path].get();
	}

	std::filesystem::path filePathName(path);
	std::string dataFilePath = filePathName.filename().string();

	std::filesystem::path dir(directoryPath_);
	bool found = false;
	for (const std::filesystem::directory_entry& entry : std::filesystem::recursive_directory_iterator(dir)) {
		if (entry.is_regular_file() && entry.path().filename().string() == dataFilePath) {
			dataFilePath = entry.path().string();
			found = true;
			break;
		}
	}
	assert(found);
	dataMap_[path] = std::make_unique<CameraVMDData>();

	std::ifstream file(dataFilePath, std::ios::binary);
	assert(file.is_open());
	
	// バイト数は https://hariganep.seesaa.net/article/201103article_1.html より

	char header[50];
	file.read(header, 50);

	// ボーンアニメーションの数を読み込む
	uint32_t boneAnimationCount;
	file.read(reinterpret_cast<char*>(&boneAnimationCount), sizeof(boneAnimationCount));

	// ボーンアニメーションのスキップ
	for (uint32_t i = 0; i < boneAnimationCount; ++i) {
		file.seekg(111, std::ios::cur); // ボーンデータをスキップ
	}

	// 表情アニメーションの数を読み込む
	uint32_t expressionAnimationCount;
	file.read(reinterpret_cast<char*>(&expressionAnimationCount), sizeof(expressionAnimationCount));

	// 表情アニメーションのスキップ
	for (uint32_t i = 0; i < expressionAnimationCount; ++i) {
		file.seekg(23, std::ios::cur); // 表情データをスキップ
	}

	uint32_t cameraFrameCount;
	file.read(reinterpret_cast<char*>(&cameraFrameCount), sizeof(cameraFrameCount));
	for (uint32_t i = 0; i < cameraFrameCount; ++i) {
		CameraVMDFrame frame;
		float pos[3];
		float rot[3];

		file.read(reinterpret_cast<char*>(&frame.frameNumber), sizeof(frame.frameNumber));
		file.read(reinterpret_cast<char*>(&frame.distance), sizeof(frame.distance));
		file.read(reinterpret_cast<char*>(pos), sizeof(pos));
		file.read(reinterpret_cast<char*>(rot), sizeof(rot));
		file.read(reinterpret_cast<char*>(frame.bezier), sizeof(frame.bezier));
		file.read(reinterpret_cast<char*>(&frame.fov), sizeof(frame.fov));
		file.read(reinterpret_cast<char*>(&frame.parth), sizeof(frame.parth));

		frame.position = { pos[0],pos[1],pos[2] };
		frame.rotation = { -rot[0],-rot[1],rot[2] };

		// 時間に変換
		frame.time = float(frame.frameNumber) / 15.0f;

		if (i != 0) {
			// フレームの差が1以下の時の時間の処理
			if (frame.frameNumber - dataMap_[path]->frames.back().frameNumber <= 1.0f) {
				dataMap_[path]->frames.back().time = frame.time - 0.00001f;
			}
		}

		dataMap_[path]->frames.push_back(frame);
	}

	std::sort(dataMap_[path]->frames.begin(), dataMap_[path]->frames.end(),[](const CameraVMDFrame& a, const CameraVMDFrame& b) {
			return a.frameNumber < b.frameNumber;
	});

	dataMap_[path]->duration = dataMap_[path]->frames.back().time;

	file.close();

	return dataMap_[path].get();
}
