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

	

	class Buffer {
	private:
	public:
		unsigned int buffer;
		Buffer(const void* data, unsigned int size);
		Buffer();
		~Buffer();
		void bind();
		void unbind();
	};


	class VertexAttributes
	{
		public:
		unsigned int vao;
		VertexAttributes();
		~VertexAttributes();
		void Load(vector <Vertex> vertices, vector <uint32_t> indexes, Buffer vbo, Buffer ebo);
		void bind();
		void unbind();

	};
	class Model : public IResource
	{
	public:
		vector <Vertex> vertices;
		vector <uint32_t> indexes;
		VertexAttributes vao;
		Buffer ebo;
		Buffer vbo;
		void Load(const std::string& path) override;
		void Print();
	};
}
