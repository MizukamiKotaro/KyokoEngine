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
	kCombo, // コンボ
};

enum class ItemStruct {
	kInt,
	kFloat,
	kVector2, 
	kVector3,
	kVector4,
	kBool,
	kString,
	kColor,
	kCombo,
	kComboID,
};