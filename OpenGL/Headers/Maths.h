#pragma once
#include "math.h"
namespace Core
{
	namespace Maths
	{
	#define M_PI 3.14159265358979323846
		class Vec2
		{
		public:
			Vec2();
			Vec2(float a, float b);
			float x;
			float y;
			void Print();
			float GetMagnitude();
			Vec2 Normalize();
			~Vec2();
		};

		class Vec3
		{
		public:
			Vec3();
			Vec3(float a, float b, float c);
			float x;
			float y;
			float z;
			void Print();
			float GetMagnitude();
			Vec3 Normalize();
			~Vec3();
		};
		float dot(const Vec3& a, const Vec3& b);
		float operator*(const Vec3& a, const Vec3& b);
		Vec3 operator+(const Vec3& a, const Vec3& b);
		Vec3 operator-(const Vec3& a, const Vec3& b);
		Vec3 operator*(const Vec3& b, const float& a);
		Vec3 operator*(const float& a, const Vec3& b);
		Vec3 CrossProduct(const Vec3& a, const Vec3& b);

		class Vec4
		{
		public:
			Vec4();
			Vec4(float a, float b, float c, float d);
			float x;
			float y;
			float z;
			float w;

			void Print();
			void Homogenize();
			Vec3 GetHomogenize();
			float GetMagnitude();
			void Normalize();
			Vec4 operator+(const Vec4& rhs);
			Vec4 operator*(const float& rhs);
			Vec4(const Vec3& vec3, float _w = 1.0f);
			~Vec4();
		};


		class Mat3
		{
		public:
			Mat3();
			float mat[9];
			void Print();
			Mat3(const float(&arr)[9]);
			Mat3(float a, float b, float c, float d, float e, float f, float g, float h, float i);
			Vec3 operator*(const Vec3& rhs);
			Mat3 operator*(const Mat3& rhs);
			static Mat3 identity();
			void TransposeMatrix(const int M, const int N);

			~Mat3();
		};


		class Mat4
		{
		public:
			Mat4();
			float mat[16];
			void Print();
			Mat4(const float(&arr)[16]);
			Mat4(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, float k, float l, float m, float n, float o, float p);
			Vec4 operator*(const Vec4& rhs);
			Mat4 operator*(const Mat4& rhs);
			static Mat4 identity();
			static Mat4 Perspective();
			static Mat4 CreateTransformMatrix(const Vec3& rotation, const Vec3& position, const Vec3& scale);
			static Mat4 CreateTranslationMatrix(const Vec3& translation);
			static Mat4 CreateScaleMatrix(const Vec3& scale);
			static Mat4 CreateXRotationMatrix(float angle);
			static Mat4 CreateYRotationMatrix(float angle);
			static Mat4 CreateZRotationMatrix(float angle);
			void TransposeMatrix(const int M, const int N);

			~Mat4();
		};


	}
}