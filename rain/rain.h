#pragma once

#include "utilities.h"

#define RAIN_COUNT 1000
#define TWO_PI (2*M_PI)


class Rain {
public:
    Rain();

    ~Rain() = default;

    void update_ground();

    void update_sky();

    void draw();

    void draw_drop();

    void draw_ripple();

private:
    Point position{};
    float color[4]{};

    float life;
    float fade;
    float vel;
    float gravity;
    float radius;

    bool on_ground;

    void reset();
};