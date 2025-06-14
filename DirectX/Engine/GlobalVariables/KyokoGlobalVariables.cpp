#include "KyokoGlobalVariables.h"
#include <fstream>
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "GlobalVariableComboNames.h"
#include "GlobalVariables/GlobalVariableUser.h"

#ifdef _DEBUG
#include "ImGuiManager/ImGuiManager.h"
#include "WindowsInfo/WindowsInfo.h"
#endif // _DEBUG

namespace Kyoko {
	GlobalVariables* GlobalVariables::GetInstance() {
		static GlobalVariables globalVariables;
		return &globalVariables;
	}

	void GlobalVariables::Initialize()
	{
#ifdef _DEBUG
		isDraw_ = true;
#endif // _DEBUG
		kMaxTreeNum_ = 8;
		kTreeName_.resize(kMaxTreeNum_);
		for (uint32_t i = 0; i < kMaxTreeNum_; i++) {
			kTreeName_[i] = "Tree" + std::to_string(i + 1);
		}
		kUnderBar.resize(1);
		kUnderBar[0] = "_";
		GlobalVariableComboNames::GetInstance()->Initialize();
	}

	void GlobalVariables::Finalize()
	{
#ifdef _DEBUG
		for (std::map<std::string, Chunk>::iterator itChunk = datas_.begin();
			itChunk != datas_.end(); ++itChunk) {
			const std::string& chunkName = itChunk->first;
			Chunk& chunk = itChunk->second;
			for (std::map<std::string, Group>::iterator itGroup = chunk.begin();
				itGroup != chunk.end(); ++itGroup) {
				const std::string& groupName = itGroup->first;
				SaveFile(chunkName, groupName, true);
			}
		}
#endif // _DEBUG
	}

