#pragma once

#include "utilities.h"

// constants for snow
#define SNOW_COUNT 200
#define SNOW_MARGIN_X 50
#define SNOW_MARGIN_Y 20
#define SNOW_SIZE_MIN 15
#define SNOW_SIZE_MAX 25

extern float wind_velocity_x;
extern float wind_velocity_y;

class Snow {
public:

    Snow();

    ~Snow() = default;

    void update();

    void draw();

private:
    Point position{};
    float color[4]{};

    bool alive;
    float life;
    float fade;
    float vel;
    float gravity;

    void reset();
};
