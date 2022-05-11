#include <ResourceManager.h>

template <typename T>
void  ResourceManager::Create(const std::string& name)
{
	//auto found = resources.find(name);
	//if (found != resources.end()) 
		//Delete(name);
	
	//T* resource_instance = new T;
	//IResource* resource_base = dynamic_cast<IResource*>(resource_instance);
	//resource_base->load(name);
	//resources.emplace(name, resource_base);
}

template <typename T>
const T& ResourceManager::Get(const std::string& name)
{
	auto found = resources.find(name);
	if (found != resources.end())
		return found->second;
	else
		return nullptr;
}

void ResourceManager::Delete(const std::string& name)
{
	resources.erase(name);
}