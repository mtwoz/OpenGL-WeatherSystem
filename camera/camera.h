#pragma once
#define FREEGLUT_STATIC

#include "utilities.h"

#define DEG_TO_RAD 0.01745329

#define Z_NEAR_MIN 3.0f
#define Z_NEAR_MAX 3.9f
#define Z_NEAR_STEP 0.01f

#define EYE_STEP 0.3f
#define EYE_X_MIN -1.0f
#define EYE_X_MAX 1.0f
#define EYE_X_STEP 0.3f
#define EYE_Y_MIN -1.0f
#define EYE_Y_MAX 1.0f
#define EYE_Y_STEP 0.3f
#define EYE_Z_MIN -1.0f
#define EYE_Z_MAX 1.88f
#define EYE_Z_STEP 0.3f

#define CENTER_X_STEP EYE_X_STEP
#define CENTER_Y_STEP EYE_Y_STEP
#define CENTER_Z_STEP EYE_Z_STEP

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

    void rotate(int dx, int dy);

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
