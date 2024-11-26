#pragma once
#include <string>
enum class StageObjectType;
class BaseStageObject;

class StageObjectFactory
{
public:
	static BaseStageObject* CreateStageObject(const StageObjectType& type, const std::string& mainName, const std::string& name, const uint32_t& no);
};