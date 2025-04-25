#pragma once
#include "Descriptor/DescriptorHandles/DescriptorHandles.h"

namespace Kyoko {
	namespace Descriptor {
		/// <summary>
		///ディスクリプター
		/// </summary>
		class Descriptor
		{
		public:
			DescriptorHandles handles; // ハンドル
			bool isUse; // 使用しているか
		};
	}
}