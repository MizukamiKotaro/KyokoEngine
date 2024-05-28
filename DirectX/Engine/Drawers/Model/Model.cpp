#include "Model.h"
#include "Drawers/DrawManager/DrawManager.h"

Model::Model(const std::string& fileName)
{
	CreateModel(fileName);
}

Model::Model(const ModelData* modelData)
{
	CreateModel(modelData);
}

void Model::Draw(const Camera& camera, BlendMode blendMode) const
{
	drawManager_->Draw(*this, camera, blendMode);
}