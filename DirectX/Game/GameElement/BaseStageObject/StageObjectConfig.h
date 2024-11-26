#pragma once
/// <summary>
/// ステージオブジェクトのタイプ
/// </summary>
enum class StageObjectType {
	SPOTLIGHT, // スポットライト
	TWIN_SPOTLIGHT, // 左右対称のスポットライト
	SCREEN, // スクリーン
	MULTIPLE_SCREEN, // マルチスクリーン
	IDOL, // アイドル
	FLOOR, // 床
	DOME, // ドーム
	FIRE_PARTICLE, // 炎のパーティクル
	OBJECT, // オブジェクト
	PEN_LIGHT, // ペンライト
};