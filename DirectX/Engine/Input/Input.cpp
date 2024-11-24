#include "Input.h"
#include <cassert>

Input* Input::GetInstance() {
	static Input instance;
	return &instance;
}

void Input::Initialize() {

	windowInfo_ = WindowsInfo::GetInstance();

	HRESULT hr = DirectInput8Create(windowInfo_->GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dInput_, nullptr);
	assert(SUCCEEDED(hr));

	// キーボード入力の設定
	hr = dInput_->CreateDevice(GUID_SysKeyboard, &devKeyboard_, NULL);
	assert(SUCCEEDED(hr));
	hr = devKeyboard_->SetDataFormat(&c_dfDIKeyboard);
	assert(SUCCEEDED(hr));
	hr = devKeyboard_->SetCooperativeLevel(windowInfo_->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(hr));

	// マウス入力の設定
	hr = dInput_->CreateDevice(GUID_SysMouse, &devMouse_, NULL);
	assert(SUCCEEDED(hr));
	hr = devMouse_->SetDataFormat(&c_dfDIMouse);
	assert(SUCCEEDED(hr));
	hr = devMouse_->SetCooperativeLevel(windowInfo_->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(hr));

	devMouse_->GetDeviceState(sizeof(DIMOUSESTATE), &mouse_);
	mousePre_ = mouse_;
}

void Input::Update() {
	// キーボード
	devKeyboard_->Acquire();
	memcpy(keyPre_, key_, sizeof(key_));
	devKeyboard_->GetDeviceState(sizeof(key_), key_);
	// マウス
	devMouse_->Acquire();
	mousePre_ = mouse_;
	devMouse_->GetDeviceState(sizeof(DIMOUSESTATE), &mouse_);

	preXInputState_ = xInputState_;
	XInputGetState(0, &xInputState_);
}

bool Input::PressingKey(BYTE keyNumber) const {
	return key_[keyNumber] && keyPre_[keyNumber];
}

bool Input::ReleasedKey(BYTE keyNumber) const
{
	return !key_[keyNumber] && keyPre_[keyNumber];
}

bool Input::PressedKey(BYTE keyNumber) const 
{
	return !keyPre_[keyNumber] && key_[keyNumber];
}

