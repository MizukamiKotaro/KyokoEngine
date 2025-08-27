#include "GlobalDataManager.h"

#include "GlobalVariables/GlobalVariableComboNames.h"

#ifdef _DEBUG
#include "imgui.h"
#endif // _DEBUG


GlobalDataManager* GlobalDataManager::GetInstance()
{
	static GlobalDataManager instance;
	return &instance;
}

void GlobalDataManager::Initialize()
{
	names_ = std::make_unique<GlobalNames>(kChunkName, "Names");
	AddTypes();

	getterType_.first = ComboTypeNames::kComboTypeNamesEnd;

#ifdef _DEBUG
	// エディターデータの作成
	editorData_.resize(Kyoko::EnumToInt(ComboTypeNames::kComboTypeNamesEnd));
	for (int32_t i = 0; i < Kyoko::EnumToInt(ComboTypeNames::kComboTypeNamesEnd); i++) {
		editorData_[i] = std::make_unique<EditorData>();
		editorData_[i]->data.reset(CreateData(typeNames_[i]));
		editorData_[i]->data->CreateData(kPatternName, typeNames_[i], kDefault);
		Save(editorData_[i]->data, typeNames_[i], kDefault);
		editorData_[i]->data->CreateData("Default", typeNames_[i], kDefault);
		SetData(editorData_[i]->data, typeNames_[i], kDefault);
		editorData_[i]->currentName = kDefault;
	}
#endif // _DEBUG
	 
	isDebug_ = false;
}

void GlobalDataManager::Update()
{
#ifdef _DEBUG
	ImGui::Begin("KyokoEditor");
	ImGui::Checkbox("デバッグオン", &isDebug_);
	for (int32_t i = 0; i < Kyoko::EnumToInt(ComboTypeNames::kComboTypeNamesEnd); i++) {
		isSave_[i] = false;
		if (ImGui::TreeNode(typeNames_[i].c_str())) {
			editorData_[i]->data->Update();

			if (ImGui::RadioButton("新規作成", editorData_[i]->isNewMake)) {
				editorData_[i]->isNewMake = true;
				SetData(editorData_[i]->data, typeNames_[i], editorData_[i]->currentName);
			}
			ImGui::SameLine();
			if (ImGui::RadioButton("既存編集", !editorData_[i]->isNewMake)) {
				editorData_[i]->isNewMake = false;
				SetData(editorData_[i]->data, typeNames_[i], editorData_[i]->currentName);
			}

			if (editorData_[i]->isNewMake) {
				// 新規作成の場合
				ImGui::InputText("パターン名", editorData_[i]->inputName, IM_ARRAYSIZE(editorData_[i]->inputName));
				// ImGuiでデータの描画
				editorData_[i]->data->DrawImGui("調整項目");

				// 入力がちゃんと行われているか
				bool isInputEmpty = (std::strlen(editorData_[i]->inputName) == 0) ||
					(std::all_of(editorData_[i]->inputName, editorData_[i]->inputName + std::strlen(editorData_[i]->inputName),
						[](char c) { return std::isspace(static_cast<unsigned char>(c)); }));
				// 禁止文字（_ や /）が含まれていないかを確認
				bool hasInvalidChars = std::strchr(editorData_[i]->inputName, '_') != nullptr ||
					std::strchr(editorData_[i]->inputName, '/') != nullptr;

				// すべての条件が満たされたときのみボタンを表示
				if (!isInputEmpty && !hasInvalidChars) {
					if (ImGui::Button("作成")) {
						Save(editorData_[i]->data, typeNames_[i], editorData_[i]->inputName);
						names_->AddComboName(i, typeNames_[i], editorData_[i]->inputName);
						isSave_[i] = true;
					}
				}
			}
			else {
				// 既存データの編集の場合
				// ImGuiComboの描画
				const std::vector<std::string>& comboList = names_->GetNames(typeNames_[i]);

				// 現在の項目 index を取得
				int currentItem = 0;
				for (int j = 0; j < static_cast<int>(comboList.size()); ++j) {
					if (comboList[j] == editorData_[i]->currentName) {
						currentItem = j;
						break;
					}
				}
				const std::string& previewLabel = comboList.empty() ? "" : comboList[currentItem];

				// BeginCombo + 検索機能
				if (ImGui::BeginCombo(typeNames_[i].c_str(), previewLabel.c_str())) {
					// 検索入力欄
					ImGui::InputText("検索", editorData_[i]->filterName, IM_ARRAYSIZE(editorData_[i]->filterName));

					for (int n = 0; n < static_cast<int>(comboList.size()); ++n) {
						const std::string& item = comboList[n];

						// 検索フィルタが空でない、一致しない場合はスキップ
						if (std::strlen(editorData_[i]->filterName) > 0 && item.find(editorData_[i]->filterName) == std::string::npos) {
							continue;
						}

						bool isSelected = (currentItem == n);
						if (ImGui::Selectable(item.c_str(), isSelected)) {
							currentItem = n;
							editorData_[i]->currentName = item;
							SetData(editorData_[i]->data, typeNames_[i], editorData_[i]->currentName);
							break;
						}

						if (isSelected) {
							ImGui::SetItemDefaultFocus();
						}
					}

					ImGui::EndCombo();
				}
				// ImGuiでデータの描画
				editorData_[i]->data->DrawImGui("調整項目");
				if (ImGui::Button("保存")) {
					Save(editorData_[i]->data, typeNames_[i], editorData_[i]->currentName);
					isSave_[i] = true;
				}
			}

			ImGui::TreePop();
		}
	}
	ImGui::End();
#endif // _DEBUG
}

