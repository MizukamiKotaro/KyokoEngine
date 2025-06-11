#include "GlobalVariableData.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

#ifdef _DEBUG
#include "ImGuiManager/ImGuiManager.h"
#endif // _DEBUG


template<typename EnumT>
int32_t GlobalVariableData::EnumToInt(EnumT id)
{
	return static_cast<int32_t>(id);
}

void GlobalVariableData::Update()
{
#ifdef _DEBUG
	UpdateValues();
	SetGlobals();
#endif // _DEBUG
}

void GlobalVariableData::Save()
{
	global_->Save();
}

void GlobalVariableData::SetData(const std::map<int32_t, Item>& items)
{
	values_ = items;
	SetGlobals();
}

const std::map<int32_t, GlobalVariableData::Item>& GlobalVariableData::GetData() const
{
	return values_;
}

GlobalVariableData::GlobalVariableData(const std::string& chunkName, const std::string& groupName, const std::string& tree1, const std::string& tree2, const std::string& tree3, const std::string& tree4, const std::string& tree5)
{
	global_ = std::make_unique<GlobalVariableUser>(chunkName, groupName, tree1, tree2, tree3, tree4, tree5);
}

void GlobalVariableData::ResetGroupName(const std::string& groupName)
{
	global_->ResetGroupName(groupName);
}

void GlobalVariableData::CreateGroup()
{
	global_->CreateGroup();
}

void GlobalVariableData::AddItem(int32_t id, const std::string& key, int32_t value, const std::string& tree1, const std::string& tree2, const std::string& tree3, const std::string& tree4, const std::string& tree5, const std::string& tree6)
{
	global_->AddItem(key, value, tree1, tree2, tree3, tree4, tree5, tree6);
	values_[id] = global_->GetIntValue(key, tree1, tree2, tree3, tree4, tree5, tree6);
#ifdef _DEBUG
	SetNames(id, ItemStruct::kInt, key, tree1, tree2, tree3, tree4, tree5, tree6);
#endif // _DEBUG
}

void GlobalVariableData::AddItem(int32_t id, const std::string& key, float value, const std::string& tree1, const std::string& tree2, const std::string& tree3, const std::string& tree4, const std::string& tree5, const std::string& tree6)
{
	global_->AddItem(key, value, tree1, tree2, tree3, tree4, tree5, tree6);
	values_[id] = global_->GetFloatValue(key, tree1, tree2, tree3, tree4, tree5, tree6);
#ifdef _DEBUG
	SetNames(id, ItemStruct::kFloat, key, tree1, tree2, tree3, tree4, tree5, tree6);
#endif // _DEBUG
}

void GlobalVariableData::AddItem(int32_t id, const std::string& key, const Vector2& value, const std::string& tree1, const std::string& tree2, const std::string& tree3, const std::string& tree4, const std::string& tree5, const std::string& tree6)
{
	global_->AddItem(key, value, tree1, tree2, tree3, tree4, tree5, tree6);
	values_[id] = global_->GetVector2Value(key, tree1, tree2, tree3, tree4, tree5, tree6);
#ifdef _DEBUG
	SetNames(id, ItemStruct::kVector2, key, tree1, tree2, tree3, tree4, tree5, tree6);
#endif // _DEBUG
}

void GlobalVariableData::AddItem(int32_t id, const std::string& key, const Vector3& value, const std::string& tree1, const std::string& tree2, const std::string& tree3, const std::string& tree4, const std::string& tree5, const std::string& tree6)
{
	global_->AddItem(key, value, tree1, tree2, tree3, tree4, tree5, tree6);
	values_[id] = global_->GetVector3Value(key, tree1, tree2, tree3, tree4, tree5, tree6);
#ifdef _DEBUG
	SetNames(id, ItemStruct::kVector3, key, tree1, tree2, tree3, tree4, tree5, tree6);
#endif // _DEBUG
}

