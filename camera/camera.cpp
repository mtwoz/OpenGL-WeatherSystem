#include "camera.h"

Camera::Camera() {
    this->fovy = 60.0f;
    this->aspect = float(WIDTH) / float(HEIGHT);
    this->z_near = 0.1f;
    this->z_far = 100.0f;

    this->eye_x = 0.0f;
    this->eye_y = 0.0f;
    this->eye_z = 0.0f;

    this->center_x = 0.0f;
    this->center_y = 0.0f;
    this->center_z = 0.0f;
    this->up_x = 0.0f;
    this->up_y = 1.0f;
    this->up_z = 0.0f;

    this->lat = 0.0f;
    this->lon = 255.0f;
    this->m_lat = 0.0f;
    this->m_lon = 0.0f;

    for(int i = 1; i <= 100; i++) {
        this->moveBackward();
    }

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(this->fovy, this->aspect, this->z_near, this->z_far);
}

void Camera::update() {
    this->center_x = this->eye_x + (float) (cosf((lat + m_lat) * DEG2RAD) * sinf((lon + m_lon) * DEG2RAD));
    this->center_y = this->eye_y + (float) (sinf((lat + m_lat) * DEG2RAD));
    this->center_z = this->eye_z + (float) (cosf((lat + m_lat) * DEG2RAD) * cosf((lon + m_lon) * DEG2RAD));

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(this->fovy, this->aspect, this->z_near, this->z_far);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(this->eye_x, this->eye_y, this->eye_z,
              this->center_x, this->center_y, this->center_z,
              this->up_x, this->up_y, this->up_z);
}

void Camera::moveForward() {
    this->eye_x += (float) sinf(lon * DEG2RAD) * EYE_STEP;
    this->eye_y += (float) sinf(lat * DEG2RAD) * EYE_STEP;
    this->eye_z += (float) cosf(lon * DEG2RAD) * EYE_STEP;
}

void Camera::moveBackward() {
    this->eye_x -= (float) sinf(lon * DEG2RAD) * EYE_STEP;
    this->eye_y -= (float) sinf(lat * DEG2RAD) * EYE_STEP;
    this->eye_z -= (float) cosf(lon * DEG2RAD) * EYE_STEP;
}

void Camera::moveLeft() {
    this->eye_z += EYE_STEP;
}

void Camera::moveRight() {
    this->eye_z -= EYE_STEP;
}

void Camera::moveUp() {
    this->eye_y -= EYE_STEP;
}

void Camera::moveDown() {
    this->eye_y += EYE_STEP;
}

void Camera::rotateUp() {
    if (this->lat + this->m_lat + TURN_ANGLE < 90)
        this->lat += TURN_ANGLE;
}

void Camera::rotateDown() {
    if (this->lat + this->m_lat - TURN_ANGLE > -90)
        this->lat -= TURN_ANGLE;
}

void Camera::rotateLeft() {
    this->lon += TURN_ANGLE;
}

void Camera::rotateRight() {
    this->lon -= TURN_ANGLE;
}