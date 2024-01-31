#pragma once

class Kyoko {
public:

	static void Initialize(const char* windowName = "LE2A_21_ミズカミ_コタロウ", int width = 1280, int height = 720);

	static const bool ProcessMessage();

	static void FirstUpdateInLoop();

	static void PreDraw();

	static void PostDraw();

	static void Finalize();
};