void GlobalVariableData::AddItem(int32_t id, const std::string& key, const Vector4& value, const std::string& tree1, const std::string& tree2, const std::string& tree3, const std::string& tree4, const std::string& tree5, const std::string& tree6)
{
	global_->AddItem(key, value, tree1, tree2, tree3, tree4, tree5, tree6);
	values_[id] = global_->GetVector4Value(key, tree1, tree2, tree3, tree4, tree5, tree6);
#ifdef _DEBUG
	SetNames(id, ItemStruct::kVector4, key, tree1, tree2, tree3, tree4, tree5, tree6);
#endif // _DEBUG
}

void GlobalVariableData::AddItem(int32_t id, const std::string& key, bool value, const std::string& tree1, const std::string& tree2, const std::string& tree3, const std::string& tree4, const std::string& tree5, const std::string& tree6)
{
	global_->AddItem(key, value, tree1, tree2, tree3, tree4, tree5, tree6);
	values_[id] = global_->GetBoolValue(key, tree1, tree2, tree3, tree4, tree5, tree6);
#ifdef _DEBUG
	SetNames(id, ItemStruct::kBool, key, tree1, tree2, tree3, tree4, tree5, tree6);
#endif // _DEBUG
}

void GlobalVariableData::AddItem(int32_t id, const std::string& key, const std::string& value, const std::string& tree1, const std::string& tree2, const std::string& tree3, const std::string& tree4, const std::string& tree5, const std::string& tree6)
{
	global_->AddItem(key, value, tree1, tree2, tree3, tree4, tree5, tree6);
	values_[id] = global_->GetStringValue(key, tree1, tree2, tree3, tree4, tree5, tree6);
#ifdef _DEBUG
	SetNames(id, ItemStruct::kString, key, tree1, tree2, tree3, tree4, tree5, tree6);
#endif // _DEBUG
}

void GlobalVariableData::AddItemColor(int32_t id, const std::string& key, const Vector4& value, const std::string& tree1, const std::string& tree2, const std::string& tree3, const std::string& tree4, const std::string& tree5, const std::string& tree6)
{
	global_->AddItemColor(key, value, tree1, tree2, tree3, tree4, tree5, tree6);
	values_[id] = global_->GetColor(key, tree1, tree2, tree3, tree4, tree5, tree6);
#ifdef _DEBUG
	SetNames(id, ItemStruct::kColor, key, tree1, tree2, tree3, tree4, tree5, tree6);
#endif // _DEBUG
}

void GlobalVariableData::AddItemCombo(int32_t id, const std::string& key, ComboNameType type, const std::string& tree1, const std::string& tree2, const std::string& tree3, const std::string& tree4, const std::string& tree5, const std::string& tree6)
{
	global_->AddItemCombo(key, type, tree1, tree2, tree3, tree4, tree5, tree6);
	values_[id] = global_->GetCombo(key, type, tree1, tree2, tree3, tree4, tree5, tree6);
#ifdef _DEBUG
	SetNames(id, ItemStruct::kCombo, key, tree1, tree2, tree3, tree4, tree5, tree6);
	comboTypes_[id] = type;
#endif // _DEBUG
}

void GlobalVariableData::AddItemCombo(int32_t id, const std::string& key, int32_t type, const std::string& tree1, const std::string& tree2, const std::string& tree3, const std::string& tree4, const std::string& tree5, const std::string& tree6)
{
	global_->AddItemCombo(key, type, tree1, tree2, tree3, tree4, tree5, tree6);
	values_[id] = global_->GetCombo(key, type, tree1, tree2, tree3, tree4, tree5, tree6);
#ifdef _DEBUG
	SetNames(id, ItemStruct::kComboID, key, tree1, tree2, tree3, tree4, tree5, tree6);
	comboIDs_[id] = type;
#endif // _DEBUG
}

int32_t GlobalVariableData::GetIntValue(int32_t id)
{
	return std::get<int32_t>(values_[id]);
}

