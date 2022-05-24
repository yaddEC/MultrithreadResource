#include <Mesh.h>

using namespace LowRenderer;

Mesh::Mesh(Model* model, const Mat4& mat)
{
	this->model = model;
	this->modelMatrix = mat;
}

void Mesh::Update(Mat4& projviewMatrix, unsigned int shaderProgram)
{
	glUseProgram(shaderProgram);
	unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");

	Mat4 transformMatrix = projviewMatrix * modelMatrix;
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, transformMatrix.mat);
	unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, modelMatrix.mat);
	// render
// ------

	// draw our first triangle
	glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0); // set it manually
	glUniform1i(glGetUniformLocation(shaderProgram, "texture2"), 1); // set it manually

	glBindVertexArray(model->vao.vao); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glDrawElements(GL_TRIANGLES, model->vertices.size(), GL_UNSIGNED_INT, 0);
}