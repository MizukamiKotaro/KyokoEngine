#pragma once
#include <string>

/// <summary>
/// debug用のログを出力させるクラス
/// </summary>
class DebugLog
{
public:
	/// <summary>
	/// 出力ウィンドウに文字を出力
	/// </summary>
	/// <param name="message">メッセージ</param>
	static void Log(const std::string& message);
	/// <summary>
	/// 出力ウィンドウに文字を出力
	/// </summary>
	/// <param name="message">メッセージ</param>
	static void Log(const std::wstring& message);

};

