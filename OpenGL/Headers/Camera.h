#pragma once
#include <Maths.h>

namespace LowRenderer
{
    struct CameraInputs
    {
        float deltaX;
        float deltaY;
        bool moveForward;
        bool moveBackward;
    };

    class Camera
    {
    private:
    public:
        Core::Maths::Vec3 from = { 0,0,-9};
        Core::Maths::Vec3 to = { 180,90,0 };
        Core::Maths::Vec3 move = { 0,0,0 };
        Core::Maths::Vec3 forward = { 0,0,0 };
        Core::Maths::Vec3 up = { 0,0,0 };
        Core::Maths::Vec3 right = { 0,0,0 };
        float speed =0.03;

        void Update(const float p_deltaTime, const CameraInputs& p_inputs);
        Core::Maths::Mat4 GetView();
        Core::Maths::Mat4 GetProjection();

    };
}