float GlobalVariableData::GetFloatValue(int32_t id)
{
	return std::get<float>(values_[id]);
}

const Vector2& GlobalVariableData::GetVector2Value(int32_t id)
{
	return std::get<Vector2>(values_[id]);
}

const Vector3& GlobalVariableData::GetVector3Value(int32_t id)
{
	return std::get<Vector3>(values_[id]);
}

const Vector4& GlobalVariableData::GetVector4Value(int32_t id)
{
	return std::get<Vector4>(values_[id]);
}

bool GlobalVariableData::GetBoolValue(int32_t id)
{
	return std::get<bool>(values_[id]);
}

const std::string& GlobalVariableData::GetStringValue(int32_t id)
{
	return std::get<std::string>(values_[id]);
}

const Vector4& GlobalVariableData::GetColor(int32_t id)
{
	return std::get<Vector4>(values_[id]);
}

const std::string& GlobalVariableData::GetCombo(int32_t id)
{
	return std::get<std::string>(values_[id]);
}

void GlobalVariableData::SetNames(int32_t id, ItemStruct itemStruct, const std::string& key, const std::string& tree1, const std::string& tree2, const std::string& tree3, const std::string& tree4, const std::string& tree5, const std::string& tree6)
{
#ifdef _DEBUG
	names_[id].first = itemStruct;
	names_[id].second.first = key;
	names_[id].second.second.clear();
	names_[id].second.second.push_back(tree1);
	names_[id].second.second.push_back(tree2);
	names_[id].second.second.push_back(tree3);
	names_[id].second.second.push_back(tree4);
	names_[id].second.second.push_back(tree5);
	names_[id].second.second.push_back(tree6);
#else
	(void)id; (void)itemStruct; (void)key; (void)tree1; (void)tree2; (void)tree3; (void)tree4; (void)tree5; (void)tree6;
#endif // _DEBUG
}

void GlobalVariableData::DrawImGui(int32_t id)
{
#ifdef _DEBUG
	if (names_[id].first == ItemStruct::kInt) {
		int32_t* ptr = std::get_if<int32_t>(&values_[id]);
		ImGui::DragInt(names_[id].second.first.c_str(), ptr, 1);
	}
	else if (names_[id].first == ItemStruct::kFloat) {
		float* ptr = std::get_if<float>(&values_[id]);
		ImGui::DragFloat(names_[id].second.first.c_str(), ptr, 0.01f);
	}
	else if (names_[id].first == ItemStruct::kVector2) {
		Vector2* ptr = std::get_if<Vector2>(&values_[id]);
		ImGui::DragFloat2(names_[id].second.first.c_str(), reinterpret_cast<float*>(ptr), 0.01f);
	}
	else if (names_[id].first == ItemStruct::kVector3) {
		Vector3* ptr = std::get_if<Vector3>(&values_[id]);
		ImGui::DragFloat3(names_[id].second.first.c_str(), reinterpret_cast<float*>(ptr), 0.01f);
	}
	else if (names_[id].first == ItemStruct::kVector4) {
		Vector4* ptr = std::get_if<Vector4>(&values_[id]);
		ImGui::DragFloat4(names_[id].second.first.c_str(), reinterpret_cast<float*>(ptr), 0.01f);
	}
	else if (names_[id].first == ItemStruct::kBool) {
		bool* ptr = std::get_if<bool>(&values_[id]);
		ImGui::Checkbox(names_[id].second.first.c_str(), ptr);
	}
	else if (names_[id].first == ItemStruct::kString) {
		std::string* ptr = std::get_if<std::string>(&values_[id]);
		std::string text = names_[id].second.first + ":" + (*ptr);
		ImGui::Text(text.c_str());
	}
	else if (names_[id].first == ItemStruct::kColor) {
		Vector4* ptr = std::get_if<Vector4>(&values_[id]);
		ImGui::ColorEdit4(names_[id].second.first.c_str(), reinterpret_cast<float*>(ptr));
	}
	else if (names_[id].first == ItemStruct::kCombo) {
		std::string* ptr = std::get_if<std::string>(&values_[id]);
		global_->DrawImGuiCombo(names_[id].second.first.c_str(), comboTypes_[id], ptr);
	}
	else if (names_[id].first == ItemStruct::kComboID) {
		std::string* ptr = std::get_if<std::string>(&values_[id]);
		global_->DrawImGuiCombo(names_[id].second.first.c_str(), comboIDs_[id], ptr);
	}
#else
	(void)id;
#endif // _DEBUG
}

