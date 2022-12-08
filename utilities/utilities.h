#pragma once

#include <ctime>
#include <random>
#include <GL/glut.h>

#define WIDTH 1280
#define HEIGHT 720
#define DEG_TO_RAD 0.01745329

// store points
typedef struct {
    GLfloat x, y, z;
} Point;

int randomInt(int, int);

float randomFloat(float, float);

bool randomBool();

void resetCoordinationSystem();
