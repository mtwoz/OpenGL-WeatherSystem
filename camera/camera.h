#pragma once
#define FREEGLUT_STATIC

#include "utilities.h"

#define EYE_STEP 0.5f
#define TURN_ANGLE 4.0

class Camera {
public:
    Camera();

    ~Camera() = default;

    void update();

    void moveForward();

    void moveBackward();

    void moveLeft();

    void moveRight();

    void moveUp();

    void moveDown();

    void rotateUp();

    void rotateDown();

    void rotateLeft();

    void rotateRight();

    // latitude and longitude
    float lat, lon;
    float m_lat, m_lon;

private:
    // perspective
    float fovy;
    float aspect;
    float z_near, z_far;

    // lookat
    float eye_x, eye_y, eye_z;
    float center_x, center_y, center_z;
    float up_x, up_y, up_z;
};
