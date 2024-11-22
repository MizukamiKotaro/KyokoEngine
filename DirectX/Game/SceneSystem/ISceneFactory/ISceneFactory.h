#pragma once
#include <stdint.h>
class SceneBase;

/// <summary>
/// シーン作成の基底クラス
/// </summary>
class ISceneFactory
{
public:
	virtual ~ISceneFactory() = default;
	/// <summary>
	/// シーンの作成
	/// </summary>
	/// <param name="sceneNo">シーンナンバー</param>
	/// <returns>シーン</returns>
	virtual SceneBase* CreateScene(int32_t sceneNo) = 0;
};