#pragma once
#define FREEGLUT_STATIC

class Camera {
public:
    Camera();
    ~Camera() = default;

    float zoom;
    float pan;
    float tilt;

private:
};
