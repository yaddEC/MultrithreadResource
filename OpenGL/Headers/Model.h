#pragma once
#include <IResource.h>
#include <Maths.h>
#include <vector>
#include <iostream>
using namespace Core::Maths;
using namespace std;
namespace Resources
{
	struct Vertex
	{
		public:
			Vec3 position;
			Vec3 normal;
			Vec2 textureUV;
	};

	class Model : public IResource
	{
		public:
			vector <Vertex> vertices;
			vector <uint32_t> indexes;
			void Load(const std::string& path) override ;
			void Print();
	};

}
