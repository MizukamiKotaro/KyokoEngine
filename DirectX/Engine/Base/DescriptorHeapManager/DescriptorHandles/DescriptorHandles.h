#pragma once
#include <d3d12.h>

/// <summary>
/// ディスクリプターのCPUとGPUのハンドル
/// </summary>
class DescriptorHandles
{
public:
	D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle; // cpuハンドル
	D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle; // gpuハンドル
	size_t no; // ナンバー
};