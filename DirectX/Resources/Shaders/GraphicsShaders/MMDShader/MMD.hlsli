struct VertexShaderOutput {
	float32_t4 vertexPos : SV_POSITION;
	float32_t2 texcoord : TEXCOORD0;
	float32_t3 normal : NORMAL0;
	float32_t3 worldPosition : WORLD_POSITION0;
	float32_t4 diffuseColor : COLOR0;
	int32_t textureNum : TEXINDEX0;

	float32_t3 ambientColor : SCOLOR0;
	float32_t3 specularColor : SCOLOR1;
	float shininess : SHININESS0;
	int32_t sphereTextureNum : TEXINDEX1;
	int32_t toonTextureNum : TEXINDEX2;
};