void GlobalVariableData::SetVariable(int32_t id, int32_t value)
{
#ifdef _DEBUG
	values_[id] = value;
	global_->SetVariable(names_[id].second.first, value, names_[id].second.second[0], names_[id].second.second[1], names_[id].second.second[2], names_[id].second.second[3], names_[id].second.second[4], names_[id].second.second[5]);
#else
	(void)id; (void)value;
#endif // _DEBUG
}

void GlobalVariableData::SetVariable(int32_t id, float value)
{
#ifdef _DEBUG
	values_[id] = value;
	global_->SetVariable(names_[id].second.first, value, names_[id].second.second[0], names_[id].second.second[1], names_[id].second.second[2], names_[id].second.second[3], names_[id].second.second[4], names_[id].second.second[5]);
#else
	(void)id; (void)value;
#endif // _DEBUG
}

void GlobalVariableData::SetVariable(int32_t id, const Vector2& value)
{
#ifdef _DEBUG
	values_[id] = value;
	global_->SetVariable(names_[id].second.first, value, names_[id].second.second[0], names_[id].second.second[1], names_[id].second.second[2], names_[id].second.second[3], names_[id].second.second[4], names_[id].second.second[5]);
#else
	(void)id; (void)value;
#endif // _DEBUG
}

void GlobalVariableData::SetVariable(int32_t id, const Vector3& value)
{
#ifdef _DEBUG
	values_[id] = value;
	global_->SetVariable(names_[id].second.first, value, names_[id].second.second[0], names_[id].second.second[1], names_[id].second.second[2], names_[id].second.second[3], names_[id].second.second[4], names_[id].second.second[5]);
#else
	(void)id; (void)value;
#endif // _DEBUG
}

void GlobalVariableData::SetVariable(int32_t id, const Vector4& value)
{
#ifdef _DEBUG
	values_[id] = value;
	global_->SetVariable(names_[id].second.first, value, names_[id].second.second[0], names_[id].second.second[1], names_[id].second.second[2], names_[id].second.second[3], names_[id].second.second[4], names_[id].second.second[5]);
#else
	(void)id; (void)value;
#endif // _DEBUG
}

void GlobalVariableData::SetVariable(int32_t id, bool value)
{
#ifdef _DEBUG
	values_[id] = value;
	global_->SetVariable(names_[id].second.first, value, names_[id].second.second[0], names_[id].second.second[1], names_[id].second.second[2], names_[id].second.second[3], names_[id].second.second[4], names_[id].second.second[5]);
#else
	(void)id; (void)value;
#endif // _DEBUG
}

void GlobalVariableData::SetVariable(int32_t id, const std::string& value)
{
#ifdef _DEBUG
	values_[id] = value;
	global_->SetVariable(names_[id].second.first, value, names_[id].second.second[0], names_[id].second.second[1], names_[id].second.second[2], names_[id].second.second[3], names_[id].second.second[4], names_[id].second.second[5]);
#else
	(void)id; (void)value;
#endif // _DEBUG
}

void GlobalVariableData::SetColor(int32_t id, const Vector4& value)
{
#ifdef _DEBUG
	values_[id] = value;
	global_->SetColor(names_[id].second.first, value, names_[id].second.second[0], names_[id].second.second[1], names_[id].second.second[2], names_[id].second.second[3], names_[id].second.second[4], names_[id].second.second[5]);
#else
	(void)id; (void)value;
#endif // _DEBUG
}

