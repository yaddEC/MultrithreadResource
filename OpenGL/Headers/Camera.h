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
        // ... and more if needed
    };

    class Camera
    {
    private:
    public:
        Core::Maths::Vec3 from ;
        Core::Maths::Vec3 to ;
        Core::Maths::Vec3 move ;


        void Update(const float p_deltaTime, const CameraInputs& p_inputs);
        Core::Maths::Mat4 GetViewMatrix();
        Core::Maths::Mat4 GetProjection();

        void ShowImGuiControls();
    };
}