#pragma once

#include "MeshData3D.h"
#include "MaterialData3D.h"
#include "NodeData3D.h"
#include "AnimationData3D.h"
#include "BoneData3D.h"
#include "Texture.h"

struct ModelData
{
	MeshData mesh;
	MaterialData material;
	NodeData rootNode;
	BoneData boneData;
	AnimationData animationData;
	std::string fileName;
	const Texture* texture;
};