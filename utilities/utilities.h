#pragma once

#include <ctime>
#include <random>
#include <iostream>
#include <memory>
#include <cstring>
#include <GL/glut.h>

#define WIDTH 1280
#define HEIGHT 720

#define DEG2RAD 0.01745329f

extern float wind_velocity_x;
extern float wind_velocity_z;

#define FLAG_ANGLE_MAX 360
#define FLAG_ANGLE_STEP 2

extern int flag_angle;

// store points
typedef struct {
    GLfloat x, y, z;
} Point;

// store colors
typedef struct {
    GLfloat r, g, b, a;
} Color;

int randomInt(int, int);

float randomFloat(float, float);

bool randomBool();
