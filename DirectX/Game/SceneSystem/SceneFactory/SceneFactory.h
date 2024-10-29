#pragma once
#include "SceneSystem/ISceneFactory/ISceneFactory.h"

class SceneFactory : public ISceneFactory
{
public:
	IScene* CreateScene(const int32_t& sceneNo) override;
};
