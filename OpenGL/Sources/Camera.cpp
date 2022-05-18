#include <Camera.h>

using namespace Core;
using namespace Maths;
using namespace LowRenderer;


void Camera::Update(const float p_deltaTime, const CameraInputs& inputs)
{
    if (inputs.deltaX > 0)
    {
        to.x += inputs.deltaX * p_deltaTime;
        to.y += inputs.deltaY * p_deltaTime;
    }

    else if (inputs.deltaX < 0)
    {
        to.x += inputs.deltaX * p_deltaTime;
        to.y += inputs.deltaY * p_deltaTime;
    }
    // DOESNT WORK VERY WELL :(
    if (inputs.moveForward)
    {
        move.x = move.x - 0.5f * sin(to.x) / 10;
        move.z = move.z - 0.5f * cos(to.z) / 10;

    }
    else if (inputs.moveBackward)
    {
        move.x = move.x + 0.5f * sin(to.x) / 20.f;
        move.z = move.z + 0.5f * cos(to.z) / 20.f;

    }
}

Mat4 Camera::GetViewMatrix()
{
    Vec3 tmp = { 0, 1, 0 };
    tmp.Normalize();
    Vec3 forward = from - to;
    forward.Normalize();
    Vec3 right = CrossProduct(tmp, forward);
    Vec3 up = CrossProduct(forward, right);
    float array[16] =
    {
        right.x, right.y, right.z, 0,
        up.x, up.y, up.z, 0,
        forward.x + move.x, forward.y, forward.z + move.z, 0,
        from.x + move.x, from.y, from.z + move.z, 1 
    };

    return array;
}

Mat4 Camera::GetProjection()
{
    float f = 2; // far clipping plane
    float n = 1; // near clipping plane
    float fov = 60;
    float s = 1 / tanf((fov / 2) * (M_PI / 180));
    float c = f / (f - n);
    float array[16] = {

        s,
        0.f,
        0.f,
        0.f,
        0.f,
        s,
        0.f,
        0.f,
        0.f,
        0.f,
        -c,
        -1.f,
        0.f,
        0.f,
        -(c * n),
        0.f,

    };
    return array;
}

void Camera::ShowImGuiControls()
{
    //TODO
}
