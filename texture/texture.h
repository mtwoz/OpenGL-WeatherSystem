#pragma once

#include "utilities.h"

class Texture {
public:
    uint texture[2];

    Texture() = default;

    ~Texture() = default;

    void readImage(const char path[256], int &image_w, int &image_h, int &pixel_l);

    void loadTexture();

private:
    int image_width_grass, image_height_grass, pixel_length_grass;
    int image_width_runway, image_height_runway, pixel_length_runway;
    std::vector<GLubyte *> p;
};