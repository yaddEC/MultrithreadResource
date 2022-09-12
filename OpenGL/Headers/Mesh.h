#pragma once
#include <Model.h>
#include <Maths.h>

using namespace Resources;

namespace LowRenderer
{
	class Mesh
	{
	private:
		Mat4 modelMatrix;
	public:
		Model* model;
		GLuint texture;
		unsigned char* data;
		int width;
		int height;
		int nrChannels;
		Mesh(Model* model, const Mat4& mat, const char* file);
		~Mesh();
		void Draw(Mat4& projviewMatrix, unsigned int shaderProgram);
		//----(o.luanda)-----------------
		void InitTextureOpenGL();


	};
}