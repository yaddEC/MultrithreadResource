#include <ResourceManager.h>



void ResourceManager::Delete(const std::string& name)
{
	resources.erase(name);
}