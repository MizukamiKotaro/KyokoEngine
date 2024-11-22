#pragma once

#include <Windows.h>
#include <cstdint>
#include <string>
#include "Vector2.h"

// ウィンドウクラス
class WindowsInfo
{
public: // 静的メンバ関数
	/// <summary>
	/// インスタンスの取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static WindowsInfo* GetInstance();

	/// <summary>
	/// ウィンドウが起動しているかどうかの取得
	/// </summary>
	/// <param name="hwnd">ウィンドウハンドル</param>
	/// <param name="msg">ハンドル</param>
	/// <param name="wparam">ハンドル</param>
	/// <param name="lparam">ハンドル</param>
	/// <returns>ウィンドウが起動しているかどうか</returns>
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

public: // メンバ関数
	/// <summary>
	/// ウィンドウの作成
	/// </summary>
	/// <param name="windowName">ウィンドウの名前</param>
	/// <param name="width">横幅</param>
	/// <param name="height">縦幅</param>
	void CreateGameWindow(const std::string& windowName = "LE3A_17_ミズカミ_コタロウ", int width = 1280, int height = 720);

	/// <summary>
	/// ウィンドウが閉じたかどうかの取得
	/// </summary>
	/// <returns>ウィンドウが閉じたかどうか</returns>
	bool ProcessMessage();

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();

	/// <summary>
	/// ウィンドウハンドルの取得
	/// </summary>
	/// <returns>ウィンドウハンドル</returns>
	HWND GetHwnd() const { return hwnd_; }

	/// <summary>
	/// hInstanceの取得
	/// </summary>
	/// <returns>hInstance</returns>
	HINSTANCE GetHInstance() const { return wndClass_.hInstance; }

	/// <summary>
	/// ウィンドウサイズの取得
	/// </summary>
	/// <returns>ウィンドウサイズ</returns>
	Vector2 GetWindowSize() const { return windowSize_; }

private: // メンバ関数
	WindowsInfo() = default;
	~WindowsInfo() = default;
	WindowsInfo(const WindowsInfo&) = delete;
	const WindowsInfo& operator=(const WindowsInfo&) = delete;

private: // メンバ変数
	// Window関連
	HWND hwnd_ = nullptr;   // ウィンドウハンドル
	WNDCLASS wndClass_{}; // ウィンドウクラス
	Vector2 windowSize_; // ウィンドウサイズ
};