const std::map<int32_t, GlobalVariableData::Item>& GlobalDataManager::GetData(ComboTypeNames type, const std::string& name)
{
	if (getterType_.first == type) {
		if (getterType_.second == name) {
			return getterData_->GetData();
		}
		getterType_.second = name;
		getterData_->CreateData(kPatternName, typeNames_[Kyoko::EnumToInt(type)], name);
		return getterData_->GetData();
	}
	else {
		getterType_.first = type;
		getterType_.second = name;
		std::string typeName = typeNames_[Kyoko::EnumToInt(type)];
		getterData_.reset(CreateData(typeName));
		getterData_->CreateData(kPatternName, typeName, name);
		return getterData_->GetData();
	}
}

const GlobalVariableData& GlobalDataManager::GetGlobalData(ComboTypeNames type, const std::string& name)
{
	if (getterType_.first == type) {
		if (getterType_.second == name) {
#ifdef _DEBUG
			getterData_->CreateData(kPatternName, typeNames_[Kyoko::EnumToInt(type)], name);
#endif // _DEBUG
			return getterData_->GetGlobalData();
		}
		getterType_.second = name;
		getterData_->CreateData(kPatternName, typeNames_[Kyoko::EnumToInt(type)], name);
		return getterData_->GetGlobalData();
	}
	else {
		getterType_.first = type;
		getterType_.second = name;
		std::string typeName = typeNames_[Kyoko::EnumToInt(type)];
		getterData_.reset(CreateData(typeName));
		getterData_->CreateData(kPatternName, typeName, name);
		return getterData_->GetGlobalData();
	}
}

bool GlobalDataManager::IsDebug() const
{
	return isDebug_;
}

bool GlobalDataManager::IsSave(ComboTypeNames type)
{
	return isSave_[Kyoko::EnumToInt(type)];
}

void GlobalDataManager::AddTypes()
{
	// 第二引数は書いてあるもの同様Englishで設定してクレメンス
	// エディターでパターンを増やしたいものの設定
	//AddType(ComboTypeNames::kStagePattern, "StagePattern");

	// コードで行うパターンの設定
	//AddSystemType(SystemComboTypeNames::kBlockType, "BlockType", "固定");

	AddEffekseerTypes();
}

void GlobalDataManager::AddEffekseerTypes()
{
	// これを汎用的にする
	std::filesystem::path dir("Effekseer/");
	if (!std::filesystem::exists(dir)) {
		return;
	}
	GlobalVariableComboNames* global = GlobalVariableComboNames::GetInstance();
	std::filesystem::recursive_directory_iterator dir_it(dir);
	for (const std::filesystem::directory_entry& entry : dir_it) {

		const std::filesystem::path& filePath = entry.path();

		std::string extension = filePath.extension().string();

		if (extension.compare(".efkefc") != 0) {
			continue;
		}
		std::string filePathStr = filePath.stem().string();

		global;
		//global->AddComboName(ComboNameType::kEffekseer, filePathStr);
	}
}

BaseGlobalData* GlobalDataManager::CreateData(const std::string& type)
{
	// 新しくエディターのパターンを増やす場合は追記してね
	BaseGlobalData* data = nullptr;
	type;
	//switch (nameTypes_[type])
	//{
	///*case ComboTypeNames::kStagePattern:
	//	data = new StageData();
	//	break;
	//case ComboTypeNames::kBlockPattern:
	//	data = new BlockData();
	//	break;
	//case ComboTypeNames::kEffekseerDataPattern:
	//	data = new EffekseerData();
	//	break;*/
	//default:
	//	break;
	//}

	return data;
}

void GlobalDataManager::AddType(ComboTypeNames id, const std::string& type)
{
	typeNames_[Kyoko::EnumToInt(id)] = type;
	nameTypes_[type] = id;
	names_->AddComboName(Kyoko::EnumToInt(id), type);
	isSave_[Kyoko::EnumToInt(id)] = false;
}

void GlobalDataManager::AddSystemType(SystemComboTypeNames id, const std::string& type, const std::string& name)
{
	names_->AddSystemComboName(Kyoko::EnumToInt(id), type, name);
}

void GlobalDataManager::Save(const std::unique_ptr<BaseGlobalData>& data, const std::string& typeName, const std::string& name)
{
	std::unique_ptr<BaseGlobalData> d;
	d.reset(CreateData(typeName));
	d->CreateData(kPatternName, typeName, name);
	// 一度目のセットと更新で、パラメータの数が増減するデータの数をセットして格納先を用意する
	d->SetData(data->GetData());
	d->Update();
	// 二度目のセットと更新で、用意された格納先に全てのデータをセットして生成している
	d->SetData(data->GetData());
	d->Update();
	d->Save();
}

void GlobalDataManager::SetData(std::unique_ptr<BaseGlobalData>& data, const std::string& typeName, const std::string& name)
{
	std::unique_ptr<BaseGlobalData> d;
	d.reset(CreateData(typeName));
	d->CreateData(kPatternName, typeName, name);
	// 一度目のセットと更新で、パラメータの数が増減するデータの数をセットして格納先を用意する
	data->SetData(d->GetData());
	data->Update();
	// 二度目のセットで、用意された格納先に全てのデータをセットしてしている
	data->SetData(d->GetData());
}
