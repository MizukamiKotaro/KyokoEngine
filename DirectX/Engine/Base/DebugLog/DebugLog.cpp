#include "DebugLog.h"
#include <Windows.h>
#include "StringConverter/StringConverter.h"

void DebugLog::Log(const std::string& message) {
	OutputDebugStringA(message.c_str());
}

void DebugLog::Log(const std::wstring& message)
{
	OutputDebugStringA(StringConverter::ConvertString(message).c_str());
}
