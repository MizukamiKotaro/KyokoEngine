#include "Transformation.h"
#include "DirectXBase/DirectXBase.h"

Transformation::Transformation()
{
	transformationResource.CreateResource(sizeof(TransformationMatrix));
	transformationData = nullptr;

	transformationResource.Map(reinterpret_cast<void**>(&transformationData));
	*transformationData = { Matrix4x4::MakeIdentity4x4() ,Matrix4x4::MakeIdentity4x4(), Matrix4x4::Inverse(Matrix4x4::MakeIdentity4x4()) };
}
