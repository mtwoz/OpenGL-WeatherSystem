#pragma once

#include "utilities.h"

class Ground {
public:

    float g_points[31][31][3];
    float g_colors[31][31][4];

    Ground() = default;

    ~Ground() = default;

    void drawGrass();

    void drawRunway();

private:
};