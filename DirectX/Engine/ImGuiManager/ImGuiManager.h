#pragma once

#ifdef _DEBUG
#include "Externals/imgui/imgui.h"
#endif // _DEBUG

namespace Kyoko {
	namespace ImGuiManager {
		// 初期化
		void Initialize();
		// 終了処理
		void Finalize();
		// 毎フレームの更新前処理
		void Begin();
		// 描画前処理
		void End();
		// 描画処理
		void Draw();
	}
}