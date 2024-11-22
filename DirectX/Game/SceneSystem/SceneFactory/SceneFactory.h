#pragma once
#include "SceneSystem/ISceneFactory/ISceneFactory.h"

/// <summary>
/// シーン作成クラス
/// </summary>
class SceneFactory : public ISceneFactory
{
public:
	/// <summary>
	/// シーンの作成
	/// </summary>
	/// <param name="sceneNo">シーンナンバー</param>
	/// <returns>シーン</returns>
	SceneBase* CreateScene(int32_t sceneNo) override;
};
