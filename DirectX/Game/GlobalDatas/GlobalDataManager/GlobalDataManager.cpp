#include "GlobalDatas/GlobalDataManager/GlobalDataManager.h"


GlobalDataManager* GlobalDataManager::GetInstance()
{
	static GlobalDataManager instance;
	return &instance;
}

void GlobalDataManager::Initialize()
{
}

void GlobalDataManager::Update()
{
}

void GlobalDataManager::Draw()
{
}

void GlobalDataManager::AddTypes()
{
}
