#include "CameraVMDAnimation.h"
#include "CameraVMDDataManager.h"
#include "calc.h"
#include "Quaternion.h"

CameraVMDAnimation::CameraVMDAnimation(const std::string& path)
{
    LoadVMDAnimationData(path);
}

void CameraVMDAnimation::LoadVMDAnimationData(const std::string& path)
{
    data_ = CameraVMDDataManager::GetInstance()->LoadVMDData(path);
    state_ = data_->frames[0];
    num_ = 0;
}

void CameraVMDAnimation::Initialize()
{
}

void CameraVMDAnimation::Update(const float& deltaTime)
{
	state_.time += deltaTime;
	if (deltaTime < 0) {
		if (state_.time < 0) {
			state_.time = data_->duration + state_.time;
		}
        num_ = 0;
	}
	else {
        if (state_.time >= data_->duration) {
            num_ = 0;
        }
		state_.time = std::fmod(state_.time, data_->duration);
	}
    state_.time += deltaTime;

    std::vector<uint8_t>  bezier;
    bezier.resize(4);

    // カメラキーフレームを検索
    for (size_t i = num_; i < data_->frames.size() - 1; ++i) {
        if (state_.time >= data_->frames[i].time && state_.time < data_->frames[i + 1].time) {
            // 線形補間を使用して位置と回転を計算
            float t = (state_.time - data_->frames[i].time) / (data_->frames[i + 1].time - data_->frames[i].time);

            // 位置座標x
            SetBezier(bezier, 0, i);
            float newT = Interpolation(bezier, t);
            state_.position.x = Calc::Lerp(data_->frames[i].position.x, data_->frames[i + 1].position.x, newT);

            // 位置座標y
            SetBezier(bezier, 4, i);
            newT = Interpolation(bezier, t);
            state_.position.y = Calc::Lerp(data_->frames[i].position.y, data_->frames[i + 1].position.y, newT);

            // 位置座標z
            SetBezier(bezier, 8, i);
            newT = Interpolation(bezier, t);
            state_.position.z = Calc::Lerp(data_->frames[i].position.z, data_->frames[i + 1].position.z, newT);

            // 回転
            Quaternion q;
            if (data_->frames[i + 1].frameNumber - data_->frames[i].frameNumber <= 1 || data_->frames[i].rotation == data_->frames[i + 1].rotation) {
                state_.rotation = data_->frames[i].rotation;
                q = Quaternion::EulerToQuaternion(data_->frames[i + 1].rotation);
            }
            else {
                SetBezier(bezier, 12, i);
                newT = Interpolation(bezier, t);
                q = Quaternion::Slerp(Quaternion::EulerToQuaternion(data_->frames[i].rotation), Quaternion::EulerToQuaternion(data_->frames[i + 1].rotation), t);
                state_.rotation = Quaternion::QuaternionToEuler(q);
            }

            // 距離
            SetBezier(bezier, 16, i);
            newT = Interpolation(bezier, t);
            state_.distance = Calc::Lerp(data_->frames[i].distance, data_->frames[i + 1].distance, newT);

            Vector3 direction = { 0.0f,0.0f,-1.0f };
            direction = Matrix4x4::RotateVector(direction, q);
            state_.position = state_.position - direction * state_.distance;

            num_ = i;
            break;
        }
    }
}

const CameraVMDFrame& CameraVMDAnimation::GetState() const
{
	return state_;
}

void CameraVMDAnimation::SetTime(const float& time)
{
    num_ = 0;
    state_.time = time;
}

float CameraVMDAnimation::Interpolation(const std::vector<uint8_t>& bezier, const float& t)
{
    float p1x = float(bezier[0]) / 127.0f; // x1
    float p1y = float(bezier[1]) / 127.0f; // y1
    float p2x = float(bezier[2]) / 127.0f; // x2
    float p2y = float(bezier[3]) / 127.0f; // y2

    // x軸ベジェ曲線を逆探索でtに対応するxを求める (単純な二分探索)
    float x = 0.0f;
    float minX = 0.0f;
    float maxX = 1.0f;
    const int iterations = 10; // 二分探索の回数

    for (int i = 0; i < iterations; ++i) {
        float midX = (minX + maxX) / 2.0f;
        float midBezierX = Calc::Bezier(0.0f, p1x, p2x, 1.0f, midX);

        if (midBezierX < t) {
            minX = midX;
        }
        else {
            maxX = midX;
        }
    }

    x = (minX + maxX) / 2.0f;

    // そのxを使ってy軸の補間値を計算
    return Calc::Bezier(0.0f, p1y, p2y, 1.0f, x);
}

void CameraVMDAnimation::SetBezier(std::vector<uint8_t> bezier, const uint8_t& start, const size_t& num)
{
    for (uint8_t i = 0; i < 4; i++) {
        bezier[i] = data_->frames[num].bezier[i + start];
    }
}
