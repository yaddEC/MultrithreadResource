#include <Light.h>

using namespace LowRenderer;
using namespace Core::Maths;
static int nbrOfDir = 0;
static int nbrOfPoint = 0;
static int nbrOfSpot = 0;
DirectionalLight::DirectionalLight(Vec3 ambient, Vec3 diffuse, Vec3 specular, Vec3 direction)
{
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->direction = direction;
	number = nbrOfDir;
	nbrOfDir++;
}

void DirectionalLight::Update(int shaderProgram)
{

	glUseProgram(shaderProgram);
	unsigned int directionLoc = glGetUniformLocation(shaderProgram, ("dirLights[" + to_string(number) + "].direction").c_str());
	glUniform3f(directionLoc, direction.x, direction.y, direction.z);
	unsigned int ambientLoc = glGetUniformLocation(shaderProgram, ("dirLights[" + to_string(number) + "].ambient").c_str());
	glUniform3f(ambientLoc, ambient.x, ambient.y, ambient.z);
	unsigned int diffuseLoc = glGetUniformLocation(shaderProgram, ("dirLights[" + to_string(number) + "].diffuse").c_str());
	glUniform3f(diffuseLoc, diffuse.x, diffuse.y, diffuse.z);
	unsigned int specularLoc = glGetUniformLocation(shaderProgram, ("dirLights[" + to_string(number) + "].specular").c_str());
	glUniform3f(specularLoc, specular.x, specular.y, specular.z);

}

PointLight::PointLight(Vec3 position, Vec3 ambient, Vec3 diffuse, Vec3 specular, float constant, float linear, float quadratic)
{
	this->position = position;
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->constant = constant;
	this->linear = linear;
	this->quadratic = quadratic;
	number = nbrOfPoint;
	nbrOfPoint++;
}

void PointLight::Update(int shaderProgram)
{

	glUseProgram(shaderProgram);

	unsigned int ambientLoc = glGetUniformLocation(shaderProgram, ("pointLights[" + to_string(number) + "].ambient").c_str());
	glUniform3f(ambientLoc, ambient.x, ambient.y, ambient.z);
	unsigned int diffuseLoc = glGetUniformLocation(shaderProgram, ("pointLights[" + to_string(number) + "].diffuse").c_str());
	glUniform3f(diffuseLoc, diffuse.x, diffuse.y, diffuse.z);
	unsigned int specularLoc = glGetUniformLocation(shaderProgram, ("pointLights[" + to_string(number) + "].specular").c_str());
	glUniform3f(specularLoc, specular.x, specular.y, specular.z);
	unsigned int positionLoc = glGetUniformLocation(shaderProgram, ("pointLights[" + to_string(number) + "].position").c_str());
	glUniform3f(positionLoc, position.x, position.y, position.z);
	unsigned int constantLoc = glGetUniformLocation(shaderProgram, ("pointLights[" + to_string(number) + "].constant").c_str());
	glUniform1f(constantLoc, constant);
	unsigned int linearLoc = glGetUniformLocation(shaderProgram, ("pointLights[" + to_string(number) + "].linear").c_str());
	glUniform1f(linearLoc, linear);
	unsigned int quadraticLoc = glGetUniformLocation(shaderProgram, ("pointLights[" + to_string(number) + "].quadratic").c_str());
	glUniform1f(quadraticLoc, quadratic);


}

SpotLight::SpotLight(Vec3 position, Vec3 direction, Vec3 ambient, Vec3 diffuse, Vec3 specular, float constant, float linear, float quadratic, float cutoff, float ocutoff)
{
	this->position = position;
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->constant = constant;
	this->linear = linear;
	this->direction = direction;
	this->quadratic = quadratic;
	this->cutoff = cutoff;
	this->ocutoff = ocutoff;
	number = nbrOfSpot;
	nbrOfSpot++;
}

void SpotLight::Update(int shaderProgram)
{
	
	glUseProgram(shaderProgram);

	unsigned int ambientLoc = glGetUniformLocation(shaderProgram, ("spotLights[" + to_string(number) + "].ambient").c_str());
	glUniform3f(ambientLoc, ambient.x, ambient.y, ambient.z);
	unsigned int directionLoc = glGetUniformLocation(shaderProgram, ("spotLights[" + to_string(number) + "].direction").c_str());
	glUniform3f(directionLoc, direction.x, direction.y, direction.z);
	unsigned int diffuseLoc = glGetUniformLocation(shaderProgram, ("spotLights[" + to_string(number) + "].diffuse").c_str());
	glUniform3f(diffuseLoc, diffuse.x, diffuse.y, diffuse.z);
	unsigned int specularLoc = glGetUniformLocation(shaderProgram, ("spotLights[" + to_string(number) + "].specular").c_str());
	glUniform3f(specularLoc, specular.x, specular.y, specular.z);
	unsigned int positionLoc = glGetUniformLocation(shaderProgram, ("spotLights[" + to_string(number) + "].position").c_str());
	glUniform3f(positionLoc, position.x, position.y, position.z);
	unsigned int constantLoc = glGetUniformLocation(shaderProgram, ("spotLights[" + to_string(number) + "].constant").c_str());
	glUniform1f(constantLoc, constant);
	unsigned int linearLoc = glGetUniformLocation(shaderProgram, ("spotLights[" + to_string(number) + "].linear").c_str());
	glUniform1f(linearLoc, linear);
	unsigned int quadraticLoc = glGetUniformLocation(shaderProgram, ("spotLights[" + to_string(number) + "].quadratic").c_str());
	glUniform1f(quadraticLoc, quadratic);
	unsigned int cutoffLoc = glGetUniformLocation(shaderProgram, ("spotLights[" + to_string(number) + "].cutOff").c_str());
	glUniform1f(cutoffLoc, cutoff);
	unsigned int ocutoffLoc = glGetUniformLocation(shaderProgram, ("spotLights[" + to_string(number) + "].OuterCutOff").c_str());
	glUniform1f(ocutoffLoc, ocutoff);

}