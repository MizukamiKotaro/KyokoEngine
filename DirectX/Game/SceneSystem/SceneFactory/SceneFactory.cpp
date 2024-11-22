#include "SceneSystem/SceneFactory/SceneFactory.h"

#include "SceneSystem/TitleScene/TitleScene.h"
#include "SceneSystem/StageScene/StageScene.h"
#include "SceneSystem/SelectScene/SelectScene.h"
#include "SceneSystem/ClearScene/ClearScene.h"
#include "SceneSystem/StageEditorScene/StageEditorScene.h"

SceneBase* SceneFactory::CreateScene(int32_t sceneNo)
{
	SceneBase* newScene = nullptr;

	switch (sceneNo)
	{
	case SCENE::TITLE:
		newScene = new TitleScene();
		break;
	case SCENE::SELECT:
		newScene = new SelectScene();
		break;
	case SCENE::STAGE:
		newScene = new StageScene();
		break;
	case SCENE::STAGE_EDITOR:
		newScene = new StageEditorScene();
		break;
	case SCENE::CLEAR:
		newScene = new ClearScene();
		break;
	default:
		break;
	}
	
	return newScene;
}