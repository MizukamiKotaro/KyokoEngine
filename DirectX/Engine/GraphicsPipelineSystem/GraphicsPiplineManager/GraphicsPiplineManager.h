#pragma once
#include <memory>
#include <unordered_map>

class GraphicsPipeline;
enum class BlendMode;
enum class PipelineType;
class IGraphicsPipelineFactory;

class GraphicsPipelineManager
{
public:
	/// <summary>
	/// インスタンスの取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static GraphicsPipelineManager* GetInstance();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 描画前処理
	/// </summary>
	void PreDraw();

	/// <summary>
	/// 描画前処理
	/// </summary>
	/// <param name="type">パイプラインタイプ</param>
	void PreDraw(PipelineType type);
	/// <summary>
	/// ブレンドモードのセット
	/// </summary>
	/// <param name="type">パイプラインタイプ</param>
	/// <param name="blendMode">ブレンドモード</param>
	void SetBlendMode(PipelineType type, BlendMode blendMode);

private:
	GraphicsPipelineManager() = default;
	~GraphicsPipelineManager() = default;
	GraphicsPipelineManager(const GraphicsPipelineManager&) = delete;
	GraphicsPipelineManager& operator=(const GraphicsPipelineManager&) = delete;

private:
	std::unordered_map<PipelineType, std::unique_ptr<GraphicsPipeline>> pipelineMap_;
	PipelineType currentPiplineType_;
	std::unique_ptr<IGraphicsPipelineFactory> pipelineFactory_;
};