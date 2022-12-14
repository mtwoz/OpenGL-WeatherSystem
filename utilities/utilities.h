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
#define RAD2DEG 57.2957795f

#define WIND_MAX 0.05
#define WIND_MIN (-0.05)
#define WIND_STEP 0.005
extern float wind_velocity_x;
extern float wind_velocity_z;

#define FLAG_ANGLE_MAX 360
#define FLAG_ANGLE_MIN 0
#define FLAG_ANGLE_STEP 1

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
