#include "BaseEditor.h"

void BaseEditor::AddComboName(ComboNameType type, const std::string& comboName)
{
	global_->AddComboName(type, comboName);
}

void BaseEditor::AddItem(const std::string& key, int32_t value, const std::string& tree2, const std::string& tree3, const std::string& tree4, const std::string& tree5, const std::string& tree6)
{
	global_->AddItem(key, value, tree2, tree3, tree4, tree5, tree6);
}

void BaseEditor::AddItem(const std::string& key, float value, const std::string& tree2, const std::string& tree3, const std::string& tree4, const std::string& tree5, const std::string& tree6)
{
	global_->AddItem(key, value, tree2, tree3, tree4, tree5, tree6);
}

void BaseEditor::AddItem(const std::string& key, const Vector2& value, const std::string& tree2, const std::string& tree3, const std::string& tree4, const std::string& tree5, const std::string& tree6)
{
	global_->AddItem(key, value, tree2, tree3, tree4, tree5, tree6);
}

void BaseEditor::AddItem(const std::string& key, const Vector3& value, const std::string& tree2, const std::string& tree3, const std::string& tree4, const std::string& tree5, const std::string& tree6)
{
	global_->AddItem(key, value, tree2, tree3, tree4, tree5, tree6);
}

void BaseEditor::AddItem(const std::string& key, const Vector4& value, const std::string& tree2, const std::string& tree3, const std::string& tree4, const std::string& tree5, const std::string& tree6)
{
	global_->AddItem(key, value, tree2, tree3, tree4, tree5, tree6);
}

void BaseEditor::AddItem(const std::string& key, bool value, const std::string& tree2, const std::string& tree3, const std::string& tree4, const std::string& tree5, const std::string& tree6)
{
	global_->AddItem(key, value, tree2, tree3, tree4, tree5, tree6);
}

void BaseEditor::AddItem(const std::string& key, const std::string& value, const std::string& tree2, const std::string& tree3, const std::string& tree4, const std::string& tree5, const std::string& tree6)
{
	global_->AddItem(key, value, tree2, tree3, tree4, tree5, tree6);
}

void BaseEditor::AddItemColor(const std::string& key, const Vector4& value, const std::string& tree2, const std::string& tree3, const std::string& tree4, const std::string& tree5, const std::string& tree6)
{
	global_->AddItemColor(key, value, tree2, tree3, tree4, tree5, tree6);
}

void BaseEditor::AddItemCombo(const std::string& key, ComboNameType type, const std::string& tree2, const std::string& tree3, const std::string& tree4, const std::string& tree5, const std::string& tree6)
{
	global_->AddItemCombo(key, type, tree2, tree3, tree4, tree5, tree6);
}

void BaseEditor::AddItemCombo(const std::string& key, const std::string& type, const std::string& tree2, const std::string& tree3, const std::string& tree4, const std::string& tree5, const std::string& tree6)
{
	global_->AddItemCombo(key, type, tree2, tree3, tree4, tree5, tree6);
}

int32_t BaseEditor::GetIntValue(const std::string& key, const std::string& tree2, const std::string& tree3, const std::string& tree4, const std::string& tree5, const std::string& tree6) const
{
	return global_->GetIntValue(key, tree2, tree3, tree4, tree5, tree6);
}

float BaseEditor::GetFloatValue(const std::string& key, const std::string& tree2, const std::string& tree3, const std::string& tree4, const std::string& tree5, const std::string& tree6) const
{
	return global_->GetFloatValue(key, tree2, tree3, tree4, tree5, tree6);
}

const Vector2& BaseEditor::GetVector2Value(const std::string& key, const std::string& tree2, const std::string& tree3, const std::string& tree4, const std::string& tree5, const std::string& tree6) const
{
	return global_->GetVector2Value(key, tree2, tree3, tree4, tree5, tree6);
}

const Vector3& BaseEditor::GetVector3Value(const std::string& key, const std::string& tree2, const std::string& tree3, const std::string& tree4, const std::string& tree5, const std::string& tree6) const
{
	return global_->GetVector3Value(key, tree2, tree3, tree4, tree5, tree6);
}

