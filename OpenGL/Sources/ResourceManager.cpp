#include "ResourceManager.h"

void ResourceManager::Delete(const std::string& name)
{
	auto iter = resources.find(name);
	if (iter != resources.end())
	{
		resources.erase(name);
	}
}

void ResourceManager::Unload()
{
	for (auto i : resources)
	{
		delete i.second;
		i.second = nullptr;
	}
	resources.clear();
}