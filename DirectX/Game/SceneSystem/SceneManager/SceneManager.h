#pragma once
#include <memory>
#include "SceneSystem/ISceneFactory/ISceneFactory.h"
#include "SceneSystem/SceneBase/SceneBase.h"
class Input;
class FrameInfo;

/// <summary>
/// シーンマネージャー
/// </summary>
class SceneManager
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	SceneManager();

	/// <summary>
	/// アプリループ
	/// </summary>
	int Run();
private:
	// シーン
	std::unique_ptr<SceneBase> scene_;

	int32_t currentSceneNo_; // 現在のシーン
	int32_t preSceneNo_; // 前のシーン

	std::unique_ptr<ISceneFactory> sceneFactory_; // シーンファクトリー

	Input* input_; // 入力
	FrameInfo* frameInfo_; // フレーム情報
};