	void GlobalVariables::Update() {
#ifdef _DEBUG
		for (std::pair<const std::string, Chunk> chunk : isTreeOpen_) {
			for (std::pair<const std::string, Group>& group : chunk.second) {
				for (std::pair<const std::string, Item>& item : group.second) {
					item.second = false;
				}
			}
		}
		ImGui::Begin("ImGuiManager");
		ImGui::Checkbox("グローバル変数を描画するか", &isDraw_);
		if (ImGui::TreeNode("タイトルバー名")) {
			int columnCount = 4;
			ImGui::Columns(columnCount, nullptr, false);
			for (std::pair<const std::string, bool>& name : isDrawTitle_) {
				ImGui::Checkbox(name.first.c_str(), &name.second);
				ImGui::NextColumn();
			}
			ImGui::Columns(1);
			ImGui::TreePop();
		}
		ImGui::End();
		if (!isDraw_) {
			return;
		}

		for (std::map<std::string, Chunk>::iterator itChunk = datas_.begin();
			itChunk != datas_.end(); ++itChunk) {
			const std::string& chunkName = itChunk->first;

			if (chunkName == kDontTouchPlayData || !isDrawTitle_[chunkName]) {
				continue;
			}

			Chunk& chunk = itChunk->second;
			if (!ImGui::Begin(chunkName.c_str(), nullptr, ImGuiWindowFlags_MenuBar)) {
				ImGui::End();
				continue;
			}
			if (!ImGui::BeginMenuBar()) {
				continue;
			}

			for (std::map<std::string, Group>::iterator itGroup = chunk.begin();
				itGroup != chunk.end(); ++itGroup) {
				const std::string& groupName = itGroup->first;
				Group& group = itGroup->second;
				if (!ImGui::BeginMenu(groupName.c_str())) {
					continue;
				}

				std::map<std::string, std::map<std::string, std::map<std::string, std::map<std::string, std::map<std::string, std::map<std::string, GroupPtr>>>>>> treeMap;
				for (std::map<std::string, Item>::iterator itItem = group.begin();
					itItem != group.end(); ++itItem) {
					const std::string& itemName = itItem->first;
					Item& item = itItem->second;
					std::vector<std::string> treeNames(kMaxTreeNum_, "_");
					MakeTreeMap(chunkName, groupName, treeMap, item, itemName, treeNames);
				}

				for (std::map<std::string, std::map<std::string, std::map<std::string, std::map<std::string, std::map<std::string, std::map<std::string, GroupPtr>>>>>>::iterator itTree1 = treeMap.begin(); itTree1 != treeMap.end(); ++itTree1) {
					const std::string& tree1 = itTree1->first;
					if (ImGui::TreeNode(tree1.c_str())) {
						isTreeOpen_[chunkName][groupName][kTreeName_[0] + tree1] = true;
						DrawTreeImGui(itTree1->second, chunkName, groupName, kTreeName_[0] + tree1);
						ImGui::TreePop();
					}
				}

				ImGui::Text("\n");
				if (ImGui::Button("Save")) {
					SaveFile(chunkName, groupName);
					std::string message = std::format("{}.json saved", chunkName + "_" + groupName);
					MessageBoxA(nullptr, message.c_str(), "GlobalVariables", 0);
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
			ImGui::End();
		}
#endif // _DEBUG
	}

	void GlobalVariables::CreateChunk(const std::string& chunkName)
	{
		datas_[chunkName];
#ifdef _DEBUG
		if (isDrawTitle_.find(chunkName) == isDrawTitle_.end()) {
			isDrawTitle_[chunkName] = false;
		}
#endif // _DEBUG
	}

	void GlobalVariables::CreateGroup(const std::string& chunkName, const std::string& groupName)
	{
		datas_[chunkName][groupName];
#ifdef _DEBUG
		if (isDrawTitle_.find(chunkName) == isDrawTitle_.end()) {
			isDrawTitle_[chunkName] = false;
		}
#endif // _DEBUG
	}

	void GlobalVariables::AddItemColor(const std::string& chunkName, const std::string& groupName, const std::string& key, const Vector4& value, const std::vector<std::string>& tree)
	{
		SetValue(chunkName, groupName, kColorName + key, value, tree);
	}

	void GlobalVariables::AddItemCombo(const std::string& chunkName, const std::string& groupName, const std::string& key, const std::string& type, const std::string& value, const std::vector<std::string>& tree)
	{
		SetValue(chunkName, groupName, kComboName + key + kComboTypeName + type, value, tree);
	}

	void GlobalVariables::EraseItem(const std::string& chunkName, const std::string& groupName, const std::string& key, const std::vector<std::string>& tree)
	{
		Group& group = datas_[chunkName][groupName];
		uint32_t i = 0;

		std::string name;
		for (const std::string& treeName : tree) {
			if (treeName == "_") {
				if (i == 0) {
					name = key;
				}
				else {
					name += "_" + key;
				}
				group.erase(name);
				break;
			}
			else {
				if (i != 0) {
					name += "_";
				}
				name += kTreeName_[i] + treeName;
				i++;
			}
		}
	}

	void GlobalVariables::EraseItemColor(const std::string& chunkName, const std::string& groupName, const std::string& key, const std::vector<std::string>& tree)
	{
		EraseItem(chunkName, groupName, kColorName + key, tree);
	}

	void GlobalVariables::EraseItem(const std::string& chunkName, const std::string& groupName, const std::string& key, const std::string& type, const std::vector<std::string>& tree)
	{
		EraseItem(chunkName, groupName, kComboName + key + kComboTypeName + type, tree);
	}

	int32_t GlobalVariables::GetIntValue(const std::string& chunkName, const std::string& groupName, const std::string& key, const std::vector<std::string>& tree) const
	{
		return GetValue<int32_t>(chunkName, groupName, key, tree);
	}

	float GlobalVariables::GetFloatValue(const std::string& chunkName, const std::string& groupName, const std::string& key, const std::vector<std::string>& tree) const
	{
		return GetValue<float>(chunkName, groupName, key, tree);
	}

	const Vector2& GlobalVariables::GetVector2Value(const std::string& chunkName, const std::string& groupName, const std::string& key, const std::vector<std::string>& tree) const
	{
		return GetValue<Vector2>(chunkName, groupName, key, tree);
	}

	const Vector3& GlobalVariables::GetVector3Value(const std::string& chunkName, const std::string& groupName, const std::string& key, const std::vector<std::string>& tree) const
	{
		return GetValue<Vector3>(chunkName, groupName, key, tree);
	}

	const Vector4& GlobalVariables::GetVector4Value(const std::string& chunkName, const std::string& groupName, const std::string& key, const std::vector<std::string>& tree) const
	{
		return GetValue<Vector4>(chunkName, groupName, key, tree);
	}

	bool GlobalVariables::GetBoolValue(const std::string& chunkName, const std::string& groupName, const std::string& key, const std::vector<std::string>& tree) const
	{
		return GetValue<bool>(chunkName, groupName, key, tree);
	}

	const std::string& GlobalVariables::GetStringValue(const std::string& chunkName, const std::string& groupName, const std::string& key, const std::vector<std::string>& tree) const
	{
		return GetValue<std::string>(chunkName, groupName, key, tree);
	}

	const Vector4& GlobalVariables::GetColor(const std::string& chunkName, const std::string& groupName, const std::string& key, const std::vector<std::string>& tree) const
	{
		return GetValue<Vector4>(chunkName, groupName, kColorName + key, tree);
	}

	const std::string& GlobalVariables::GetCombo(const std::string& chunkName, const std::string& groupName, const std::string& key, const std::string& type, const std::vector<std::string>& tree) const
	{
		return GetValue<std::string>(chunkName, groupName, kComboName + key + kComboTypeName + type, tree);
	}

	int32_t GlobalVariables::GetIntValueDontTouchImGui(const std::string& key) const
	{
		return GetValueDontTouchImGui<int32_t>(key);
	}

	float GlobalVariables::GetFloatValueDontTouchImGui(const std::string& key) const
	{
		return GetValueDontTouchImGui<float>(key);
	}

	const Vector2& GlobalVariables::GetVector2ValueDontTouchImGui(const std::string& key) const
	{
		return GetValueDontTouchImGui<Vector2>(key);
	}

	const Vector3& GlobalVariables::GetVector3ValueDontTouchImGui(const std::string& key) const
	{
		return GetValueDontTouchImGui<Vector3>(key);
	}

	const Vector4& GlobalVariables::GetVector4ValueDontTouchImGui(const std::string& key) const
	{
		return GetValueDontTouchImGui<Vector4>(key);
	}

	bool GlobalVariables::GetBoolValueDontTouchImGui(const std::string& key) const
	{
		return GetValueDontTouchImGui<bool>(key);
	}

	const std::string& GlobalVariables::GetStringValueDontTouchImGui(const std::string& key) const
	{
		return GetValueDontTouchImGui<std::string>(key);
	}

	const Vector4& GlobalVariables::GetColorDontTouchImGui(const std::string& key) const
	{
		return GetValueDontTouchImGui<Vector4>(kColorName + key);
	}

	const std::string& GlobalVariables::GetComboValueDontTouchImGui(const std::string& key, const std::string& type) const
	{
		return GetValueDontTouchImGui<std::string>(kComboName + key + kComboTypeName + type);
	}

	void GlobalVariables::SetColor(const std::string& chunkName, const std::string& groupName, const std::string& key, const Vector4& value, const std::vector<std::string>& tree)
	{
		SetValue<Vector4>(chunkName, groupName, kColorName + key, value, tree, false);
	}

	void GlobalVariables::SetCombo(const std::string& chunkName, const std::string& groupName, const std::string& key, const std::string& type, const std::string& value, const std::vector<std::string>& tree)
	{
		SetValue<std::string>(chunkName, groupName, kComboName + key + kComboTypeName + type, value, tree, false);
	}

	template<typename T>
	void GlobalVariables::SetValue(const std::string& chunkName, const std::string& groupName, const std::string& key, const T& value, const std::vector<std::string>& tree, bool isAddItem)
	{
		Group& group = datas_[chunkName][groupName];

		Item newItem{};
		newItem = value;
		uint32_t i = 0;

		std::string name;
		for (const std::string& treeName : tree) {
			if (treeName == "_") {
				if (i == 0) {
					name = key;
				}
				else {
					name += "_" + key;
				}
				if (group.find(name) == group.end()) {
					group[name] = newItem;
#ifdef _DEBUG
					std::string tName;
					for (uint32_t n = 0; n < i; n++) {
						tName += kTreeName_[n] + tree[n];
						isTreeOpen_[chunkName][groupName][tName] = false;
						tName += "_";
					}
					std::string debugName = chunkName + groupName + name;
					tempData_[debugName] = newItem;
#endif // _DEBUG
				}
				else if (!isAddItem) {
					group[name] = newItem;
#ifdef _DEBUG
					std::string debugName = chunkName + groupName + name;
					tempData_[debugName] = newItem;
#endif // _DEBUG
				}
				break;
			}
			else {
				if (i != 0) {
					name += "_";
				}
				name += kTreeName_[i] + treeName;
				i++;
			}
		}
	}
	template void GlobalVariables::SetValue<int32_t>(const std::string&, const std::string&, const std::string&, const int32_t&, const std::vector<std::string>&, bool);
	template void GlobalVariables::SetValue<float>(const std::string&, const std::string&, const std::string&, const float&, const std::vector<std::string>&, bool);
	template void GlobalVariables::SetValue<Vector2>(const std::string&, const std::string&, const std::string&, const Vector2&, const std::vector<std::string>&, bool);
	template void GlobalVariables::SetValue<Vector3>(const std::string&, const std::string&, const std::string&, const Vector3&, const std::vector<std::string>&, bool);
	template void GlobalVariables::SetValue<Vector4>(const std::string&, const std::string&, const std::string&, const Vector4&, const std::vector<std::string>&, bool);
	template void GlobalVariables::SetValue<bool>(const std::string&, const std::string&, const std::string&, const bool&, const std::vector<std::string>&, bool);
	template void GlobalVariables::SetValue<std::string>(const std::string&, const std::string&, const std::string&, const std::string&, const std::vector<std::string>&, bool);

	template<typename T>
	void GlobalVariables::AddItem(const std::string& chunkName, const std::string& groupName, const std::string& key, const T& value, const std::vector<std::string>& tree)
	{
		SetValue(chunkName, groupName, key, value, tree);
	}
	template void GlobalVariables::AddItem<int32_t>(const std::string&, const std::string&, const std::string&, const int32_t&, const std::vector<std::string>&);
	template void GlobalVariables::AddItem<float>(const std::string&, const std::string&, const std::string&, const float&, const std::vector<std::string>&);
	template void GlobalVariables::AddItem<Vector2>(const std::string&, const std::string&, const std::string&, const Vector2&, const std::vector<std::string>&);
	template void GlobalVariables::AddItem<Vector3>(const std::string&, const std::string&, const std::string&, const Vector3&, const std::vector<std::string>&);
	template void GlobalVariables::AddItem<Vector4>(const std::string&, const std::string&, const std::string&, const Vector4&, const std::vector<std::string>&);
	template void GlobalVariables::AddItem<bool>(const std::string&, const std::string&, const std::string&, const bool&, const std::vector<std::string>&);
	template void GlobalVariables::AddItem<std::string>(const std::string&, const std::string&, const std::string&, const std::string&, const std::vector<std::string>&);

	template<typename T>
	const T& GlobalVariables::GetValue(const std::string& chunkName, const std::string& groupName, const std::string& key, const std::vector<std::string>& tree) const
	{
		assert(datas_.find(chunkName) != datas_.end());
		const Chunk& chunk = datas_.at(chunkName);
		assert(chunk.find(groupName) != chunk.end());
		const Group& group = chunk.at(groupName);

		uint32_t i = 0;
		std::string name;
		for (const std::string& treeName : tree) {
			if (treeName == "_") {
				name += key;
				assert(group.find(name) != group.end());
				return std::get<T>(group.find(name)->second);
			}
			else {
				name += kTreeName_[i] + treeName + "_";
				i++;
			}
		}
		name += key;
		assert(group.find(name) != group.end());
		return std::get<T>(group.find(name)->second);
	}

	template<typename T>
	void GlobalVariables::SetVariable(const std::string& chunkName, const std::string& groupName, const std::string& key, const T& value, const std::vector<std::string>& tree)
	{
		SetValue<T>(chunkName, groupName, key, value, tree, false);
	}
	template void GlobalVariables::SetVariable<int32_t>(const std::string&, const std::string&, const std::string&, const int32_t&, const std::vector<std::string>&);
	template void GlobalVariables::SetVariable<float>(const std::string&, const std::string&, const std::string&, const float&, const std::vector<std::string>&);
	template void GlobalVariables::SetVariable<Vector2>(const std::string&, const std::string&, const std::string&, const Vector2&, const std::vector<std::string>&);
	template void GlobalVariables::SetVariable<Vector3>(const std::string&, const std::string&, const std::string&, const Vector3&, const std::vector<std::string>&);
	template void GlobalVariables::SetVariable<Vector4>(const std::string&, const std::string&, const std::string&, const Vector4&, const std::vector<std::string>&);
	template void GlobalVariables::SetVariable<bool>(const std::string&, const std::string&, const std::string&, const bool&, const std::vector<std::string>&);
	template void GlobalVariables::SetVariable<std::string>(const std::string&, const std::string&, const std::string&, const std::string&, const std::vector<std::string>&);

	template<typename T>
	void GlobalVariables::SaveAndSetVariable(const std::string& chunkName, const std::string& groupName, const std::string& key, const T& value, const std::vector<std::string>& tree)
	{
		SetVariable<T>(chunkName, groupName, key, value, tree, false);
		SaveFile(chunkName, groupName);
	}

	template<typename T>
	void GlobalVariables::AddItemDontTouchImGui(const std::string& key, const T& value)
	{
		Group& group = datas_[kDontTouchPlayData][kDontTouch];
		if (group.find(key) == group.end()) {
			std::vector<std::string> tree(1, "_");
			SetValue<T>(kDontTouchPlayData, kDontTouch, key, value, tree);
		}
	}
	template void GlobalVariables::AddItemDontTouchImGui<int32_t>(const std::string&, const int32_t&);
	template void GlobalVariables::AddItemDontTouchImGui<float>(const std::string&, const float&);
	template void GlobalVariables::AddItemDontTouchImGui<Vector2>(const std::string&, const Vector2&);
	template void GlobalVariables::AddItemDontTouchImGui<Vector3>(const std::string&, const Vector3&);
	template void GlobalVariables::AddItemDontTouchImGui<Vector4>(const std::string&, const Vector4&);
	template void GlobalVariables::AddItemDontTouchImGui<bool>(const std::string&, const bool&);
	template void GlobalVariables::AddItemDontTouchImGui<std::string>(const std::string&, const std::string&);

	template<typename T>
	const T& GlobalVariables::GetValueDontTouchImGui(const std::string& key) const
	{
		std::vector<std::string> tree(1, "_");
		return GetValue<T>(kDontTouchPlayData, kDontTouch, key, tree);
	}

	template<typename T>
	void GlobalVariables::SaveAndSetVariableDontTouchImGui(const std::string& key, const T& value)
	{
		std::vector<std::string> tree(1, "_");
		SetValue<T>(kDontTouchPlayData, kDontTouch, key, value, tree);
		SaveFile(kDontTouchPlayData, kDontTouch);
	}
	template void GlobalVariables::SaveAndSetVariableDontTouchImGui<int32_t>(const std::string&, const int32_t&);
	template void GlobalVariables::SaveAndSetVariableDontTouchImGui<float>(const std::string&, const float&);
	template void GlobalVariables::SaveAndSetVariableDontTouchImGui<Vector2>(const std::string&, const Vector2&);
	template void GlobalVariables::SaveAndSetVariableDontTouchImGui<Vector3>(const std::string&, const Vector3&);
	template void GlobalVariables::SaveAndSetVariableDontTouchImGui<Vector4>(const std::string&, const Vector4&);
	template void GlobalVariables::SaveAndSetVariableDontTouchImGui<bool>(const std::string&, const bool&);
	template void GlobalVariables::SaveAndSetVariableDontTouchImGui<std::string>(const std::string&, const std::string&);

	void GlobalVariables::AddColorDontTouchImGui(const std::string& key, const Vector4& value)
	{
		Group& group = datas_[kDontTouchPlayData][kDontTouch];
		if (group.find(kColorName + key) == group.end()) {
			std::vector<std::string> tree(1, "_");
			SetValue<Vector4>(kDontTouchPlayData, kDontTouch, kColorName + key, value, tree);
		}
	}

	void GlobalVariables::AddComboDontTouchImGui(const std::string& key, const std::string& type, const std::string& value)
	{
		Group& group = datas_[kDontTouchPlayData][kDontTouch];
		if (group.find(kComboName + key + kComboTypeName + type) == group.end()) {
			std::vector<std::string> tree(1, "_");
			SetValue<std::string>(kDontTouchPlayData, kDontTouch, kComboName + key + kComboTypeName + type, value, tree);
		}
	}

	void GlobalVariables::SaveAndSetColorDontTouchImGui(const std::string& key, const Vector4& value)
	{
		std::vector<std::string> tree(1, "_");
		SetValue<Vector4>(kDontTouchPlayData, kDontTouch, kColorName + key, value, tree);
		SaveFile(kDontTouchPlayData, kDontTouch);
	}

	void GlobalVariables::SaveAndSetComboDontTouchImGui(const std::string& key, const std::string& type, const std::string& value)
	{
		std::vector<std::string> tree(1, "_");
		SetValue<std::string>(kDontTouchPlayData, kDontTouch, kComboName + key + kComboTypeName + type, value, tree);
		SaveFile(kDontTouchPlayData, kDontTouch);
	}

	bool GlobalVariables::IsTreeOpen(const std::string& chunkName, const std::string& groupName, const std::vector<std::string>& tree)
	{
#ifdef _DEBUG
		if (isTreeOpen_.find(chunkName) == isTreeOpen_.end()) {
			return false;
		}
		const Chunk& chunk = isTreeOpen_.at(chunkName);
		if (chunk.find(groupName) == chunk.end()) {
			return false;
		}
		const Group& group = chunk.at(groupName);
		uint32_t i = 0;

		std::string name;
		for (const std::string& treeName : tree) {
			if (treeName == "_") {
				if (group.find(name) == group.end()) {
					return false;
				}
				return std::get<bool>(group.find(name)->second);
			}
			else {
				if (i != 0) {
					name += "_";
				}
				name += kTreeName_[i] + treeName;
				i++;
			}
		}
		if (group.find(name) == group.end()) {
			return false;
		}
		return std::get<bool>(group.find(name)->second);
#endif // _DEBUG
		(void)chunkName; (void)groupName; (void)tree;
		return false;
	}

	void GlobalVariables::SaveFile(const std::string& chunkName, const std::string& groupName, bool isFin)
	{
		std::map<std::string, Chunk>::iterator itChunk = datas_.find(chunkName);

		assert(itChunk != datas_.end());

		std::map<std::string, Group>::iterator itGroup = itChunk->second.find(groupName);

		assert(itGroup != itChunk->second.end());

		nlohmann::json root;

		root = nlohmann::json::object();

		root[groupName] = nlohmann::json::object();

		for (std::map<std::string, Item>::iterator itItem = itGroup->second.begin();
			itItem != itGroup->second.end(); ++itItem) {

			std::string itemName = itItem->first;
			std::vector<std::string> treeNames(kMaxTreeNum_, "_");

			MakeTreeNames(itemName, treeNames);
			Item& item = itItem->second;

			ItemToRoot(root[groupName], item, itemName, treeNames);
		}

		std::filesystem::path dir(kDirectoryPath);

		std::string filePath;
		if (isFin) {
			dir /= kZZESC;
			if (!std::filesystem::exists(dir)) {
				std::filesystem::create_directories(dir);
			}
			filePath = dir.string() + "/" + kZZESC + "_" + chunkName + "_" + groupName + ".json";
		}
		else {
			dir /= chunkName;
			if (!std::filesystem::exists(dir)) {
				std::filesystem::create_directories(dir);
			}
			filePath = dir.string() + "/" + chunkName + "_" + groupName + ".json";
		}

		std::ofstream ofs;

		ofs.open(filePath);

		if (ofs.fail()) {
#ifdef _DEBUG
			std::string message = "Failed open data file file for write";
			MessageBoxA(nullptr, message.c_str(), "GlobalVariables", 0);
#endif // _DEBUG
			assert(0);
			return;
		}

		ofs << std::setw(4) << root << std::endl;

		ofs.close();
	}

	void GlobalVariables::LoadFiles() {

		std::filesystem::path dir(kDirectoryPath);

		if (!std::filesystem::exists(dir)) {
			return;
		}

		std::filesystem::recursive_directory_iterator dir_it(dir);
		for (const std::filesystem::directory_entry& entry : dir_it) {

			const std::filesystem::path& filePath = entry.path();

			std::string extension = filePath.extension().string();

			if (extension.compare(".json") != 0) {
				continue;
			}
			std::string filePathStr = filePath.stem().string();

			size_t underscorePos = filePathStr.find('_');
			std::string chunkName = filePathStr.substr(0, underscorePos);
			std::string groupName = filePathStr.substr(underscorePos + 1);

			LoadFile(chunkName, groupName);
		}
	}

	void GlobalVariables::LoadFile(const std::string& chunkName, const std::string& groupName) {

		if (chunkName == kZZESC) {
			return;
		}
		std::string filePath = kDirectoryPath + chunkName + "/" + chunkName + "_" + groupName + ".json";
		std::ifstream ifs;
		ifs.open(filePath);

		if (ifs.fail()) {
#ifdef _DEBUG
			std::string message = "Failed open data file file for read";
			MessageBoxA(nullptr, message.c_str(), "GlobalVariables", 0);
#endif // _DEBUG
			assert(0);
			return;
		}

		nlohmann::json root;
		ifs >> root;
		ifs.close();
		nlohmann::json::iterator itGroup = root.find(groupName);
		assert(itGroup != root.end());

		std::vector<std::string> treeNames(kMaxTreeNum_, "_");
		RootToSetValue(chunkName, groupName, itGroup, treeNames);
	}

	void GlobalVariables::AddComboName(const std::string& key, const std::string& comboName)
	{
		SetValue(kGlobalCombo, key, comboName, comboName, kUnderBar);
		SetComboName(key, comboName);
	}

	const std::map<std::string, std::vector<std::string>>* GlobalVariables::GetComboNameMap() const
	{
		return &comboNames_;
	}

	void GlobalVariables::DrawImGuiCombo(const std::string& key, const std::string& type, std::string* ptr)
	{
#ifdef _DEBUG
		const std::vector<std::string>& comboList = comboNames_[type];
		int currentItem = 0;

		// 現在の値に一致するインデックスを取得しますの
		for (int i = 0; i < static_cast<int>(comboList.size()); ++i) {
			if (comboList[i] == *ptr) {
				currentItem = i;
				break;
			}
		}

		// 現在の選択名を表示するためのプレビューラベル
		const std::string& previewLabel = comboList.empty() ? "" : comboList[currentItem];
		
		if (ImGui::BeginCombo(key.c_str(), previewLabel.c_str())) {
			ImGui::InputText("検索", filterName, IM_ARRAYSIZE(filterName));
			for (int n = 0; n < static_cast<int>(comboList.size()); ++n) {
				const std::string& name = comboList[n];

				// 検索ワードが空でない場合、部分一致していなければスキップ
				if (std::strlen(filterName) > 0 &&
					name.find(filterName) == std::string::npos) {
					continue;
				}

				bool isSelected = (currentItem == n);
				if (ImGui::Selectable(comboList[n].c_str(), isSelected)) {
					currentItem = n;
					*ptr = comboList[n]; // 新しい選択を保存いたしますわ
				}
				if (isSelected) {
					ImGui::SetItemDefaultFocus(); // デフォルトでフォーカスを当てておきますの
				}
			}
			ImGui::EndCombo();
		}
#else
		(void)key; (void)type; (void)ptr;
#endif // _DEBUG
	}


	std::string GlobalVariables::GetAfterName(const std::string& itemName, const std::string& findName)
	{
		return itemName.substr(findName.length());
	}

	void GlobalVariables::SetComboName(const std::string& key, const std::string& comboName)
	{
		bool isBe = false;
		for (std::string& name : comboNames_[key]) {
			if (name == comboName) {
				isBe = true;
				break;
			}
		}
		if (!isBe) {
			comboNames_[key].push_back(comboName);
		}
	}

	void GlobalVariables::ItemToRoot(nlohmann::json& root, Item& item, const std::string& key, const std::vector<std::string>& treeNames, uint32_t level)
	{
		if (treeNames[level] == "_") {
			if (std::holds_alternative<int32_t>(item)) {
				root[key] = std::get<int32_t>(item);
			}
			else if (std::holds_alternative<float>(item)) {
				root[key] = std::get<float>(item);
			}
			else if (std::holds_alternative<Vector2>(item)) {
				Vector2 value = std::get<Vector2>(item);
				root[key] = nlohmann::json::array({ value.x, value.y });
			}
			else if (std::holds_alternative<Vector3>(item)) {
				Vector3 value = std::get<Vector3>(item);
				root[key] = nlohmann::json::array({ value.x, value.y, value.z });
			}
			else if (std::holds_alternative<Vector4>(item)) {
				Vector4 value = std::get<Vector4>(item);
				root[key] = nlohmann::json::array({ value.x, value.y, value.z, value.w });
			}
			else if (std::holds_alternative<bool>(item)) {
				root[key] = std::get<bool>(item);
			}
			else if (std::holds_alternative<std::string>(item)) {
				root[key] = std::get<std::string>(item);
			}
		}
		else {
			if (!root[treeNames[level]].is_object()) {
				root[treeNames[level]] = nlohmann::json::object();
			}
			ItemToRoot(root[treeNames[level]], item, key, treeNames, level + 1);
		}
	}

	void GlobalVariables::MakeTreeNames(std::string& key, std::vector<std::string>& treeNames, uint32_t level)
	{
		size_t pos = key.find(kTreeName_[level]);
		if (pos != std::string::npos) {
			size_t underscorePos = key.find("_", pos + 5);
			treeNames[level] = key.substr(pos + 5, underscorePos - pos - 5);

			key = key.substr(underscorePos + 1);
			MakeTreeNames(key, treeNames, level + 1);
		}
	}

	void GlobalVariables::RootToSetValue(const std::string& chunkName, const std::string& groupName, nlohmann::json::iterator& itGroup, const std::vector<std::string>& treeNames, uint32_t level)
	{
		for (nlohmann::json::iterator itItem = itGroup->begin(); itItem != itGroup->end(); ++itItem) {
			const std::string& itemName = itItem.key();
			if (itItem->is_object()) {
				std::vector<std::string> tNames = treeNames;
				tNames[level] = itemName;
				RootToSetValue(chunkName, groupName, itItem, tNames, level + 1);
			}
			else {
				if (itItem->is_number_integer()) {
					int32_t value = itItem->get<int32_t>();
					SetValue(chunkName, groupName, itemName, value, treeNames);
				}
				else if (itItem->is_number_float()) {
					double value = itItem->get<double>();
					SetValue(chunkName, groupName, itemName, static_cast<float>(value), treeNames);
				}
				else if (itItem->is_array() && itItem->size() == 2) {
					Vector2 value = { itItem->at(0), itItem->at(1) };
					SetValue(chunkName, groupName, itemName, value, treeNames);
				}
				else if (itItem->is_array() && itItem->size() == 3) {
					Vector3 value = { itItem->at(0), itItem->at(1), itItem->at(2) };
					SetValue(chunkName, groupName, itemName, value, treeNames);
				}
				else if (itItem->is_array() && itItem->size() == 4) {
					Vector4 value = { itItem->at(0), itItem->at(1), itItem->at(2), itItem->at(3) };
					SetValue(chunkName, groupName, itemName, value, treeNames);
				}
				else if (itItem->is_boolean()) {
					bool value = itItem->get<bool>();
					SetValue(chunkName, groupName, itemName, value, treeNames);
				}
				else if (itItem->is_string()) {
					std::string value = itItem->get<std::string>();
					SetValue(chunkName, groupName, itemName, value, treeNames);
					if (chunkName == kGlobalCombo) {
						SetComboName(groupName, value);
					}
				}
			}
		}
	}

#ifdef _DEBUG
	void GlobalVariables::MakeTreeMap(const std::string& chunkName, const std::string& groupName, std::map<std::string, std::map<std::string, std::map<std::string, std::map<std::string, std::map<std::string, std::map<std::string, GroupPtr>>>>>>& treeMap, Item& item, const std::string& itemName, std::vector<std::string>& treeNames, uint32_t level)
	{
		size_t pos = itemName.find(kTreeName_[level]);
		std::string text = itemName;
		if (pos != std::string::npos) {
			size_t underscorePos = itemName.find("_", pos + 5);
			treeNames[level] = itemName.substr(pos + 5, underscorePos - pos - 5);

			text = itemName.substr(underscorePos + 1);
			level++;
			pos = text.find(kTreeName_[level]);
			if (pos != std::string::npos) {
				underscorePos = text.find("_", pos + 5);
				treeNames[level] = text.substr(pos + 5, underscorePos - pos - 5);

				text = text.substr(underscorePos + 1);
				level++;
				MakeTreeMap(chunkName, groupName, treeMap, item, text, treeNames, level);
			}
			else {
				treeMap[treeNames[0]][treeNames[1]][treeNames[2]][treeNames[3]][treeNames[4]][treeNames[5]][text] = &item;
				std::string openTreeName;
				for (uint32_t i = 0; i < level; i++) {
					if (i != 0) {
						openTreeName += "_";
					}
					openTreeName += kTreeName_[i] + treeNames[i];
				}
				isTreeOpen_[chunkName][groupName][openTreeName] = false;
			}
		}
		else if (level == 0) {
			PreparationImGui(itemName, item, chunkName + groupName + itemName);
		}
		else {
			treeMap[treeNames[0]][treeNames[1]][treeNames[2]][treeNames[3]][treeNames[4]][treeNames[5]][text] = &item;
			std::string openTreeName;
			for (uint32_t i = 0; i < level; i++) {
				if (i != 0) {
					openTreeName += "_";
				}
				openTreeName += kTreeName_[i] + treeNames[i];
			}
			isTreeOpen_[chunkName][groupName][openTreeName] = false;
		}
	}

	template<typename T>
	void GlobalVariables::DrawTreeImGui(T& tree, const std::string& chunkName, const std::string& groupName, const std::string& treeName, uint32_t level)
	{
		for (auto it = tree.begin(); it != tree.end(); ++it) {
			const std::string& key = it->first;
			if (key == "_") {
				DrawTreeImGui(it->second, chunkName, groupName, treeName + "_" + kTreeName_[level] + key, level + 1);
			}
			else {
				if (ImGui::TreeNode(key.c_str())) {
					isTreeOpen_[chunkName][groupName][treeName + "_" + kTreeName_[level] + key] = true;
					DrawTreeImGui(it->second, chunkName, groupName, treeName + "_" + kTreeName_[level] + key, level + 1);
					ImGui::TreePop();
				}
			}
		}
	}
	template <>
	void GlobalVariables::DrawTreeImGui<std::map<std::string, GlobalVariables::Item*>>(std::map<std::string, Item*>& tree, const std::string& chunkName, const std::string& groupName, const std::string& treeName, uint32_t level)
	{
		if (level == 10 && chunkName == treeName && treeName == groupName) {}
		for (std::map<std::string, Item*>::iterator it = tree.begin(); it != tree.end(); ++it) {
			std::string debugName = chunkName + groupName + treeName + it->first;
			PreparationImGui(it->first, *it->second, debugName);
		}
	}

	void GlobalVariables::PreparationImGui(const std::string& itemName, Item& item, const std::string& debugName)
	{
		if (itemName.find(kColorName) == 0) {
			Vector4* ptr = std::get_if<Vector4>(&item);
			ImGui::ColorEdit4(GetAfterName(itemName, kColorName).c_str(), reinterpret_cast<float*>(ptr));
		}
		else if (itemName.find(kComboName) == 0) {
			size_t keyStart = itemName.find(kComboName);
			keyStart += kComboName.length();  // keyの開始位置

			size_t keyEnd = itemName.find(kComboTypeName, keyStart);

			std::string key = itemName.substr(keyStart, keyEnd - keyStart);  // key部分を抽出
			std::string type = itemName.substr(keyEnd + kComboTypeName.length());  // type部分を抽出

			int currentItem = 0;
			int i = 0;
			std::string* ptr = std::get_if<std::string>(&item);
			const std::vector<std::string>& comboList = comboNames_[type];

			// 現在の選択位置を取得
			for (const std::string& name : comboList) {
				if (name == *ptr) {
					currentItem = i;
					break;
				}
				i++;
			}

			const std::string& previewLabel = comboList.empty() ? "" : comboList[currentItem];

			if (ImGui::BeginCombo(key.c_str(), previewLabel.c_str())) {
				ImGui::InputText("検索", filterName, IM_ARRAYSIZE(filterName));

				for (int n = 0; n < static_cast<int>(comboList.size()); ++n) {
					const std::string& name = comboList[n];

					// 検索ワードが空でない場合、部分一致していなければスキップ
					if (std::strlen(filterName) > 0 &&
						name.find(filterName) == std::string::npos) {
						continue;
					}

					bool isSelected = (currentItem == n);
					if (ImGui::Selectable(name.c_str(), isSelected)) {
						currentItem = n;
						*ptr = name;  // 選択した値を反映
						break;
					}
					if (isSelected) {
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}
		}
		else if (std::holds_alternative<int32_t>(item)) {
			int32_t* ptr = std::get_if<int32_t>(&item);
			//int32_t* ptr = std::get_if<int32_t>(&tempData_[debugName]);
			(void)debugName;
			ImGui::DragInt(itemName.c_str(), ptr, 1);
			/*if (ImGui::IsItemDeactivatedAfterEdit()) {
				item = tempData_[debugName];
			}*/
		}
		else if (std::holds_alternative<float>(item)) {
			float* ptr = std::get_if<float>(&item);
			ImGui::DragFloat(itemName.c_str(), ptr, 0.01f);
		}
		else if (std::holds_alternative<Vector2>(item)) {
			Vector2* ptr = std::get_if<Vector2>(&item);
			ImGui::DragFloat2(itemName.c_str(), reinterpret_cast<float*>(ptr), 0.01f);
		}
		else if (std::holds_alternative<Vector3>(item)) {
			Vector3* ptr = std::get_if<Vector3>(&item);
			ImGui::DragFloat3(itemName.c_str(), reinterpret_cast<float*>(ptr), 0.01f);
		}
		else if (std::holds_alternative<bool>(item)) {
			bool* ptr = std::get_if<bool>(&item);
			ImGui::Checkbox(itemName.c_str(), ptr);
		}
		else if (std::holds_alternative<Vector4>(item)) {
			Vector4* ptr = std::get_if<Vector4>(&item);
			ImGui::DragFloat4(itemName.c_str(), reinterpret_cast<float*>(ptr), 0.01f);
		}
		else if (std::holds_alternative<std::string>(item)) {
			std::string* ptr = std::get_if<std::string>(&item);
			std::string text = itemName + ":" + (*ptr);
			ImGui::Text(text.c_str());
		}
	}
#endif // _DEBUG
}