Vector2 Input::GetGamePadLStick()
{
	if ((xInputState_.Gamepad.sThumbLX <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		xInputState_.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
		(xInputState_.Gamepad.sThumbLY <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			xInputState_.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		xInputState_.Gamepad.sThumbLX = 0;
		xInputState_.Gamepad.sThumbLY = 0;
	}
	return Vector2(static_cast<float>(xInputState_.Gamepad.sThumbLX) / SHRT_MAX, static_cast<float>(xInputState_.Gamepad.sThumbLY) / SHRT_MAX);
}

Vector2 Input::GetGamePadRStick()
{
	if ((xInputState_.Gamepad.sThumbRX <  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
		xInputState_.Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) &&
		(xInputState_.Gamepad.sThumbRY <  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
			xInputState_.Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE))
	{
		xInputState_.Gamepad.sThumbRX = 0;
		xInputState_.Gamepad.sThumbRY = 0;
	}
	return Vector2(static_cast<float>(xInputState_.Gamepad.sThumbRX) / SHRT_MAX, static_cast<float>(xInputState_.Gamepad.sThumbRY) / SHRT_MAX);
}

bool Input::PressedGamePadButton(GamePadButton button)
{
	return !GetPreGamePadButton(button) && GetGamePadButton(button);
}

bool Input::PressingGamePadButton(GamePadButton button)
{
	return GetPreGamePadButton(button) && GetGamePadButton(button);
}

bool Input::ReleasedGamePadButton(GamePadButton button)
{
	return GetPreGamePadButton(button) && !GetGamePadButton(button);
}

bool Input::PressedMouse(MouseButton button)
{
	return GetMouseButton(button) && !GetPreMouseButton(button);
}

bool Input::PressingMouse(MouseButton button)
{
	return GetMouseButton(button) && GetPreMouseButton(button);
}

bool Input::ReleasedMouse(MouseButton button)
{
	return !GetMouseButton(button) && GetPreMouseButton(button);
}

int32_t Input::GetWheel() const
{
	return static_cast<int32_t>(mouse_.lZ);
}

Vector2 Input::GetMouseMove() const
{
	return { (float)mouse_.lX,(float)mouse_.lY };
}

Vector2 Input::GetMousePosition()
{
	GetCursorPos(&mousePos_);
	ScreenToClient(WindowsInfo::GetInstance()->GetHwnd(), &mousePos_);
	return Vector2(static_cast<float>(mousePos_.x), static_cast<float>(mousePos_.y));
}

bool Input::GetGamePadButton(GamePadButton button) const
{
	switch (button)
	{
	case Input::GamePadButton::A:
		return xInputState_.Gamepad.wButtons & XINPUT_GAMEPAD_A;
	case Input::GamePadButton::B:
		return xInputState_.Gamepad.wButtons & XINPUT_GAMEPAD_B;
	case Input::GamePadButton::X:
		return xInputState_.Gamepad.wButtons & XINPUT_GAMEPAD_X;
	case Input::GamePadButton::Y:
		return xInputState_.Gamepad.wButtons & XINPUT_GAMEPAD_Y;
	case Input::GamePadButton::UP:
		return xInputState_.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP;
	case Input::GamePadButton::DOWN:
		return xInputState_.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN;
	case Input::GamePadButton::LEFT:
		return xInputState_.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT;
	case Input::GamePadButton::RIGHT:
		return xInputState_.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT;
	case Input::GamePadButton::START:
		return xInputState_.Gamepad.wButtons & XINPUT_GAMEPAD_START;
	case Input::GamePadButton::BACK:
		return xInputState_.Gamepad.wButtons & XINPUT_GAMEPAD_BACK;
	case Input::GamePadButton::LEFT_THUMB:
		return xInputState_.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB;
	case Input::GamePadButton::RIGHT_THUMB:
		return xInputState_.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB;
	case Input::GamePadButton::LEFT_SHOULDER:
		return xInputState_.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER;
	case Input::GamePadButton::RIGHT_SHOULDER:
		return xInputState_.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER;
	default:
		break;
	}
	return false;
}

bool Input::GetPreGamePadButton(GamePadButton button) const
{
	switch (button)
	{
	case Input::GamePadButton::A:
		return preXInputState_.Gamepad.wButtons & XINPUT_GAMEPAD_A;
	case Input::GamePadButton::B:
		return preXInputState_.Gamepad.wButtons & XINPUT_GAMEPAD_B;
	case Input::GamePadButton::X:
		return preXInputState_.Gamepad.wButtons & XINPUT_GAMEPAD_X;
	case Input::GamePadButton::Y:
		return preXInputState_.Gamepad.wButtons & XINPUT_GAMEPAD_Y;
	case Input::GamePadButton::UP:
		return preXInputState_.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP;
	case Input::GamePadButton::DOWN:
		return preXInputState_.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN;
	case Input::GamePadButton::LEFT:
		return preXInputState_.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT;
	case Input::GamePadButton::RIGHT:
		return preXInputState_.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT;
	case Input::GamePadButton::START:
		return preXInputState_.Gamepad.wButtons & XINPUT_GAMEPAD_START;
	case Input::GamePadButton::BACK:
		return preXInputState_.Gamepad.wButtons & XINPUT_GAMEPAD_BACK;
	case Input::GamePadButton::LEFT_THUMB:
		return preXInputState_.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB;
	case Input::GamePadButton::RIGHT_THUMB:
		return preXInputState_.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB;
	case Input::GamePadButton::LEFT_SHOULDER:
		return preXInputState_.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER;
	case Input::GamePadButton::RIGHT_SHOULDER:
		return preXInputState_.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER;
	default:
		break;
	}
	return false;
}

bool Input::GetMouseButton(MouseButton button) const
{
	uint32_t key = static_cast<uint32_t>(button);
	return mouse_.rgbButtons[key];
}

bool Input::GetPreMouseButton(MouseButton button) const
{
	uint32_t key = static_cast<uint32_t>(button);
	return mousePre_.rgbButtons[key];
}
