#pragma once
#include "MeshDataPMD.h"
#include "ModelData/NodeData3D.h"
#include "ModelData/AnimationData3D.h"
#include "ModelData/BoneData3D.h"
#include "ModelData/WeightData.h"

class ModelDataPMD
{
public:
	MeshDataPMD mesh;
	NodeData rootNode;
	BoneData boneData;
	AnimationData animationData;
	std::string fileName;
	std::map<std::string, JointWeightData> skinClusterData;
};