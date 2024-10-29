#pragma once

namespace Kyoko {
	namespace Engine {
		// 初期化
		void Initialize(const char* windowName = "LE2A_21_ミズカミ_コタロウ", int width = 1280, int height = 720);
		// ウィンドウメッセージの取得
		const bool ProcessMessage();
		// ループ内の最初の更新処理
		void FirstUpdateInLoop();
		// 描画前処理
		void PreDraw();
		// 描画後処理
		void PostDraw();
		// 終了処理
		void Finalize();
	}
}