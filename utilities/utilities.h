#pragma once

#include <ctime>
#include <random>
#include <iostream>
#include <GL/glut.h>

#define WIDTH 1280
#define HEIGHT 720

extern float wind_velocity_x;
extern float wind_velocity_z;

// store points
typedef struct {
    GLfloat x, y, z;
} Point;

int randomInt(int, int);

float randomFloat(float, float);

bool randomBool();
