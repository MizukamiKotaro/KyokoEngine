#include "DebugCamera.h"
#include "ImGuiManager/ImGuiManager.h"
#include "Input.h"

DebugCamera::DebugCamera()
{
	input_ = Input::GetInstance();
	beforeDebugTransform_ = {};
	isDebug_ = false;
	is2D_ = false;
	isPreDebug_ = isDebug_;

	isTranslate_ = false;
	isRotate_ = false;
	isRotateTranslate_ = false;

	subRotate_ = {};
	subTranslate_ = {};
	mousePos_ = {};
}

void DebugCamera::Update(EulerTransform& transform)
{
	transform;
#ifdef _DEBUG
	isPreDebug_ = isDebug_;
	if (!ImGui::Begin("Camera", nullptr, ImGuiWindowFlags_MenuBar)) {
		ImGui::End();
	}
	else {
		if (ImGui::BeginMenuBar()) {
			if (ImGui::BeginMenu("デバッグカメラ")) {
				ImGui::Checkbox("デバッグモードか", &isDebug_);
				ImGui::Text("LShift : デバッグモード切替");
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
		ImGui::End();
	}

	if (input_->PressedKey(DIK_LSHIFT)) {
		if (isDebug_) {
			isDebug_ = false;
			transform = beforeDebugTransform_;
		}
		else {
			isDebug_ = true;
			beforeDebugTransform_ = transform;
			isTranslate_ = false;
			isRotate_ = false;
			isRotateTranslate_ = false;
		}
	}
	else if (!isPreDebug_ && isDebug_) {
		if (isDebug_) {
			beforeDebugTransform_ = transform;
			isTranslate_ = false;
			isRotate_ = false;
			isRotateTranslate_ = false;
		}
		else {
			transform = beforeDebugTransform_;
		}
	}
	DebugUpdate(transform);
#endif // _DEBUG
}

void DebugCamera::StopDebug()
{
	isDebug_ = false;
	isMouseMove_ = true;
}

void DebugCamera::DebugUpdate(EulerTransform& transform)
{
	transform;
#ifdef _DEBUG
	if (isDebug_) {
		if (!ImGui::Begin("Camera", nullptr, ImGuiWindowFlags_MenuBar)) {
			ImGui::End();
		}
		else {
			if (ImGui::BeginMenuBar()) {
				if (ImGui::BeginMenu("デバッグカメラ")) {
					ImGui::Checkbox("2Dカメラのデバッグか(マウスでの調整)", &is2D_);
					ImGui::Checkbox("マウスでカメラを動かすか", &isMouseMove_);
					ImGui::DragFloat3("ポジション", &transform.translate_.x, 0.01f);
					ImGui::DragFloat3("角度", &transform.rotate_.x, 0.01f);
					ImGui::Text("マウス真ん中長押し : 上下左右移動");
					if (!is2D_) {
						ImGui::Text("マウスホイール : 前後移動");
						ImGui::Text("マウス左長押し : 回転移動");
						ImGui::Text("マウス右長押し : 回転");
					}
					ImGui::EndMenu();
				}
				ImGui::EndMenuBar();
			}
			ImGui::End();
		}

		if (input_->PressedKey(DIK_LCONTROL)) {
			isMouseMove_ = !isMouseMove_;
		}

		if (isMouseMove_) {
			if (is2D_) {
				if (input_->PressedMouse(Input::MouseButton::CENTER) && !isRotate_ && !isRotateTranslate_) {
					mousePos_ = input_->GetMousePosition();
					isTranslate_ = true;
					subTranslate_ = transform.translate_;
				}
				else if (input_->PressingMouse(Input::MouseButton::CENTER) && isTranslate_) {
					Vector2 vector = input_->GetMousePosition();

					Vector3 move = { -(vector.x - mousePos_.x) / 80,(vector.y - mousePos_.y) / 45,0.0f };
					move = Matrix4x4::Multiply(move, Matrix4x4::MakeRotateXYZMatrix(transform.rotate_));

					transform.translate_ = subTranslate_ + move;
				}
				else {
					isTranslate_ = false;
				}

				if (input_->GetWheel() && !isRotate_ && !isRotateTranslate_ && !isTranslate_) {
					float moveLength = float(input_->GetWheel()) / 120;
					Vector3 move = { 0.0f,0.0f,1.0f };
					move = Matrix4x4::Multiply(move, Matrix4x4::MakeRotateXYZMatrix(transform.rotate_));
					move *= moveLength;
					transform.translate_ += move;
				}
			}
			else {
				if (input_->PressedMouse(Input::MouseButton::LEFT) && !isTranslate_ && !isRotate_) {
					mousePos_ = input_->GetMousePosition();
					isRotateTranslate_ = true;
					subRotate_ = transform.rotate_;
					subTranslate_ = transform.translate_;
				}
				else if (input_->PressingMouse(Input::MouseButton::LEFT) && isRotateTranslate_) {

					Vector2 length = input_->GetMousePosition() - mousePos_;

					float pi = 3.141592f;

					transform.rotate_.y = subRotate_.y - length.x / 640 * pi;
					transform.rotate_.x = subRotate_.x + length.y / 360 * pi;

					transform.translate_ = Matrix4x4::Multiply(subTranslate_, Matrix4x4::MakeRotateXYZMatrix({ length.y / 360 * pi, -length.x / 640 * pi,0.0f }));

				}
				else {
					isRotateTranslate_ = false;
				}

				if (input_->PressedMouse(Input::MouseButton::RIGHT) && !isTranslate_ && !isRotateTranslate_) {
					mousePos_ = input_->GetMousePosition();
					isRotate_ = true;
					subRotate_ = transform.rotate_;
				}
				else if (input_->PressingMouse(Input::MouseButton::RIGHT) && isRotate_) {
					Vector2 length = input_->GetMousePosition() - mousePos_;
					float pi = 3.141592f;
					Vector2 windowSize = WindowsInfo::GetInstance()->GetWindowSize();
					transform.rotate_.y = subRotate_.y + length.x / (windowSize.x * 0.5f) * pi;
					transform.rotate_.x = subRotate_.x + length.y / (windowSize.y * 0.5f) * pi;
				}
				else {
					isRotate_ = false;
				}

				if (input_->PressedMouse(Input::MouseButton::CENTER) && !isRotate_ && !isRotateTranslate_) {
					mousePos_ = input_->GetMousePosition();
					isTranslate_ = true;
					subTranslate_ = transform.translate_;
				}
				else if (input_->PressingMouse(Input::MouseButton::CENTER) && isTranslate_) {
					Vector2 vector = input_->GetMousePosition();

					Vector3 move = { -(vector.x - mousePos_.x) / 80,(vector.y - mousePos_.y) / 45,0.0f };
					move = Matrix4x4::Multiply(move, Matrix4x4::MakeRotateXYZMatrix(transform.rotate_));

					transform.translate_ = subTranslate_ + move;
				}
				else {
					isTranslate_ = false;
				}

				if (input_->GetWheel() && !isRotate_ && !isRotateTranslate_ && !isTranslate_) {
					float moveLength = float(input_->GetWheel()) / 120;
					Vector3 move = { 0.0f,0.0f,1.0f };
					move = Matrix4x4::Multiply(move, Matrix4x4::MakeRotateXYZMatrix(transform.rotate_));
					move *= moveLength;
					transform.translate_ += move;
				}
			}
		}
	}
#endif // _DEBUG
}
