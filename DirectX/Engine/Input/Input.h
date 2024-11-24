#pragma once

#define DIRECTINPUT_VERSION 0x0800 
#include <dinput.h>
#include <XInput.h>

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib, "xinput.lib")
#include <wrl.h>

#include <vector>
#include "Utils/Math/Vector2.h"
#include "WindowsInfo/WindowsInfo.h"

/// <summary>
/// 入力処理
/// </summary>
class Input
{
public:
	
	/// <summary>
	/// ゲームパッドのボタン
	/// </summary>
	enum class GamePadButton {
		A, // A
		B, // B
		X, // X
		Y, // Y
		UP, // 十字キー上
		DOWN, // 十字キー下
		LEFT, // 十字キー左
		RIGHT, // 十字キー右
		START, // 中央右
		BACK, // 中央左
		LEFT_THUMB, // 左スティック押し込み
		RIGHT_THUMB, // 右スティック押し込み 
		LEFT_SHOULDER, // LB
		RIGHT_SHOULDER, // RB
	};

	enum class MouseButton {
		LEFT, // 左
		RIGHT, // 右
		CENTER, // ホイール
	};

	// namespace省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

	/// <summary>
	/// インスタンスの取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static Input* GetInstance();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// キーボードが押された瞬間
	/// </summary>
	/// <param name="keyNumber">キー番号( DIK_0 等)</param>
	/// <returns>押されているか</returns>
	bool PressedKey(BYTE keyNumber) const;

	/// <summary>
	/// キーボードが押されている間
	/// </summary>
	/// <param name="keyNumber">キー番号( DIK_0 等)</param>
	/// <returns>押され続けているか</returns>
	bool PressingKey(BYTE keyNumber) const;

	/// <summary>
	/// キーボードを離した瞬間
	/// </summary>
	/// <param name="keyNumber">キー番号( DIK_0 等)</param>
	/// <returns>離したか</returns>
	bool ReleasedKey(BYTE keyNumber) const;


	/// <summary>
	/// ゲームパッドのLスティックの入力
	/// </summary>
	/// <returns>Vector2</returns>
	Vector2 GetGamePadLStick();

	/// <summary>
	/// ゲームパッドのRスティックの入力
	/// </summary>
	/// <returns>Vector2</returns>
	Vector2 GetGamePadRStick();

	/// <summary>
	/// ゲームパッドが押された瞬間
	/// </summary>
	/// <param name="button">ボタン( Input::GamePadButton::A 等)</param>
	/// <returns>押されているか</returns>
	bool PressedGamePadButton(GamePadButton button);

	/// <summary>
	/// ゲームパッドが押され続けているか
	/// </summary>
	/// <param name="button">ボタン( Input::GamePadButton::A 等)</param>
	/// <returns>押され続けているか</returns>
	bool PressingGamePadButton(GamePadButton button);

	/// <summary>
	/// ゲームパッドが離れてか
	/// </summary>
	/// <param name="button">ボタン( Input::GamePadButton::A 等)</param>
	/// <returns>離れたか</returns>
	bool ReleasedGamePadButton(GamePadButton button);

	/// <summary>
	/// マウスが押された瞬間
	/// </summary>
	/// <param name="button">ボタン( Input::MouseButton::LEFT 等)</param>
	/// <returns>押されているか</returns>
	bool PressedMouse(MouseButton button);

	/// <summary>
	/// マウスが押され続けているか
	/// </summary>
	/// <param name="button">ボタン( Input::MouseButton::LEFT 等)</param>
	/// <returns>押され続けているか</returns>
	bool PressingMouse(MouseButton button);

	/// <summary>
	/// マウスが離れたか
	/// </summary>
	/// <param name="button">ボタン( Input::MouseButton::LEFT 等)</param>
	/// <returns>離れたか</returns>
	bool ReleasedMouse(MouseButton button);

	/// <summary>
	/// マウスホイールのスクロール量を取得する
	/// </summary>
	/// <returns>ホイールのスクロール量</returns>
	int32_t GetWheel() const;

	/// <summary>
	/// マウスの動量を取得する
	/// </summary>
	/// <returns>マウスの移動量</returns>
	Vector2 GetMouseMove() const;

	/// <summary>
	/// マウスの座標を取得
	/// </summary>
	/// <returns>マウスの座標</returns>
	Vector2 GetMousePosition();

private:
	Input() = default;
	~Input() = default;
	Input(const Input&) = delete;
	const Input& operator=(const Input&) = delete;

	/// <summary>
	/// 現在のゲームパッドのボタンの状態の取得
	/// </summary>
	/// <param name="button">ボタン</param>
	/// <returns>押されているか</returns>
	bool GetGamePadButton(GamePadButton button) const;
	/// <summary>
	/// 以前のゲームパッドのボタンの状態の取得
	/// </summary>
	/// <param name="button">ボタン</param>
	/// <returns>押されているか</returns>
	bool GetPreGamePadButton(GamePadButton button) const;
	/// <summary>
	/// 現在のマウスのボタンの状態の取得
	/// </summary>
	/// <param name="button">ボタン</param>
	/// <returns>押されているか</returns>
	bool GetMouseButton(MouseButton button) const;
	/// <summary>
	/// 以前のマウスのボタンの状態の取得
	/// </summary>
	/// <param name="button">ボタン</param>
	/// <returns>押されているか</returns>
	bool GetPreMouseButton(MouseButton button) const;

private:
	WindowsInfo* windowInfo_ = nullptr; // ウィンドウ情報

	ComPtr<IDirectInput8> dInput_; // IDirectInput8
	ComPtr<IDirectInputDevice8> devKeyboard_; // キーボード
	ComPtr<IDirectInputDevice8> devMouse_; // マウス

	XINPUT_STATE xInputState_ = {}; // 現在の状態
	XINPUT_STATE preXInputState_ = {}; // 以前の状態


	BYTE key_[256] = {}; // 現在のキー
	BYTE keyPre_[256] = {}; // 以前のキー

	DIMOUSESTATE2 mouse_; // 現在のマウス
	DIMOUSESTATE2 mousePre_; // 以前のマウス
	POINT mousePos_; // マウスの座標

};

