#include "StageFloorEditor.h"
#include "Camera.h"
#include "TextureManager.h"

StageFloorEditor::StageFloorEditor(const std::string& mainName, const std::string& name, uint32_t no)
{
	model_ = std::make_unique<Model>("ground");
	model_->SetTexture(TextureManager::GetInstance()->LoadTexture("Resources/Texture/white.png"));
	model_->Update();
	model_->UnUsedLight();
	model_->SetColor(Vector4{ 1.0f,1.0f,1.0f,1.0f });
	isWater_ = true;
	isStage_ = true;
	WaterInitialize();
	model_->SetSRVGPUDescriptorHandle_(post_->GetSRVGPUDescriptorHandle());
	CreateStageEditor(mainName, name, no);
	SetGlobalVariable();
	WaterUpdate(0.2f);
	WaterUpdate(0.2f);
}

void StageFloorEditor::Initialize()
{
}

void StageFloorEditor::Update(float time)
{
#ifdef _DEBUG
	UpdateGlobalVariable();
#endif // _DEBUG
	WaterUpdate(time);
}

void StageFloorEditor::Draw(const Camera& camera)
{
	model_->Draw(camera);
}

void StageFloorEditor::SetGlobalVariable()
{
	stageEditor_->AddItem("スケール", 1.0f);
	stageEditor_->AddItemColor("床の色", Vector4{ 0.1f,0.1f,0.1f,1.0f });
	stageEditor_->AddItem("水にするか", isWater_);
	stageEditor_->AddItem("水の色", Vector3{ 0.3f,1.0f,0.8f }, "水の設定");
	stageEditor_->AddItem("うねうねの色", Vector3{ 0.8f,0.8f,0.8f }, "水の設定");
	stageEditor_->AddItem("うねうねの動きにくさ", int(uneune_), "水の設定");
	stageEditor_->AddItem("密度", noise_->noiseData_->density, "水の設定");
	stageEditor_->AddItem("ステージを描画するか", isStage_);
	ApplyGlobalVariable();
}

void StageFloorEditor::ApplyGlobalVariable()
{
	model_->transform_.scale_.x = stageEditor_->GetFloatValue("スケール");
	model_->transform_.scale_ = { model_->transform_.scale_.x ,model_->transform_.scale_.x ,model_->transform_.scale_.x };
	model_->Update();
	bool preIsWater = isWater_;
	isWater_ = stageEditor_->GetBoolValue("水にするか");
	Vector3 waterColor = stageEditor_->GetVector3Value("水の色", "水の設定");
	waterColor = waterColor.Clamp(0.0, 1.0f);
	stageEditor_->SetVariable("水の色", waterColor, "水の設定");
	noise_->noiseData_->waterColor = { waterColor.x,waterColor.y,waterColor.z,1.0f };
	waterColor = stageEditor_->GetVector3Value("うねうねの色", "水の設定");
	waterColor = waterColor.Clamp(0.0, 1.0f);
	stageEditor_->SetVariable("うねうねの色", waterColor, "水の設定");
	noise_->noiseData_->lightningColor = { waterColor.x,waterColor.y,waterColor.z,1.0f };
	noise_->noiseData_->density = stageEditor_->GetFloatValue("密度", "水の設定");
	if (noise_->noiseData_->density <= 0.0f) {
		noise_->noiseData_->density = 0.1f;
		stageEditor_->SetVariable("密度", noise_->noiseData_->density, "水の設定");
	}
	uneune_ = stageEditor_->GetIntValue("うねうねの動きにくさ", "水の設定");
	if (uneune_ <= 0) {
		uneune_ = 1;
		stageEditor_->SetVariable("うねうねの動きにくさ", int(uneune_), "水の設定");
	}
	if (!preIsWater && isWater_) {
		model_->SetSRVGPUDescriptorHandle_(post_->GetSRVGPUDescriptorHandle());
		model_->SetColor(Vector4{ 1.0f,1.0f,1.0f,1.0f });
	}
	else if (preIsWater && !isWater_) {
		model_->SetTexture(TextureManager::GetInstance()->LoadTexture("Resources/Texture/white.png"));
		model_->SetColor(stageEditor_->GetColor("床の色"));
	}
	else if (!isWater_) {
		model_->SetColor(stageEditor_->GetColor("床の色"));
	}
}

void StageFloorEditor::WaterInitialize()
{
	if (!post_) {
		post_ = std::make_unique<PostEffect>();
	}
	if (!noise_) {
		noise_ = std::make_unique<Noise>();
	}
	uneune_ = 20;
}

void StageFloorEditor::WaterUpdate(const float& time)
{
	if (isWater_) {
		noise_->Update(time / uneune_);
		post_->PreDrawScene();
		noise_->Draw();
		post_->PostDrawScene();
	}
}
