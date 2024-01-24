#pragma once

#include <wrl.h>
#include <d3d12.h>
#include <string>
#include "Externals/DirectXTex/DirectXTex.h"
#include <vector>
#include <memory>
#include "DescriptorHeapManager/DescriptorHeap/DescriptorHeap.h"
#include "Texture.h"

// namespace省略
template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

class TextureManager {
public:

	static TextureManager* GetInstance();

	void Initialize();

	void Finalize();

public:

	const Texture* LoadTexture(const std::string& filePath);

private:
	TextureManager() = default;
	~TextureManager() = default;
	TextureManager(const TextureManager&) = delete;
	TextureManager& operator=(const TextureManager&) = delete;

	DirectX::ScratchImage Load(const std::string& filePath);

	ID3D12Resource* CreateTextureResource(const DirectX::TexMetadata& metadata);

	ID3D12Resource* UploadTextureData(ID3D12Resource* texture, const DirectX::ScratchImage& mipImages);

private:

	ID3D12Device* device_ = nullptr;

	std::vector<std::unique_ptr<Texture>> textures_;

};