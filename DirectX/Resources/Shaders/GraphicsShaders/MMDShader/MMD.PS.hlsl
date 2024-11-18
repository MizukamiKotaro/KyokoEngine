#include "MMD.hlsli"

Texture2D<float32_t4> gTexture[1024] : register(t0);
SamplerState gSampler : register(s0);

struct PixelShaderOutput {
	float32_t4 color : SV_TARGET0;
};

struct Camera {
	float32_t3 worldPosition;
};
ConstantBuffer<Camera> gCamera : register(b0);

PixelShaderOutput main(VertexShaderOutput input) {
	PixelShaderOutput output;
	float32_t4 textureColor = {1.0f,1.0f,1.0f,1.0f};
	if(input.textureNum != -1){
		textureColor = gTexture[input.textureNum].Sample(gSampler, input.texcoord);
	}

	float32_t3 light = normalize(float32_t3(1,-1,1));
	float32_t3 lightColor = float32_t3(1,1,1);

	float32_t NdotL = dot(normalize(input.normal), -light);
	float32_t cos = pow(NdotL * 0.5f + 0.5f, 2.0f);

	float32_t4 toon = {1,1,1,1};
	if(input.toonTextureNum != -1){
		toon = gTexture[input.toonTextureNum].Sample(gSampler, float32_t2(0,1.0f - cos));
	}

	float32_t3 toEye = normalize(gCamera.worldPosition - input.worldPosition);
	float32_t3 halfVector = normalize(-light + toEye);
	float32_t NdotH = dot(normalize(input.normal), halfVector);
	float32_t specularPow = pow(saturate(NdotH), input.shininess);

	float32_t3 diffuse = saturate(input.diffuseColor.rgb * textureColor.rgb * lightColor * toon.rgb);

	float32_t3 specular = input.specularColor * specularPow;

	output.color.rgb = max(diffuse + specular, textureColor.rgb * input.ambientColor);
	output.color.a = 1.0f;
	
	
	return output;
}