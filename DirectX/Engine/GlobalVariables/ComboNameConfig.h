#pragma once
/// <summary>
/// コンボのタイプ
/// </summary>
enum class ComboNameType {
	kTexture, // テクスチャ
	kOBJ, // オブジェクト
	kRigidAnimationModel, // リジッドアニメーションモデル
	kSkinningModel, // スキニングモデル
	kAudio, // オーディオ
	kEase, // イージング
	kCameraAnimationVMD, // カメラアニメーション
	kPMD, // pmd
};