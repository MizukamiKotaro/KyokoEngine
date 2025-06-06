#include "Transformation.h"
#include "DirectXBase/DirectXBase.h"
#include "ResourceManager/ResourceManager.h"
Transformation::Transformation()
{
	transformationResource = DirectXBase::CreateBufferResource(sizeof(TransformationMatrix));
	transformationData = nullptr;
	transformationResource->Map(0, nullptr, reinterpret_cast<void**>(&transformationData));
	*transformationData = { Matrix4x4::MakeIdentity4x4() ,Matrix4x4::MakeIdentity4x4(), Matrix4x4::Inverse(Matrix4x4::MakeIdentity4x4()) };
}

Transformation::~Transformation()
{
	ResourceManager::GetInstance()->AddReleaseResource(std::move(transformationResource));
}