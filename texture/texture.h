#pragma once

#include "utilities.h"

class Texture {
public:
    uint texture[2]{};

    Texture() = default;

    ~Texture() = default;

    void readImage(const char path[256], int &image_w, int &image_h, int &pixel_l);

    void loadTexture();

private:
    int image_width{}, image_height{}, pixel_length{};
    std::vector<GLubyte *> p;
};