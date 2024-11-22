#pragma once
#include <string>

/// <summary>
/// stringとwstringを変換させるクラス
/// </summary>
class StringConverter
{
public:
	/// <summary>
	/// マルチバイト文字列(string)からワイド文字列(wstring)に変換
	/// </summary>
	/// <param name="mString">マルチバイト文字列(string)</param>
	/// <returns> ワイド文字列(wstring)</returns>
	static std::wstring ConvertString(const std::string& mString);

	/// <summary>
	/// ワイド文字列(wstring)からマルチバイト文字列(string)に変換
	/// </summary>
	/// <param name="wString">ワイド文字列(wstring)</param>
	/// <returns> マルチバイト文字列(string)</returns>
	static std::string ConvertString(const std::wstring& wString);
};