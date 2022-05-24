#pragma once
#include<Maths.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>


using namespace Core::Maths;
using namespace std;
namespace LowRenderer
{
	class Light
	{
	public:
		Vec3 ambient;
		Vec3 diffuse;
		Vec3 specular;
		int number;
		virtual void Update(int shaderProgram)=0;

	};
	class DirectionalLight : public Light
	{
	public:
		DirectionalLight() {}
		Vec3 direction;
		DirectionalLight(Vec3 ambient, Vec3 diffuse, Vec3 specular, Vec3 direction);
		void Update(int shaderProgram) override;
	};

	class PointLight :public Light
	{
	public:
		Vec3 position;
		float constant;
		float linear;
		float quadratic;
		PointLight(Vec3 position, Vec3 ambient, Vec3 diffuse, Vec3 specular, float constant,float linear,float quadratic);
		void Update(int shaderProgram) override;

	};

	
	class SpotLight :public Light
	{
	public:
		Vec3 position;
		Vec3 direction;
		float constant;
		float linear;
		float quadratic;
		float cutoff;
		float ocutoff;
		SpotLight(Vec3 position, Vec3 direction, Vec3 ambient, Vec3 diffuse, Vec3 specular, float constant, float linear, float quadratic,float cutoff, float ocutoff);
		void Update(int shaderProgram) override;

	};

}