#pragma once
#include <iostream>
#include <unordered_map>
#include <Log.h>
#include <IResource.h>
using namespace std;
using namespace Resources;

class ResourceManager {
public:

	template <typename T>
	void Create(const std::string& name) {
		ASSERT(std::is_base_of<IResource, T>::value, "ya po dheritage lo");

		auto found = resources.find(name);
		if (found != resources.end()) {
			Delete(name);
		}
		T* resource_instance = new T;
		IResource* resource_base = dynamic_cast<IResource*>(resource_instance);
		resource_base->load(name);
		resources.emplace(name, resource_base);
	}

	template <typename T>
	const T& Get(const std::string& name)
	{
		auto found = resources.find(name);
		if (found != resources.end())
			return *found->second;
		else
			return nullptr;
	}

	void Delete(const std::string& name)
	{
		resources.erase(name);
	}

private:
	std::unordered_map<std::string, IResource> resources;

};