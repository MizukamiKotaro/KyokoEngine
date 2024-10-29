#pragma once
#include "Vector3.h"
#include <stdint.h>
#include <vector>

struct CameraVMDFrame
{
    uint32_t frameNumber; // フレーム番号
    float distance; // 目標点とカメラの距離(目標点がカメラ前面でマイナス)
    Vector3 position;
    Vector3 rotation;
    uint8_t bezier[24]; // 補間パラメータ
    uint32_t fov; // 視野角(deg)
    uint8_t parth; // パースペクティブ, 0:ON, 1:OFF

    float time;
};

struct CameraVMDData
{
    float duration; // アニメーション全体の尺
    std::vector<CameraVMDFrame> frames;
};