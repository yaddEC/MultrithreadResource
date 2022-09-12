#include <Camera.h>

using namespace Core;
using namespace Maths;
using namespace LowRenderer;
#define sensitivity 0.05f

void Camera::Update(const float p_deltaTime, const CameraInputs& inputs)
{
	to.x += inputs.deltaX * p_deltaTime* sensitivity;
	to.y += inputs.deltaY * p_deltaTime* sensitivity;
	if (to.x > 250)
		to.x = 250;
	if (to.x < 100)
		to.x = 100;
}

Mat4 Camera::GetView()
{
	Vec3 direction;
	direction = Vec3(cos(rad(to.y)) * -cos(rad(to.x)),
				-sin(rad(to.x)),
				sin(rad(to.y)) * cos(rad(to.x)));

	up = { 0, 1, 0 };

	forward = direction;
	forward.Normalize();
	right = CrossProduct(up, forward).Normalize();

	Vec3 yaxis = CrossProduct(forward, right);
	float array[16] =
	{
		right.x, right.y, right.z, -dot(from,right),
		yaxis.x, yaxis.y, yaxis.z, -dot(from,yaxis),
		forward.x , forward.y, forward.z, -dot(from,forward),
		0, 0, 0, 1
	};

	return array;
}

Mat4 Camera::GetProjection()
{
	float f = 100;
	float n = 1;
	float fov = 45;
	float s = 1 / tanf((fov / 2) * (M_PI / 180));
	float c = f / (f - n);
	float array[16] = {

		s,0.f,0.f,0.f,
		0.f,s,0.f,0.f,
		0.f,0.f,-c,-(c * n),
		0.f,0.f,-1.f ,0.f,

	};
	return array;
}

