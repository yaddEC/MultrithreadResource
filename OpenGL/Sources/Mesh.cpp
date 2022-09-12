#include <Mesh.h>
#define STB_IMAGE_IMPLEMENTATION
#include <STB_Image/stb_image.h>

using namespace LowRenderer;



Mesh::Mesh(Model* model, const Mat4& mat, const char* file)
{
	this->model = model;
	this->modelMatrix = mat;
	//int width, height, nrChannels;
	//stbi_set_flip_vertically_on_load(true);
	data = stbi_load(file, &width, &height, &nrChannels, 0);

}

void Mesh::Draw(Mat4& projviewMatrix, unsigned int shaderProgram)
{
	if (model->modelDrawable)
	{
		glUseProgram(shaderProgram);
		unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");

		Mat4 transformMatrix = projviewMatrix * modelMatrix;
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, transformMatrix.mat);
		unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, modelMatrix.mat);
#if 1 //(o.luanda)
		glBindTexture(GL_TEXTURE_2D, texture);
#endif

		glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
		glBindVertexArray(model->vao.vao);
		glDrawElements(GL_TRIANGLES, model->vertices.size(), GL_UNSIGNED_INT, 0);

	}

#if 0 
	glBindTextureUnit(0, texture);
#endif

}

void Mesh::InitTextureOpenGL()
{
	if (!data)
	{
		return;
	}
	//(o.luanda) : format
	int format = GL_RGB;
	if (nrChannels == 4)
	{
		format = GL_RGBA;
	}
	//(o.luanda) : format

	//(o.luanda)
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);

}