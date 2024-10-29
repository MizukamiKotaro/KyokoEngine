#pragma once

#include <Windows.h>
#include <cstdint>
#include <string>
#include "Vector2.h"

// ウィンドウクラス
class WindowsInfo
{
public: // 静的メンバ関数
	// インスタンスの取得
	static WindowsInfo* GetInstance();

	//ウィンドウプロシャープ
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

public: // メンバ関数
	// ウィンドウの作成
	void CreateGameWindow(const std::string& windowName = "LE2A_21_ミズカミ_コタロウ", int width = 1280, int height = 720);

	// メッセージ処理
	bool ProcessMessage();

	// 終了処理
	void Finalize();

	// ウィンドウハンドルの取得
	HWND GetHwnd() const { return hwnd_; }

	// hInstanceの取得
	HINSTANCE GetHInstance() const { return wndClass_.hInstance; }

	// ウィンドウサイズの取得
	const Vector2 GetWindowSize() const { return windowSize_; }

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