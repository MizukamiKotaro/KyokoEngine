#include "../Object3dShader/Object3d.hlsli"

struct TransformationMatrix {
	float32_t4x4 WVP;
	float32_t4x4 World;
	float32_t4x4 WorldInverse;
};
ConstantBuffer<TransformationMatrix>gTransformationMatrix : register(b0);

struct Well{
	float32_t4x4 skeletonSpaceMatrix;
	float32_t4x4 skeletonSpaceInverseTransposeMatrix;
};
StructuredBuffer<Well> gMatrixPalette : register(t0);

struct VertexShaderInput {
	float32_t4 vertexPos : POSITION0;
	float32_t2 texcoord : TEXCOORD0;
	float32_t3 normal : NORMAL0;
	float32_t4 weight : WEIGHT0;
	int32_t4 index : INDEX0; 
};

struct Skinned{
	float32_t4 position;
	float32_t3 normal;
};

Skinned Skinning(VertexShaderInput input){
	Skinned skinned;

	skinned.position = mul(input.vertexPos, gMatrixPalette[input.index.x].skeletonSpaceMatrix) * input.weight.x;
	skinned.position += mul(input.vertexPos, gMatrixPalette[input.index.y].skeletonSpaceMatrix) * input.weight.y;
	skinned.position += mul(input.vertexPos, gMatrixPalette[input.index.z].skeletonSpaceMatrix) * input.weight.z;
	skinned.position += mul(input.vertexPos, gMatrixPalette[input.index.w].skeletonSpaceMatrix) * input.weight.w;
	skinned.position.w = 1.0f;

	skinned.normal = mul(input.normal,(float32_t3x3)gMatrixPalette[input.index.x].skeletonSpaceInverseTransposeMatrix) * input.weight.x;
	skinned.normal += mul(input.normal,(float32_t3x3)gMatrixPalette[input.index.y].skeletonSpaceInverseTransposeMatrix) * input.weight.y;
	skinned.normal += mul(input.normal,(float32_t3x3)gMatrixPalette[input.index.z].skeletonSpaceInverseTransposeMatrix) * input.weight.z;
	skinned.normal += mul(input.normal,(float32_t3x3)gMatrixPalette[input.index.w].skeletonSpaceInverseTransposeMatrix) * input.weight.w;
	skinned.normal = normalize(skinned.normal);

	return skinned;
}

VertexShaderOutput main(VertexShaderInput input) {
	VertexShaderOutput output;
	Skinned skinned = Skinning(input);

	output.vertexPos = mul(skinned.position, gTransformationMatrix.WVP);
	output.texcoord = input.texcoord;
	output.normal = normalize(mul(skinned.normal, (float32_t3x3)gTransformationMatrix.WorldInverse));
	output.worldPosition = mul(skinned.position, gTransformationMatrix.World).xyz;
	return output;
}