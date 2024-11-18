#include "MMD.hlsli"

struct TransformationMatrix {
	float32_t4x4 WVP;
	float32_t4x4 World;
	float32_t4x4 WorldInverse;
};
ConstantBuffer<TransformationMatrix>gTransformationMatrix : register(b0);

struct VertexShaderInput {
	float32_t4 vertexPos : POSITION0;
	float32_t2 texcoord : TEXCOORD0;
	float32_t3 normal : NORMAL0;
	float32_t4 diffuseColor : COLOR0;
	int32_t textureNum : TEXINDEX0;

	float32_t3 ambientColor : SCOLOR0;
	float32_t3 specularColor : SCOLOR1;
	float shininess : SHININESS0;
	int32_t sphereTextureNum : TEXINDEX1;
	int32_t toonTextureNum : TEXINDEX2;
};

VertexShaderOutput main(VertexShaderInput input) {
	VertexShaderOutput output;
	output.vertexPos = mul(input.vertexPos, gTransformationMatrix.WVP);
	output.texcoord = input.texcoord;
	output.normal = normalize(mul(input.normal, (float32_t3x3)gTransformationMatrix.WorldInverse));
	output.worldPosition = mul(input.vertexPos, gTransformationMatrix.World).xyz;
	output.diffuseColor = input.diffuseColor;
	output.textureNum = input.textureNum;
	output.ambientColor = input.ambientColor;
	output.specularColor = input.specularColor;
	output.shininess = input.shininess;
	output.sphereTextureNum = input.sphereTextureNum;
	output.toonTextureNum = input.toonTextureNum;
	return output;
}