void GlobalVariableData::SetCombo(int32_t id, const std::string& value)
{
#ifdef _DEBUG
	values_[id] = value;
	if (names_[id].first == ItemStruct::kCombo) {
		global_->SetCombo(names_[id].second.first, comboTypes_[id], value, names_[id].second.second[0], names_[id].second.second[1], names_[id].second.second[2], names_[id].second.second[3], names_[id].second.second[4], names_[id].second.second[5]);
	}
	else {
		global_->SetCombo(names_[id].second.first, comboIDs_[id], value, names_[id].second.second[0], names_[id].second.second[1], names_[id].second.second[2], names_[id].second.second[3], names_[id].second.second[4], names_[id].second.second[5]);
	}
#else
	(void)id; (void)value;
#endif // _DEBUG
}

void GlobalVariableData::UpdateValues()
{
#ifdef _DEBUG
	for (int32_t i = 0; i < int32_t(names_.size()); i++) {
		switch (names_[i].first)
		{
		case ItemStruct::kInt:
			values_[i] = global_->GetIntValue(names_[i].second.first, names_[i].second.second[0], names_[i].second.second[1], names_[i].second.second[2], names_[i].second.second[3], names_[i].second.second[4], names_[i].second.second[5]);
			break;
		case ItemStruct::kFloat:
			values_[i] = global_->GetFloatValue(names_[i].second.first, names_[i].second.second[0], names_[i].second.second[1], names_[i].second.second[2], names_[i].second.second[3], names_[i].second.second[4], names_[i].second.second[5]);
			break;
		case ItemStruct::kVector2:
			values_[i] = global_->GetVector2Value(names_[i].second.first, names_[i].second.second[0], names_[i].second.second[1], names_[i].second.second[2], names_[i].second.second[3], names_[i].second.second[4], names_[i].second.second[5]);
			break;
		case ItemStruct::kVector3:
			values_[i] = global_->GetVector3Value(names_[i].second.first, names_[i].second.second[0], names_[i].second.second[1], names_[i].second.second[2], names_[i].second.second[3], names_[i].second.second[4], names_[i].second.second[5]);
			break;
		case ItemStruct::kVector4:
			values_[i] = global_->GetVector4Value(names_[i].second.first, names_[i].second.second[0], names_[i].second.second[1], names_[i].second.second[2], names_[i].second.second[3], names_[i].second.second[4], names_[i].second.second[5]);
			break;
		case ItemStruct::kBool:
			values_[i] = global_->GetBoolValue(names_[i].second.first, names_[i].second.second[0], names_[i].second.second[1], names_[i].second.second[2], names_[i].second.second[3], names_[i].second.second[4], names_[i].second.second[5]);
			break;
		case ItemStruct::kString:
			values_[i] = global_->GetStringValue(names_[i].second.first, names_[i].second.second[0], names_[i].second.second[1], names_[i].second.second[2], names_[i].second.second[3], names_[i].second.second[4], names_[i].second.second[5]);
			break;
		case ItemStruct::kColor:
			values_[i] = global_->GetColor(names_[i].second.first, names_[i].second.second[0], names_[i].second.second[1], names_[i].second.second[2], names_[i].second.second[3], names_[i].second.second[4], names_[i].second.second[5]);
			break;
		case ItemStruct::kCombo:
			values_[i] = global_->GetCombo(names_[i].second.first, comboTypes_[i], names_[i].second.second[0], names_[i].second.second[1], names_[i].second.second[2], names_[i].second.second[3], names_[i].second.second[4], names_[i].second.second[5]);
			break;
		case ItemStruct::kComboID:
			values_[i] = global_->GetCombo(names_[i].second.first, comboIDs_[i], names_[i].second.second[0], names_[i].second.second[1], names_[i].second.second[2], names_[i].second.second[3], names_[i].second.second[4], names_[i].second.second[5]);
			break;
		default:
			break;
		}
	}
#endif // _DEBUG
}

