#include "LevelDataLoader.h"
#include "Externals/nlohmann/json.hpp"
#include <fstream>
#include <Windows.h>

const std::string kDirectoryPath = "Resources/LevelDatas/";

LevelDataLoader* LevelDataLoader::GetInstance()
{
	static LevelDataLoader instance;
	return &instance;
}

void LevelDataLoader::LoadFiles()
{
	std::filesystem::path dir(kDirectoryPath);

	if (!std::filesystem::exists(dir)) {
		return;
	}

	std::filesystem::directory_iterator dir_it(dir);
	for (const std::filesystem::directory_entry& entry : dir_it) {

		const std::filesystem::path& filePath = entry.path();

		std::string extension = filePath.extension().string();

		if (extension.compare(".json") != 0) {
			continue;
		}

		std::filesystem::path relativePath = std::filesystem::relative(filePath, dir);

		LoadFile(relativePath.string());
	}
}

void LevelDataLoader::LoadFile(const std::string& filePath)
{
	std::string fullpath = kDirectoryPath + filePath;

	std::ifstream ifs;

	ifs.open(fullpath);

	if (ifs.fail()) {
#ifdef _DEBUG
		std::string message = "Failed open data file file for read";
		MessageBoxA(nullptr, message.c_str(), "LevelData", 0);
#endif // _DEBUG
		assert(0);
	}

	// JSON文字列から解凍したデータ
	nlohmann::json deserialized;

	// 解凍
	ifs >> deserialized;

	// 正しいレベルデータファイルかチェック
	assert(deserialized.is_object());
	assert(deserialized.contains("name"));
	assert(deserialized["name"].is_string());

	// "name"を文字列として取得
	std::string name = deserialized["name"].get<std::string>();
	// 正しいレベルファイルかチェック
	assert(name.compare("scene") == 0);

	// レベルデータ格納用インスタンスを生成
	

	ifs.close();

}