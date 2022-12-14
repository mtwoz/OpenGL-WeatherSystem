#pragma once

#include "utilities.h"

#define HAIL_COUNT 1000

class HailFrag {
public:
    HailFrag() = default;

    HailFrag(Color color, Point pos);

    ~HailFrag() = default;

    void draw();

    void update();

    Point position{};
    Color color{};
    int frag_on{};
    float frag_time{};

private:

    int frag_cnt{};
    int frag_shape{};

    int rotate_angle{};
    int rotate_x{};
    int rotate_y{};
    int rotate_z{};

    float frag_attr[10][4]{};
};

class Hail {
public:
    Hail();

    ~Hail() = default;

    void draw();

    void update();

private:
    Point position{};
    Color color{};

    HailFrag hail_frag;

    float life;
    float fade;
    float vel;
    float gravity;
    float motion_x;
    float motion_z;

    int shape;

    int rotate_angle;
    int rotate_x;
    int rotate_y;
    int rotate_z;

    void reset();
};