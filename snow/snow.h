#pragma once

#include "utilities.h"

#define SNOW_COUNT 1000

class Snow {
public:
    Snow();

    ~Snow() = default;

    void update();

    void draw();

private:
    Point position;
    float color[4];

    float life;
    float fade;
    float vel;
    float gravity;
    float motion_x;
    float motion_z;

    bool on_ground;

    void reset();
};