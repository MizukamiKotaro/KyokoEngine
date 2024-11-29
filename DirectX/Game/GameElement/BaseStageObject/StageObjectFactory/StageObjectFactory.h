#pragma once
#include <string>
enum class StageObjectType;
class BaseStageObject;
/// <summary>
/// ステージオブジェクトの作成
/// </summary>
class StageObjectFactory
{
public:
	/// <summary>
	/// ステージオブジェクトの作成
	/// </summary>
	/// <param name="type">タイプ</param>
	/// <param name="mainName">メインの名前</param>
	/// <param name="name">名前</param>
	/// <param name="no">ナンバー</param>
	/// <returns>ステージオブジェクト</returns>
	static BaseStageObject* CreateStageObject(const StageObjectType& type, const std::string& mainName, const std::string& name, const uint32_t& no);
};