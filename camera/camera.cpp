#include "camera.h"

Camera::Camera() {
    this->fovy = 60.0f;
    this->aspect = float(WIDTH) / float(HEIGHT);
    this->z_near = 0.1f;
    this->z_far = 100.0f;

    this->eye_x = 0.0f;
    this->eye_y = -0.2f;
    this->eye_z = 1.5f;
    this->center_x = 0.0f;
    this->center_y = 0.0f;
    this->center_z = 0.0f;
    this->up_x = 0.0f;
    this->up_y = 1.0f;
    this->up_z = 0.0f;

    this->lat = 0.0f;
    this->lon = 255.0f;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(this->fovy, this->aspect, this->z_near, this->z_far);
}

void Camera::update() {
    this->center_x = this->eye_x + (float) (cos((lat + m_lat) * DEG_TO_RAD) * sin((lon + m_lon) * DEG_TO_RAD));
    this->center_y = this->eye_y + (float) (sin((lat + m_lat) * DEG_TO_RAD));
    this->center_z = this->eye_z + (float) (cos((lat + m_lat) * DEG_TO_RAD) * cos((lon + m_lon) * DEG_TO_RAD));

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
    this->eye_x += (float) sin(lon * DEG_TO_RAD) * EYE_STEP;
    this->eye_y += (float) sin(lat * DEG_TO_RAD) * EYE_STEP;
    this->eye_z += (float) cos(lon * DEG_TO_RAD) * EYE_STEP;
}

void Camera::moveBackward() {
    this->eye_x -= (float) sin(lon * DEG_TO_RAD) * EYE_STEP;
    this->eye_y -= (float) sin(lat * DEG_TO_RAD) * EYE_STEP;
    this->eye_z -= (float) cos(lon * DEG_TO_RAD) * EYE_STEP;
}

void Camera::moveUp() {
    if (this->lat + this->m_lat + TURN_ANGLE < 90)
        this->lat += TURN_ANGLE;
}

void Camera::moveDown() {
    if (this->lat + this->m_lat - TURN_ANGLE > -90)
        this->lat -= TURN_ANGLE;
}

void Camera::moveLeft() {
    this->lon += TURN_ANGLE;
}

void Camera::moveRight() {
    this->lon -= TURN_ANGLE;
}

void Camera::rotate(int dx, int dy) {
}