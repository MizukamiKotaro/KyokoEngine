#pragma once

// 響子
namespace Kyoko {
	// エンジン
	namespace Engine {
		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="windowName">タイトルバー名</param>
		/// <param name="width">横幅</param>
		/// <param name="height">縦幅</param>
		void Initialize(const char* windowName = "LE3A_17_ミズカミ_コタロウ", int width = 1280, int height = 720);
		/// <summary>
		/// ウィンドウが閉じたかの取得
		/// </summary>
		/// <returns>ウィンドウが閉じたか</returns>
		bool ProcessMessage();

		/// <summary>
		/// ダブルバッファの実装で最初に確定させる処理
		/// </summary>
		void CloseCommandlist();

		/// <summary>
		/// ループ内の最初の更新処理
		/// </summary>
		void FirstUpdateInLoop();
		/// <summary>
		/// 描画前処理
		/// </summary>
		void PreDraw();
		/// <summary>
		/// 描画後処理
		/// </summary>
		void PostDraw();
		/// <summary>
		/// 終了処理
		/// </summary>
		void Finalize();
	}
}