const Vector4& BaseEditor::GetVector4Value(const std::string& key, const std::string& tree2, const std::string& tree3, const std::string& tree4, const std::string& tree5, const std::string& tree6) const
{
	return global_->GetVector4Value(key, tree2, tree3, tree4, tree5, tree6);
}

bool BaseEditor::GetBoolValue(const std::string& key, const std::string& tree2, const std::string& tree3, const std::string& tree4, const std::string& tree5, const std::string& tree6) const
{
	return global_->GetBoolValue(key, tree2, tree3, tree4, tree5, tree6);
}

const std::string& BaseEditor::GetStringValue(const std::string& key, const std::string& tree2, const std::string& tree3, const std::string& tree4, const std::string& tree5, const std::string& tree6) const
{
	return global_->GetStringValue(key, tree2, tree3, tree4, tree5, tree6);
}

const Vector4& BaseEditor::GetColor(const std::string& key, const std::string& tree2, const std::string& tree3, const std::string& tree4, const std::string& tree5, const std::string& tree6) const
{
	return global_->GetColor(key, tree2, tree3, tree4, tree5, tree6);
}

const std::string& BaseEditor::GetCombo(const std::string& key, const std::string& type, const std::string& tree2, const std::string& tree3, const std::string& tree4, const std::string& tree5, const std::string& tree6) const
{
	return global_->GetCombo(key, type, tree2, tree3, tree4, tree5, tree6);
}

const std::string& BaseEditor::GetCombo(const std::string& key, ComboNameType type, const std::string& tree2, const std::string& tree3, const std::string& tree4, const std::string& tree5, const std::string& tree6) const
{
	return global_->GetCombo(key, type, tree2, tree3, tree4, tree5, tree6);
}

void BaseEditor::SetVariable(const std::string& key, int32_t value, const std::string& tree2, const std::string& tree3, const std::string& tree4, const std::string& tree5, const std::string& tree6)
{
	global_->SetVariable(key, value, tree2, tree3, tree4, tree5, tree6);
}

void BaseEditor::SetVariable(const std::string& key, float value, const std::string& tree2, const std::string& tree3, const std::string& tree4, const std::string& tree5, const std::string& tree6)
{
	global_->SetVariable(key, value, tree2, tree3, tree4, tree5, tree6);
}

void BaseEditor::SetVariable(const std::string& key, const Vector2& value, const std::string& tree2, const std::string& tree3, const std::string& tree4, const std::string& tree5, const std::string& tree6)
{
	global_->SetVariable(key, value, tree2, tree3, tree4, tree5, tree6);
}

void BaseEditor::SetVariable(const std::string& key, const Vector3& value, const std::string& tree2, const std::string& tree3, const std::string& tree4, const std::string& tree5, const std::string& tree6)
{
	global_->SetVariable(key, value, tree2, tree3, tree4, tree5, tree6);
}

void BaseEditor::SetVariable(const std::string& key, const Vector4& value, const std::string& tree2, const std::string& tree3, const std::string& tree4, const std::string& tree5, const std::string& tree6)
{
	global_->SetVariable(key, value, tree2, tree3, tree4, tree5, tree6);
}

void BaseEditor::SetVariable(const std::string& key, bool value, const std::string& tree2, const std::string& tree3, const std::string& tree4, const std::string& tree5, const std::string& tree6)
{
	global_->SetVariable(key, value, tree2, tree3, tree4, tree5, tree6);
}

void BaseEditor::SetVariable(const std::string& key, const std::string& value, const std::string& tree2, const std::string& tree3, const std::string& tree4, const std::string& tree5, const std::string& tree6)
{
	global_->SetVariable(key, value, tree2, tree3, tree4, tree5, tree6);
}

bool BaseEditor::IsTreeOpen(const std::string& tree2, const std::string& tree3, const std::string& tree4, const std::string& tree5, const std::string& tree6)
{
	return global_->IsTreeOpen(tree2, tree3, tree4, tree5, tree6);
}

bool BaseEditor::IsTreeOpen(int treeNo)
{
	return global_->IsTreeOpen(treeNo);
}

