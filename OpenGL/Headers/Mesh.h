#pragma once
#include <Model.h>
#include <Maths.h>

using namespace Resources;

namespace LowRenderer
{
	class Mesh
	{
		private:
		Model* model;
		Mat4 modelMatrix;
		public:

			Mesh(Model* model, const Mat4& mat);
			~Mesh();
			void Update( Mat4& projviewMatrix, unsigned int shaderProgram);
	};
}