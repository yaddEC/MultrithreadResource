#pragma once
#include <string>
namespace Resources
{
    class IResource
    {
    public:
		IResource() {  }
        virtual void Load(const std::string& path) {  }
		virtual ~IResource() {  }
    };
     
}

