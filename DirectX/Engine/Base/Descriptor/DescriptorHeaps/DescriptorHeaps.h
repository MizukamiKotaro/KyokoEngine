#pragma once
#include "Descriptor/DescriptorHeap/DescriptorHeap.h"

namespace Kyoko {
	namespace Descriptor {
		/// <summary>
		/// SRV用ディスクリプターヒープ
		/// </summary>
		class SRVDescriptorHeap : public DescriptorHeap
		{
		public:
			SRVDescriptorHeap();
			/// <summary>
			/// テクスチャ用ディスクリプターの最大数の取得
			/// </summary>
			/// <returns>テクスチャ用ディスクリプターの最大数</returns>
			static UINT GetTextureMaxNum();
		};
		/// <summary>
		/// RTV用ディスクリプターヒープ
		/// </summary>
		class RTVDescriptorHeap : public DescriptorHeap
		{
		public:
			RTVDescriptorHeap();
		};
		/// <summary>
		/// DSV用ディスクリプターヒープ
		/// </summary>
		class DSVDescriptorHeap : public DescriptorHeap
		{
		public:
			DSVDescriptorHeap();
		};
	}
}
