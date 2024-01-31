#pragma once

#ifdef _DEBUG
#include "Externals/imgui/imgui.h"
#endif // _DEBUG

class ImGuiManager
{
public:

	static void Initialize();

	static void Finalize();

	static void Begin();

	static void End();

	static void Draw();

};

