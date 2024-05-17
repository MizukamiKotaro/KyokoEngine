#pragma once
#include <string>

class LevelDataLoader 
{
public:
	static LevelDataLoader* GetInstance();

	void LoadFiles();

	void LoadFile(const std::string& filePath);

private:
	LevelDataLoader() = default;
	~LevelDataLoader() = default;
	LevelDataLoader(const LevelDataLoader& obj) = delete;
	LevelDataLoader& operator=(const LevelDataLoader& obj) = delete;
};