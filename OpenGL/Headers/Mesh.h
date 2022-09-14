#pragma once
#include <Model.h>
#include <Maths.h>

using namespace Resources;

namespace LowRenderer
{
	class Mesh
	{
	private:
	public:
		Mat4 modelMatrix;
		Model* model;
		GLuint texture;
		unsigned char* data;
		int width;
		int height;
		int nrChannels;
		Mesh(Model* model, const Mat4& mat, const char* file);
		~Mesh();
		void Draw(Mat4& projviewMatrix, unsigned int shaderProgram);
		
		void InitTextureOpenGL();


	};
}