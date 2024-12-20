#include "Bloom.h"
#include "ImGuiManager/ImGuiManager.h"
#include "WindowsInfo/WindowsInfo.h"

Bloom::Bloom()
{
	postEffect_ = std::make_unique<PostEffect>();
	postEffect_->Initialize();

	highLumi_ = std::make_unique<HighLumi>();
	highLumi_->Initialize();
	highLumi_->highLumiData_->min = 0.2f;
	highLumi_->highLumiData_->max = 1.0f;

	gaussianBlur_ = std::make_unique<GaussianBlur>();
	gaussianBlur_->Initialize();
	gaussianBlur_->SetSize(10);
	gaussianBlur_->SetSigma(14.0f);
}

Bloom::Bloom(const Vector2& size)
{
	postEffect_ = std::make_unique<PostEffect>(size);
	postEffect_->Initialize();

	highLumi_ = std::make_unique<HighLumi>(size);
	highLumi_->Initialize();
	highLumi_->highLumiData_->min = 0.2f;
	highLumi_->highLumiData_->max = 1.0f;

	gaussianBlur_ = std::make_unique<GaussianBlur>(true, false, size);
	gaussianBlur_->Initialize();
	gaussianBlur_->SetSize(10);
	gaussianBlur_->SetSigma(14.0f);
}

Bloom::~Bloom()
{
}

void Bloom::Initialize()
{
}

void Bloom::Update()
{
#ifdef _DEBUG
	int32_t size = gaussianBlur_->GetSize();
	float sigma = gaussianBlur_->GetSigma();
	ImGui::Begin("ブルーム");
	ImGui::DragInt("サイズ", &size, 1, 1, 100);
	ImGui::DragFloat("シグマ", &sigma, 0.1f, 0.5f, 100.0f);
	ImGui::DragFloat("明度最小", &highLumi_->highLumiData_->min, 0.01f, 0.0f, 1.0f);
	ImGui::DragFloat("明度最大", &highLumi_->highLumiData_->max, 0.01f, 0.0f, 1.0f);
	ImGui::End();
	gaussianBlur_->SetSize(size);
	gaussianBlur_->SetSigma(sigma);
#endif // _DEBUG
}

void Bloom::Draw()
{
	postEffect_->Draw();
	gaussianBlur_->Draw(BlendMode::kBlendModeAdd);
}

void Bloom::PreDrawScene()
{
	postEffect_->PreDrawScene();
}

void Bloom::PostDrawScene()
{
	postEffect_->PostDrawScene();
	// 高輝度抽出用
	highLumi_->PreDrawScene();
	postEffect_->Draw();
	highLumi_->PostDrawScene();
	// ガウシアンブラー用
	gaussianBlur_->PreDrawScene();
	highLumi_->Draw();
	gaussianBlur_->PostDrawScene();
}
