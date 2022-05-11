#pragma once
#include <Log.h>
#include <iostream>
#include <unordered_map>
#include <IResource.h>
using namespace std;
using namespace Resources;

class ResourceManager {
public:
	template <typename T>
	void  Create(const std::string& name)
	{
		auto found = resources.find(name);
		if (found != resources.end())
			Delete(name);

		T* resource_instance = new T;
		IResource* resource_base = dynamic_cast<IResource*>(resource_instance);
		resource_base->Load(name);
		resources.try_emplace(name, resource_base);
	}

	template <typename T>
	 T* Get(const std::string& name)
	{
		auto found =  resources.find(name);
		if (found != resources.end())
			return  dynamic_cast<T*>(found->second);
		else
			return nullptr;
	}

	void Delete(const std::string& name);

private:
	std::unordered_map<std::string, IResource*> resources;
};