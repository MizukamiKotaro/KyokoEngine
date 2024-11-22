#pragma once
#include "DescriptorHeapManager/DescriptorHandles/DescriptorHandles.h"

/// <summary>
/// ディスクリプター
/// </summary>
class Descriptor
{
public:
	DescriptorHandles handles; // ハンドル
	bool isUse; // 使用しているか
};