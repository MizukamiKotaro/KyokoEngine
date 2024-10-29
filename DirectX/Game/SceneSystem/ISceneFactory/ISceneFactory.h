#pragma once
#include <stdint.h>
class IScene;

class ISceneFactory
{
public:
	virtual ~ISceneFactory() = default;

	virtual IScene* CreateScene(const int32_t& sceneNo) = 0;
};