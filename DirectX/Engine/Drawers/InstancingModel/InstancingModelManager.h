#pragma once
#include <list>
#include <unordered_map>
#include <memory>
#include "DescriptorHeapManager/DescriptorHeap/DescriptorHeap.h"
#include "Drawers/DrawerBase/DrawerBase.h"

#include "ModelData/ModelData.h"
#include "DescriptorHeapManager/DescriptorHandles/DescriptorHandles.h"
#include "ILight/ILight.h"

#include "InstancingModelData.h"
#include "InstancingModelList/InstancingModelList.h"

class Camera;

/// <summary>
/// インスタンシングモデルマネージャー
/// </summary>
class InstancingModelManager : public DrawerBase
{
public:
	/// <summary>
	/// インスタンスの取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static InstancingModelManager* GetInstance();
	/// <summary>
	/// 最初の初期化
	/// </summary>
	void FirstInitialize();
	/// <summary>
	/// データと同じものの描画
	/// </summary>
	/// <param name="camera">カメラ</param>
	/// <param name="modelData">モデルデータ</param>
	void Draw(const Camera& camera, const InstancingGroupData* modelData);
	/// <summary>
	/// タグと同じものの描画
	/// </summary>
	/// <param name="camera">カメラ</param>
	/// <param name="tag">タグ</param>
	void Draw(const Camera& camera, const std::string& tag = "normal");
	/// <summary>
	/// グループデータの作成とそのポインタの取得
	/// </summary>
	/// <param name="data">データ</param>
	/// <returns>グループデータ</returns>
	const InstancingGroupData* GetDrawData(const InstancingGroupData& data);
	/// <summary>
	/// 板ポリの場合のグループデータの作成とそのポインタの取得
	/// </summary>
	/// <param name="texturePath">テクスチャ</param>
	/// <param name="tag">タグ</param>
	/// <param name="blendMode">ブレンドモード</param>
	/// <returns>グループデータ</returns>
	const InstancingGroupData* GetDrawData(const std::string& texturePath, const std::string& tag = "normal", const BlendMode& blendMode = BlendMode::kBlendModeNormal);
	/// <summary>
	/// 要素の追加
	/// </summary>
	/// <param name="modelData">グループデータ</param>
	/// <param name="model">トランスフォームとかのデータ</param>
	void AddInstanceTransform(const InstancingGroupData* modelData, InstancingModelData&& model);
	/// <summary>
	/// クリア
	/// </summary>
	void Clear();
	/// <summary>
	/// ライトのセット
	/// </summary>
	/// <param name="modelData">グループデータ</param>
	/// <param name="light">ライト</param>
	void SetLight(const InstancingGroupData* modelData, const BaseLight* light);

private:
	InstancingModelManager() = default;
	~InstancingModelManager() = default;
	InstancingModelManager(const InstancingModelManager&) = delete;
	const InstancingModelManager& operator=(const InstancingModelManager&) = delete;

private:
	std::unordered_map<const InstancingGroupData*, std::unique_ptr<InstancingModelList>> instancingModelMap_; // インスタンスリストのマップ
	std::list<std::unique_ptr<InstancingGroupData>> drawDatas_; // グループデータのリスト
	const ModelData* plane_; // 板ポリ
};