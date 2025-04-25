#pragma once
#include <wrl.h>
#include <d3d12.h>

namespace Kyoko {
	namespace Descriptor {
		class DescriptorHandles;
	}
}

class Texture {
public:
	~Texture();
public:
	Microsoft::WRL::ComPtr<ID3D12Resource> resource_;
	Microsoft::WRL::ComPtr<ID3D12Resource> intermediateResource_;
	const Kyoko::Descriptor::DescriptorHandles* handles_;
};