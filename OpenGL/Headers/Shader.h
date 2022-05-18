#pragma once
#include <IResource.h>
#include <Maths.h>
#include <filesystem>
#include <iostream>
using namespace Core::Maths;
using namespace std;
namespace Resources
{

	class Shader : public IResource
	{
	public:
		Shader() {  }
		bool SetVertexShader(std::filesystem::path const& filename);
		bool SetFragmentShader(std::filesystem::path const& filename);
		bool Link();
		void Load(const std::string& path) {  }
		int fragmentShader;
		int vertexShader;
		int shaderProgram;
	};

}