void GlobalVariableData::SetGlobals()
{
#ifdef _DEBUG
	for (int32_t i = 0; i < int32_t(names_.size()); i++) {
		switch (names_[i].first)
		{
		case ItemStruct::kInt:
			SetVariable(i, std::get<int32_t>(values_[i]));
			break;
		case ItemStruct::kFloat:
			SetVariable(i, std::get<float>(values_[i]));
			break;
		case ItemStruct::kVector2:
			SetVariable(i, std::get<Vector2>(values_[i]));
			break;
		case ItemStruct::kVector3:
			SetVariable(i, std::get<Vector3>(values_[i]));
			break;
		case ItemStruct::kVector4:
			SetVariable(i, std::get<Vector4>(values_[i]));
			break;
		case ItemStruct::kBool:
			SetVariable(i, std::get<bool>(values_[i]));
			break;
		case ItemStruct::kString:
			SetVariable(i, std::get<std::string>(values_[i]));
			break;
		case ItemStruct::kColor:
			SetColor(i, std::get<Vector4>(values_[i]));
			break;
		case ItemStruct::kCombo:
			SetCombo(i, std::get<std::string>(values_[i]));
			break;
		case ItemStruct::kComboID:
			SetCombo(i, std::get<std::string>(values_[i]));
			break;
		default:
			break;
		}
	}
#endif // _DEBUG
}

void GlobalVariableData::DrawTreeRecursive(const std::map<int32_t, std::pair<ItemStruct, std::pair<std::string, std::vector<std::string>>>>& names, int32_t level, const std::string& parentPath)
{
#ifdef _DEBUG
	std::map<std::string, std::vector<int32_t>> grouped;

	for (std::map<int32_t, std::pair<ItemStruct, std::pair<std::string, std::vector<std::string>>>>::const_iterator it = names.begin(); it != names.end(); ++it) {
		int32_t id = it->first;
		const std::pair<ItemStruct, std::pair<std::string, std::vector<std::string>>>& value = it->second;
		const std::vector<std::string>& path = value.second.second;

		if (level >= static_cast<int32_t>(path.size())) {
			continue;
		}

		if (!parentPath.empty()) {
			std::string fullPath = "";
			for (int32_t i = 0; i < level; ++i) {
				if (path[i] != "_") {
					fullPath += path[i] + "/";
				}
			}
			if (fullPath != parentPath) {
				continue;
			}
		}

		const std::string& nodeName = path[level];
		grouped[nodeName].push_back(id);
	}

	// グループごとに描画
	std::map<std::string, std::vector<int32_t>>::iterator groupIt;
	for (groupIt = grouped.begin(); groupIt != grouped.end(); ++groupIt) {
		const std::string& name = groupIt->first;
		const std::vector<int32_t>& ids = groupIt->second;

		if (name == "_") {
			for (size_t i = 0; i < ids.size(); ++i) {
				int32_t id = ids[i];
				std::map<int32_t, std::pair<ItemStruct, std::pair<std::string, std::vector<std::string>>>>::const_iterator itemIt = names.find(id);
				if (itemIt != names.end()) {
					DrawImGui(id);
				}
			}
		}
		else {
			if (ImGui::TreeNode(name.c_str())) {
				DrawTreeRecursive(names, level + 1, parentPath + name + "/");
				ImGui::TreePop();
			}
		}
	}
#else
	(void)names; (void)level; (void)parentPath;
#endif // _DEBUG
}

void GlobalVariableData::DrawImGui(const std::string& treeName, bool isSave)
{
#ifdef _DEBUG
	if (ImGui::TreeNode(treeName.c_str())) {
		DrawTreeRecursive(names_, 0);
		if (isSave) {
			SetGlobals();
		}
		ImGui::TreePop();
	}
#else
	(void)treeName; (void)isSave;
#endif // _DEBUG
}

